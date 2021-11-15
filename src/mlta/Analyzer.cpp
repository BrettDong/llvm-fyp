#include "Analyzer.h"

void IterativeModulePass::run(ModuleList &modules) {
    ModuleList::iterator i, e;
    OP << "[" << ID << "] Initializing " << modules.size() << " modules ";
    bool again = true;
    while (again) {
        again = false;
        for (i = modules.begin(), e = modules.end(); i != e; ++i) {
            again |= doInitialization(i->first);
            OP << ".";
        }
    }
    OP << "\n";

    unsigned iter = 0, changed = 1;
    while (changed) {
        ++iter;
        changed = 0;
        unsigned counter_modules = 0;
        unsigned total_modules = modules.size();
        for (i = modules.begin(), e = modules.end(); i != e; ++i) {
            OP << "[" << ID << " / " << iter << "] ";
            OP << "[" << ++counter_modules << " / " << total_modules << "] ";
            OP << "[" << i->second << "]\n";

            bool ret = doModulePass(i->first);
            if (ret) {
                ++changed;
                OP << "\t [CHANGED]\n";
            } else
                OP << "\n";
        }
        OP << "[" << ID << "] Updated in " << changed << " modules.\n";
    }

    OP << "[" << ID << "] Postprocessing ...\n";
    again = true;
    while (again) {
        again = false;
        for (i = modules.begin(), e = modules.end(); i != e; ++i) {
            // TODO: Dump the results.
            again |= doFinalization(i->first);
        }
    }

    OP << "[" << ID << "] Done!\n\n";
}
