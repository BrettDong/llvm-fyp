// Copyright 2022 Binrui Dong
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ConstraintSolver.h"

bool ConstraintSolver::intersectWith(ClassSet &dst, const ClassSet &src) {
    return dst.intersectWith(src);
}

bool ConstraintSolver::unionWith(ClassSet &dst, const ClassSet &src) { return dst.unionWith(src); }

void ConstraintSolver::solve() {
    std::queue<NodeID> q;

    for (const auto &[node, val] : system->constants) {
        answers.insert({node, val});
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

        if (answers.count(cur) == 0) {
            answers.insert({cur, ClassSet(classes)});
        }

        for (NodeID left : system->backwardEdges[cur]) {
            if (system->constants.count(left) > 0) {
                continue;
            }

            if (answers.count(left) == 0) {
                answers.insert({left, ClassSet(classes)});
            }

            bool changed = false;

            if (system->backwardVisited[left]) {
                changed = intersectWith(answers.at(left), answers.at(cur));
            } else {
                for (const Elem &elem : answers.at(cur).toClasses()) {
                    answers.at(left).insert(elem);
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

            if (answers.count(right) == 0) {
                answers.insert({right, ClassSet(classes)});
            }

            bool changed = unionWith(answers.at(right), answers.at(cur));

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
        if (system->backwardEdges[node].empty()) {
            continue;
        }
        ClassSet unionOf(classes);
        for (const NodeID &prev : system->backwardEdges[node]) {
            if (answers.count(prev) == 0) {
                answers.insert({prev, ClassSet(classes)});
            }
            unionWith(unionOf, answers.at(prev));
        }
        if (unionOf.empty()) {
            continue;
        }
        bool changed = intersectWith(answers.at(node), unionOf);
        if (changed) {
            for (const NodeID &next : system->forwardEdges[node]) {
                q.push(next);
            }
        }
    }

    while (!q.empty()) {
        NodeID cur = q.front();
        q.pop();
        if (system->backwardEdges[cur].empty()) {
            continue;
        }
        ClassSet unionOf(classes);
        for (const NodeID &prev : system->backwardEdges[cur]) {
            unionWith(unionOf, answers.at(prev));
        }
        if (unionOf.empty()) {
            continue;
        }
        bool changed = intersectWith(answers.at(cur), unionOf);
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
    for (const NodeID &node : system->nodes) {
        if (system->backwardEdges[node].empty() && !system->forwardEdges[node].empty()) {
            q.push(node);
        }
    }

    while (!q.empty()) {
        NodeID cur = q.front();
        q.pop();
        visited.insert(cur);

        for (const NodeID &next : system->forwardEdges[cur]) {
            if (answers.count(cur) > 0 && answers.count(next) > 0 &&
                !answers.at(cur).isSubSetOf(answers.at(next))) {
                return false;
            }
            if (visited.count(next) == 0) {
                q.push(next);
            }
        }
    }

    return true;
}

ClassSet ConstraintSolver::query(NodeTy v) {
    if (system->idMap.count(v) == 0) {
        return ClassSet(classes);
    }
    return answers.at(system->idMap[v]);
}
