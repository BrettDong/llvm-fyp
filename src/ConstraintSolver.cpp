#include "ConstraintSolver.h"

#include "Utils.h"

void SetConstraintSolver::buildGraph() {
    for (const SetConstraint &constraint : constraints) {
        if (constraint.c == SetConstraintType::Subset) {
            forwardEdges[constraint.a].insert(constraint.b);
            backwardEdges[constraint.b].insert(constraint.a);
        } else {
            forwardEdges[constraint.b].insert(constraint.a);
            backwardEdges[constraint.a].insert(constraint.b);
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
            if (answers[left].empty()) {
                for (Elem elem : answers[cur]) {
                    answers[left].insert(elem);
                }
                changed = true;
            }
            set<Elem> toBeRemoved;
            for (Elem elem : answers[left]) {
                if (answers[cur].count(elem) == 0) {
                    toBeRemoved.insert(elem);
                }
            }
            if (!toBeRemoved.empty()) {
                for (Elem elem : toBeRemoved) {
                    answers[left].erase(elem);
                }
                changed = true;
            }
            if (changed) {
                outs() << "Node[" << cur << "] updated Node[" << left << "] to "
                       << list_out(answers[left]) << '\n';
                backwardVisited[left] = true;
                q.push(left);
            }
        }

        for (NodeID right : forwardEdges[cur]) {
            if (constants.count(right) > 0 || backwardVisited[right]) {
                continue;
            }

            bool changed = false;
            for (Elem elem : answers[cur]) {
                if (answers[right].count(elem) == 0) {
                    answers[right].insert(elem);
                    changed = true;
                }
            }

            if (changed) {
                outs() << "Node[" << cur << "] updated Node[" << right << "] to "
                       << list_out(answers[right]) << '\n';
                forwardVisited[right] = true;
                q.push(right);
            }
        }
    }
}

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
