#include "Analyzer.h"

#include "FunctionObjectFlow.h"
#include "Utils.h"

std::optional<int> Analyzer::getVTableIndex(const CallBase *callInst) const {
    const LoadInst *loadInst = dyn_cast<LoadInst>(callInst->getCalledOperand());
    if (loadInst == nullptr) return std::nullopt;

    const auto *GEP = dyn_cast<GetElementPtrInst>(loadInst->getPointerOperand());
    if (GEP == nullptr) return std::nullopt;

    const ConstantInt *index = dyn_cast<ConstantInt>(GEP->getOperand(1));
    if (index == nullptr) return std::nullopt;

    return index->getZExtValue();
}

std::optional<string> Analyzer::getVirtCallType(const CallBase *callInst) const {
    const Type *op0Ty = callInst->getArgOperand(0)->getType();
    if (op0Ty == nullptr) return std::nullopt;
    const StructType *ty = dyn_cast<StructType>(op0Ty->getPointerElementType());
    if (ty == nullptr) return std::nullopt;
    std::string className = ty->getName().str();
    if (beginsWith(className, "class.")) {
        className = removePrefix(className, "class.");
    } else if (beginsWith(className, "struct.")) {
        className = removePrefix(className, "struct.");
    }
    className = stripTrailing(className);
    if (!classes.isClassExist(className)) {
        // outs() << "Non-existing class name " << className << '\n';
        return std::nullopt;
    }
    return className;
}

set<string> Analyzer::analyzeVirtCall(const CallBase *callInst) {
    auto index = getVTableIndex(callInst);
    if (!index.has_value()) {
        // outs() << "cannot get vtable index" << '\n';
        return set<string>();
    }
    auto type = getVirtCallType(callInst);
    if (!type.has_value()) {
        // outs() << "cannot get virt call type" << '\n';
        return set<string>();
    }
    set<string> derivedClasses = classes.getHierarchyGraph().queryDerivedClasses(type.value());
    derivedClasses.insert(type.value());
    set<string> targets;
    for (const string &derived : derivedClasses) {
        Function *target = classes.getClass(derived).getVTable()->getEntry(index.value());
        targets.insert(demangle(target->getName().str()));
    }
    auto pure_virtual = targets.find("__cxa_pure_virtual");
    if (pure_virtual != targets.end()) {
        targets.erase(pure_virtual);
    }
    return targets;
}

void Analyzer::analyzeFunction(const Function &f) {
    FunctionObjectFlow flow;
    flow.analyzeFunction(&f);

    for (auto &bb : f) {
        for (auto &inst : bb) {
            if (auto callInst = dyn_cast<CallBase>(&inst)) {
                if (callInst->getCalledFunction() == nullptr) {
                    set<string> targets = analyzeVirtCall(callInst);
                    if (!targets.empty()) {
                        const Value *obj = callInst->getOperand(0);
                        ObjectFlowOrigin origin = flow.traverseBack(obj);
                        outs() << "Indirect call " << callInst << " has " << targets.size()
                               << " targets:\n";
                        for (auto &target : targets) {
                            outs() << demangle(f.getName().str()) << " =(I)=> " << target << "\n";
                        }
                        outs() << "Object origin: ";
                        if (origin.argument) {
                            outs() << "[arg]";
                        }
                        if (origin.instantiated) {
                            outs() << "[instantiated]";
                        }
                        if (origin.retVal) {
                            outs() << "[ret-val]";
                        }
                        outs() << '\n';
                        outs() << '\n';
                    }
                }
            }
        }
    }
}

Analyzer::Analyzer() { llvmContext = make_unique<LLVMContext>(); }

void Analyzer::analyze(const vector<string> &files) {
    for (const string &file : files) {
        // outs() << "Reading bitcode file: " << file << "\n";
        unique_ptr<Module> module = parseIRFile(file, err, *llvmContext);
        if (!module) {
            errs() << "Error loading bitcode file \"" << file << "\": " << err.getMessage() << "\n";
            continue;
        }
        modules[file] = std::move(module);
    }

    for (const auto &[file, module] : modules) {
        // outs() << "Decoding class information from " << file << '\n';
        classes.analyzeModule(module.get());
    }

    outs() << "Building class hierarchy graph" << '\n';
    classes.buildClassHierarchyGraph();

    for (const auto &[file, module] : modules) {
        // outs() << "Decoding functions from " << file << '\n';
        for (const Function &f : *module) {
            functions[f.getName().str()] = &f;
        }
    }

    // outs() << "Analyzing main function" << '\n';
    // analyzeFunction(*functions["_Z3fooP5Shaped"]);
    // analyzeFunction(*functions["main"]);
    for (auto it : functions) {
        analyzeFunction(*it.second);
    }
}
