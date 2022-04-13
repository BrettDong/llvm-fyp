#include "ConstraintSolver.h"

bool ConstraintSolver::isSameCluster(std::set<Elem> a, std::set<Elem> b) const {
    std::set<int> cluster;
    for (const Elem elem : a) {
        cluster.insert(classes->clusterOf(elem));
    }
    for (const Elem elem : b) {
        cluster.insert(classes->clusterOf(elem));
    }
    return cluster.size() <= 1;
}

bool ConstraintSolver::intersectWith(std::set<Elem> &dst, const std::set<Elem> &src) {
    if (!isSameCluster(dst, src)) {
        llvm::outs() << "not the same cluster\n";
    }
    bool changed = false;
    std::set<Elem> toBeRemoved;
    for (const Elem &elem : dst) {
        if (src.count(elem) == 0) {
            toBeRemoved.insert(elem);
        }
    }
    if (!toBeRemoved.empty()) {
        for (const Elem &elem : toBeRemoved) {
            dst.erase(elem);
        }
        changed = true;
    }
    return changed;
}

bool ConstraintSolver::unionWith(std::set<Elem> &dst, const std::set<Elem> &src) {
    if (!isSameCluster(dst, src)) {
        llvm::outs() << "not the same cluster\n";
    }
    bool changed = false;
    for (const Elem &elem : src) {
        if (dst.count(elem) == 0) {
            dst.insert(elem);
            changed = true;
        }
    }
    return changed;
}

void ConstraintSolver::solve() {
    std::queue<NodeID> q;

    for (const auto &[node, val] : system->constants) {
        answers[node] = val;
    }

    for (const auto &[node, val] : system->constants) {
        if (!system->forwardEdges[node].empty() && system->backwardEdges[node].empty()) {
            q.push(node);
        }
    }
    for (const auto &[node, val] : system->constants) {
        if (system->forwardEdges[node].empty() && !system->backwardEdges[node].empty()) {
            q.push(node);
        }
    }

    while (!q.empty()) {
        NodeID cur = q.front();
        q.pop();

        for (NodeID left : system->backwardEdges[cur]) {
            if (system->constants.count(left) > 0) {
                continue;
            }

            bool changed = false;

            if (system->backwardVisited[left]) {
                changed = intersectWith(answers[left], answers[cur]);
            } else {
                for (const Elem &elem : answers[cur]) {
                    answers[left].insert(elem);
                }
                changed = true;
                system->backwardVisited[left] = true;
            }

            if (changed) {
                // outs() << "Node[" << cur << "] updated Node[" << left << "] to "
                //       << list_out(answers[left]) << '\n';
                system->backwardVisited[left] = true;
                q.push(left);
            }
        }

        for (NodeID right : system->forwardEdges[cur]) {
            if (system->constants.count(right) > 0 || system->backwardVisited[right]) {
                continue;
            }

            bool changed = unionWith(answers[right], answers[cur]);

            if (changed) {
                // outs() << "Node[" << cur << "] updated Node[" << right << "] to "
                //       << list_out(answers[right]) << '\n';
                system->forwardVisited[right] = true;
                q.push(right);
            }
        }
    }

    for (const NodeID &node : system->nodes) {
        if (system->constants.count(node) > 0) {
            continue;
        }
        std::set<Elem> unionOf;
        for (const NodeID &prev : system->backwardEdges[node]) {
            unionWith(unionOf, answers[prev]);
        }
        if (unionOf.empty()) {
            continue;
        }
        bool changed = intersectWith(answers[node], unionOf);
        if (changed) {
            for (const NodeID &next : system->forwardEdges[node]) {
                q.push(next);
            }
        }
    }

    while (!q.empty()) {
        NodeID cur = q.front();
        q.pop();
        std::set<Elem> unionOf;
        for (const NodeID &prev : system->backwardEdges[cur]) {
            unionWith(unionOf, answers[prev]);
        }
        if (unionOf.empty()) {
            continue;
        }
        bool changed = intersectWith(answers[cur], unionOf);
        if (changed) {
            for (const NodeID &next : system->forwardEdges[cur]) {
                q.push(next);
            }
        }
    }
}

static bool isSubsetOf(std::set<HashTy> a, const std::set<HashTy> &b) {
    for (const auto &elem : a) {
        if (b.count(elem) == 0) {
            return false;
        }
    }
    return true;
}

bool ConstraintSolver::sanityCheck() {
    std::queue<NodeID> q;
    std::set<NodeID> visited;
    std::set<int> cluster;
    for (const NodeID &node : system->nodes) {
        if (system->backwardEdges[node].empty() && !system->forwardEdges[node].empty()) {
            q.push(node);
        }
    }

    while (!q.empty()) {
        NodeID cur = q.front();
        q.pop();
        visited.insert(cur);
        for (const auto elem : answers[cur]) {
            cluster.insert(classes->clusterOf(elem));
        }

        for (const NodeID &next : system->forwardEdges[cur]) {
            if (!isSubsetOf(answers[cur], answers[next])) {
                return false;
            }
            if (visited.count(next) == 0) {
                q.push(next);
            }
        }
    }

    if (cluster.size() != 1) {
        // llvm::outs() << "cluster.size() != 1\n";
    }

    return true;
}

std::set<ConstraintSolver::Elem> ConstraintSolver::query(NodeTy v) {
    if (system->idMap.count(v) == 0) {
        return {};
    }
    return answers[system->idMap[v]];
}
