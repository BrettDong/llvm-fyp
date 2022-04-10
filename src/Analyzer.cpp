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
    if (callInst->arg_size() < 1) return std::nullopt;
    const Type *op0Ty = callInst->getArgOperand(0)->getType();
    if (op0Ty == nullptr) return std::nullopt;
    if (!op0Ty->isPointerTy()) return std::nullopt;
    const StructType *ty = dyn_cast<StructType>(op0Ty->getPointerElementType());
    if (ty == nullptr) return std::nullopt;
    std::string className = stripClassName(ty->getName().str());
    if (!classes.isClassExist(className)) {
        // outs() << "Non-existing class name " << className << '\n';
        return std::nullopt;
    }
    return className;
}

set<string> Analyzer::collectVirtualMethods(const set<string> &types, int index) const {
    set<string> targets;
    for (const string &className : types) {
        VTable *vtable = classes.getClass(className).getVTable();
        if (vtable == nullptr) {
            // outs() << derived << " does not have VTable!\n";
            continue;
        }
        Function *target = vtable->getEntry(index);
        if (target == nullptr) {
            // outs() << index.value() << " is out-of-bound in VTable of " << derived << '\n';
            continue;
        }
        targets.insert(demangle(target->getName().str()));
    }
    auto pure_virtual = targets.find("__cxa_pure_virtual");
    if (pure_virtual != targets.end()) {
        targets.erase(pure_virtual);
    }
    return targets;
}

void Analyzer::analyzeVirtCall(const CallBase *callInst) {
    auto index = getVTableIndex(callInst);
    if (!index.has_value()) {
        // outs() << "cannot get vtable index" << '\n';
        return;
    }
    auto type = getVirtCallType(callInst);
    if (!type.has_value()) {
        // outs() << "cannot get virt call type" << '\n';
        return;
    }
    const auto &hierarchy = classes.getHierarchyGraph();
    set<string> derivedClasses = hierarchy.querySelfWithDerivedClasses(type.value());

    set<string> CHA = collectVirtualMethods(derivedClasses, index.value());

    const Value *obj = callInst->getOperand(0);
    FunctionObjectFlow flow(&classes);
    flow.analyzeFunction(callInst->getParent()->getParent());
    set<string> OFA = collectVirtualMethods(flow.traverseBack(obj), index.value());

    if (CHA.empty()) {
        outs() << "NO TARGET FOUND: " << *callInst << '\n';
    } else {
        ++totalCallSites;
        totalCHATargets += CHA.size();
        totalOFATargets += OFA.size();
    }
    if (CHA == OFA) {
        return;
    }
    outs() << "In function " << demangle(callInst->getFunction()->getName().str()) << "\n";
    outs() << "At virtual call " << *callInst << "\n";
    outs() << "Class hierarchy analysis (" << CHA.size() << "): " << list_out(CHA) << '\n';
    outs() << "Object-flow analysis (" << OFA.size() << "): " << list_out(OFA) << '\n';
    outs() << '\n';
}

void Analyzer::analyzeFunction(const Function &f) {
    for (auto &bb : f) {
        for (auto &inst : bb) {
            if (auto callInst = dyn_cast<CallBase>(&inst)) {
                if (callInst->getCalledFunction() == nullptr) {
                    analyzeVirtCall(callInst);
                }
            }
        }
    }
}

Analyzer::Analyzer() { llvmContext = make_unique<LLVMContext>(); }

static void printTime(const decltype(chrono::system_clock::now()) &start) {
    float seconds = chrono::duration<float>(chrono::system_clock::now() - start).count();
    ostringstream oss;
    oss.precision(3);
    oss << fixed << seconds;
    outs() << "[" << oss.str() << "] ";
}

void Analyzer::analyze(const vector<string> &files) {
    auto start = chrono::system_clock::now();
    printTime(start);
    outs() << "Parsing LLVM IR from " << files.size() << " modules" << '\n';
    for (const string &file : files) {
        // outs() << "Reading bitcode file: " << file << "\n";
        unique_ptr<Module> module = parseIRFile(file, err, *llvmContext);
        if (!module) {
            errs() << "Error loading bitcode file \"" << file << "\": " << err.getMessage() << "\n";
            continue;
        }
        modules[file] = std::move(module);
    }

    printTime(start);
    outs() << "Analyzing class inheritance relationships" << '\n';
    for (const auto &[file, module] : modules) {
        // outs() << "Decoding class information from " << file << '\n';
        classes.analyzeModule(module.get());
    }

    printTime(start);
    outs() << "Building class hierarchy graph" << '\n';
    classes.buildClassHierarchyGraph();

    for (const auto &[file, module] : modules) {
        // outs() << "Decoding functions from " << file << '\n';
        for (const Function &f : *module) {
            functions[f.getName().str()] = &f;
        }
    }

    printTime(start);
    outs() << "Analyzing " << functions.size() << " functions" << '\n';
    // outs() << "Analyzing main function" << '\n';
    // analyzeFunction(*functions["_Z3fooP5Shaped"]);
    // analyzeFunction(*functions["main"]);
    for (const auto &it : functions) {
        analyzeFunction(*it.second);
    }

    printTime(start);
    outs() << "Analysis completed" << '\n';
    outs() << "Total virtual call sites: " << totalCallSites << '\n';
    outs() << "Total targets reported by class hierarchy analysis: " << totalCHATargets << '\n';
    outs() << "Total targets reported by object flow analysis: " << totalOFATargets << '\n';
}
