#include "Analyzer.h"

#include "Utils.h"

std::optional<int> Analyzer::getVTableIndex(const CallInst *callInst) const {
    const LoadInst *loadInst = dyn_cast<LoadInst>(callInst->getCalledOperand());
    if (loadInst == nullptr) return std::nullopt;

    const auto *GEP = dyn_cast<GetElementPtrInst>(loadInst->getPointerOperand());
    if (GEP == nullptr) return std::nullopt;

    const ConstantInt *index = dyn_cast<ConstantInt>(GEP->getOperand(1));
    if (index == nullptr) return std::nullopt;

    return index->getZExtValue();
}

std::optional<string> Analyzer::getVirtCallType(const CallInst *callInst) const {
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
    return className;
}

void Analyzer::analyzeVirtCall(const CallInst *callInst) {
    auto index = getVTableIndex(callInst);
    if (!index.has_value()) {
        outs() << "cannot get vtable index" << '\n';
        return;
    }
    auto type = getVirtCallType(callInst);
    if (!type.has_value()) {
        outs() << "cannot get virt call type" << '\n';
        return;
    }
    set<string> derivedClasses = classes.getHierarchyGraph().queryDerivedClasses(type.value());
    for (const string &derived : derivedClasses) {
        Function *target = classes.getClass(derived).getVTable()->getEntry(index.value());
        outs() << " -> " << demangle(target->getName().str()) << '\n';
    }
}

void Analyzer::analyzeFunction(const Function &f) {
    for (auto &bb : f) {
        for (auto &inst : bb) {
            if (auto callInst = dyn_cast<CallInst>(&inst)) {
                if (const Function *callee = callInst->getCalledFunction()) {
                    outs() << demangle(f.getName().str()) << " =(D)=> "
                           << demangle(callee->getName().str()) << '\n';
                } else {
                    outs() << demangle(f.getName().str()) << " =(I)=> ?\n";
                    analyzeVirtCall(callInst);
                }
            }
        }
    }
}

Analyzer::Analyzer() { llvmContext = make_unique<LLVMContext>(); }

void Analyzer::analyze(const vector<string> &files) {
    for (const string &file : files) {
        outs() << "Reading bitcode file: " << file << "\n";
        unique_ptr<Module> module = parseIRFile(file, err, *llvmContext);
        if (!module) {
            errs() << "Error loading bitcode file \"" << file << "\": " << err.getMessage() << "\n";
            continue;
        }
        modules[file] = std::move(module);
    }

    for (const auto &[file, module] : modules) {
        outs() << "Decoding class information from " << file << '\n';
        classes.analyzeModule(module.get());
    }

    outs() << "Building class hierarchy graph" << '\n';
    classes.buildClassHierarchyGraph();

    for (const auto &[file, module] : modules) {
        outs() << "Decoding functions from " << file << '\n';
        for (const Function &f : *module) {
            functions[f.getName().str()] = &f;
        }
    }

    outs() << "Analyzing main function" << '\n';
    analyzeFunction(*functions["main"]);
}
