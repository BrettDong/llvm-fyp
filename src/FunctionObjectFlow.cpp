#include "FunctionObjectFlow.h"

#include <queue>

#include "Utils.h"

static bool isConstructor(string functionName) {
    if (functionName.substr(functionName.length() - 2) != "()") return false;
    functionName = functionName.substr(0, functionName.length() - 2);
    auto pos = functionName.find("::");
    if (pos == string::npos) return false;
    string left = functionName.substr(0, pos);
    string right = functionName.substr(pos + 2);
    return left == right;
}

static string getConstructorClassName(string functionName) {
    functionName = functionName.substr(0, functionName.length() - 2);
    auto pos = functionName.find("::");
    string left = functionName.substr(0, pos);
    string right = functionName.substr(pos + 2);
    return right;
}

void FunctionObjectFlow::addEdge(const Value *src, const Value *dst) {
    auto it = edges.find(dst);
    if (it == edges.end()) {
        it = edges.insert({dst, set<const Value *>()}).first;
    }
    it->second.insert(src);
}

void FunctionObjectFlow::addInstantiation(const Value *dst, const string &className) {
    auto it = instantiations.find(dst);
    if (it == instantiations.end()) {
        it = instantiations.insert({dst, set<string>()}).first;
    }
    it->second.insert(className);
}

void FunctionObjectFlow::handleCallBase(const Instruction *inst) {
    const auto *callBase = dyn_cast<CallBase>(inst);
    // outs() << "CALL/INVOKE " << inst << " <- " << callBase->getOperand(0) << '\n';
    bool constructor = false;
    bool system = false;
    if (auto callee = callBase->getCalledFunction()) {
        string demangled = demangle(callee->getName().str());
        // outs() << "     (" << demangled << ")\n";
        if (isConstructor(demangled)) {
            constructor = true;
            // outs() << "     [ CONSTRUCTOR ]\n";
            addInstantiation(callBase->getOperand(0), getConstructorClassName(demangled));
        }
        if (beginsWith(demangled, "operator new") || beginsWith(demangled, "llvm.memset")) {
            system = true;
        }
    }
    if (!constructor && !system) {
        // outs() << "adding " << inst << " to ret val set: " << *inst << '\n';
        retVals.insert(inst);
    }
}

void FunctionObjectFlow::analyzeFunction(const Function *f) {
    function = f;

    for (const Argument &arg : f->args()) {
        arguments.emplace_back(&arg);
    }

    for (auto &bb : *f) {
        for (auto &inst : bb) {
            switch (inst.getOpcode()) {
                case Instruction::Alloca: {
                    alloca.insert(&inst);
                    // outs() << "ALLOCA " << &inst << '\n';
                    break;
                }
                case Instruction::Load: {
                    if (inst.getType()->isPointerTy()) {
                        addEdge(inst.getOperand(0), &inst);
                        // outs() << "LOAD " << &inst << " <- " << inst.getOperand(0) << '\n';
                    }
                    break;
                }
                case Instruction::Store: {
                    if (inst.getOperand(0)->getType()->isPointerTy()) {
                        addEdge(inst.getOperand(0), inst.getOperand(1));
                        // outs() << "STORE " << inst.getOperand(1) << " <- " << inst.getOperand(0)
                        // << '\n';
                    }
                    break;
                }
                case Instruction::BitCast: {
                    if (inst.getType()->isPointerTy()) {
                        addEdge(inst.getOperand(0), &inst);
                        // outs() << "BITCAST " << &inst << " <- " << inst.getOperand(0) << '\n';
                    }
                    break;
                }
                case Instruction::Call:
                case Instruction::Invoke: {
                    handleCallBase(dyn_cast<CallBase>(&inst));
                    break;
                }
                default: {
                    // outs() << "Unknown opcode " << inst.getOpcodeName() << '\n';
                }
            }
        }
    }
}

ObjectFlowOrigin FunctionObjectFlow::traverseBack(const Value *val) {
    ObjectFlowOrigin answer;
    queue<const Value *> q;
    set<const Value *> visited;
    set<string> result;
    q.push(val);
    while (!q.empty()) {
        const Value *cur = q.front();
        q.pop();
        visited.insert(cur);

        auto instantiation = instantiations.find(cur);
        if (instantiation != instantiations.end()) {
            answer.instantiated = true;
            for (const string &className : instantiation->second) {
                // outs() << "instantiated " << className << '\n';
            }
        }

        if (alloca.count(cur) != 0) {
            // outs() << "reached alloca." << '\n';
        }

        if (std::find(arguments.begin(), arguments.end(), cur) != arguments.end()) {
            answer.argument = true;
            // outs() << "from a function argument." << '\n';
        }

        if (retVals.count(cur) != 0) {
            answer.retVal = true;
            // outs() << cur << " is from return value from another function." << '\n';
        }

        auto edge = edges.find(cur);
        if (edge != edges.end()) {
            for (const Value *src : edge->second) {
                if (visited.count(src) == 0) {
                    // outs() << cur << " <- " << src << '\n';
                    q.push(src);
                }
            }
        }
    }

    return answer;
}
