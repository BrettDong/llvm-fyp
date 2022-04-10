#include "ConstraintSolver.h"

#include "Utils.h"

void SetConstraintSolver::addConstraint(NodeTy a, NodeTy b, SetConstraintType c) {
    NodeID idA = 0;
    if (idMap.count(a) == 0) {
        idA = nextId++;
        idMap[a] = idA;
        nodes.insert(idA);
    } else {
        idA = idMap[a];
    }
    NodeID idB = 0;
    if (idMap.count(b) == 0) {
        idB = nextId++;
        idMap[b] = idB;
        nodes.insert(idB);
    } else {
        idB = idMap[b];
    }
    constraints.emplace_back(idA, idB, c);
}

void SetConstraintSolver::addLiteralConstraint(NodeTy a, const set<Elem> &literal,
                                               SetConstraintType c) {
    NodeID idA = 0;
    if (idMap.count(a) == 0) {
        idA = nextId++;
        idMap[a] = idA;
        nodes.insert(idA);
    } else {
        idA = idMap[a];
    }
    NodeID literalId = nextId++;
    nodes.insert(literalId);
    constants.insert(literalId);
    answers[literalId] = literal;
    constraints.emplace_back(idA, literalId, c);
}

void SetConstraintSolver::buildGraph() {
    for (const SetConstraint &constraint : constraints) {
        if (constraint.c == SetConstraintType::Subset) {
            forwardEdges[constraint.a].insert(constraint.b);
            backwardEdges[constraint.b].insert(constraint.a);
            /*
            outs() << constraint.a << " is subset of " << constraint.b << '\n';
            if (constants.count(constraint.b) > 0) {
                outs() << "constant " << constraint.b << " is " << list_out(answers[constraint.b])
                       << '\n';
            }*/
        } else {
            forwardEdges[constraint.b].insert(constraint.a);
            backwardEdges[constraint.a].insert(constraint.b);
            // outs() << constraint.b << " is subset of " << constraint.a << '\n';
        }
    }
}

void SetConstraintSolver::solve() {
    queue<NodeID> q;

    for (const NodeID &i : nodes) {
        if (constants.count(i) > 0) {
            // (forwardEdges[i].empty() && !backwardEdges[i].empty()) ||
            // (!forwardEdges[i].empty() && backwardEdges[i].empty())) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        NodeID cur = q.front();
        q.pop();

        for (NodeID left : backwardEdges[cur]) {
            if (constants.count(left) > 0) {
                continue;
            }

            bool changed = false;

            if (backwardVisited[left]) {
                changed = intersectWith(answers[left], answers[cur]);
            } else {
                for (const Elem &elem : answers[cur]) {
                    answers[left].insert(elem);
                }
                changed = true;
                backwardVisited[left] = true;
            }

            if (changed) {
                // outs() << "Node[" << cur << "] updated Node[" << left << "] to "
                //       << list_out(answers[left]) << '\n';
                backwardVisited[left] = true;
                q.push(left);
            }
        }

        for (NodeID right : forwardEdges[cur]) {
            if (constants.count(right) > 0 || backwardVisited[right]) {
                continue;
            }

            bool changed = unionWith(answers[right], answers[cur]);

            if (changed) {
                // outs() << "Node[" << cur << "] updated Node[" << right << "] to "
                //       << list_out(answers[right]) << '\n';
                forwardVisited[right] = true;
                q.push(right);
            }
        }
    }
}

bool SetConstraintSolver::intersectWith(set<Elem> &dst, const set<Elem> &src) {
    bool changed = false;
    set<Elem> toBeRemoved;
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

bool SetConstraintSolver::unionWith(set<Elem> &dst, const set<Elem> &src) {
    bool changed = false;
    for (const Elem &elem : src) {
        if (dst.count(elem) == 0) {
            dst.insert(elem);
            changed = true;
        }
    }
    return changed;
}

set<SetConstraintSolver::Elem> SetConstraintSolver::query(NodeTy v) {
    if (idMap.count(v) == 0) {
        return {};
    }
    return answers[idMap[v]];
}

/*
void SetConstraintSolver::run() {
    nodes = {2, 6, 9, 12, 15, 25, 26, 27};
    constraints.emplace_back(9, 27, SetConstraintType::Subset);
    constraints.emplace_back(15, 27, SetConstraintType::Subset);
    constraints.emplace_back(9, 2, SetConstraintType::Subset);
    constraints.emplace_back(15, 2, SetConstraintType::Subset);
    constraints.emplace_back(9, 6, SetConstraintType::Subset);
    constraints.emplace_back(6, 25, SetConstraintType::Subset);
    constraints.emplace_back(15, 12, SetConstraintType::Subset);
    constraints.emplace_back(12, 26, SetConstraintType::Subset);
    constants.insert(25);
    constants.insert(26);
    constants.insert(27);
    answers[25] = {"Circle"};
    answers[26] = {"Square"};
    answers[27] = {"Shape", "Rectangle", "Square", "Circle"};

    buildGraph();

    solve();

    for (const NodeID &i : nodes) {
        if (!answers[i].empty()) {
            outs() << "Node[" << i << "] = " << list_out(answers[i]) << '\n';
        }
    }
}
*/
