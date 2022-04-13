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

#include "ConstraintSystem.h"

#include "Utils.h"

void ConstraintSystem::addConstraint(NodeTy a, NodeTy b, ConstraintRelation c) {
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
    // outs() << "Added variable constraint: ";
    // printConstraint(constraints.back());
}

void ConstraintSystem::addLiteralConstraint(NodeTy a, const std::set<Elem> &literal,
                                            ConstraintRelation c) {
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
    constants.insert({literalId, literal});
    constraints.emplace_back(idA, literalId, c);
    // outs() << "Added literal constraint: ";
    // printConstraint(constraints.back());
}

void ConstraintSystem::buildGraph() {
    for (const Constraint &constraint : constraints) {
        if (constraint.c == ConstraintRelation::Subset) {
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

std::optional<ConstraintSystem::NodeTy> ConstraintSystem::lookupNodeID(const NodeID &id) {
    for (const auto &[node, nodeID] : idMap) {
        if (nodeID == id) {
            return node;
        }
    }
    return std::nullopt;
};

std::string ConstraintSystem::visualizeConstraintOperand(const ConstraintSystem::NodeID &id) {
    auto origin = lookupNodeID(id);
    if (origin.has_value()) {
        return getInstSeqNum(origin.value());
    } else {
        return "{" + list_out(constants[id]) + "}";
    }
}

void ConstraintSystem::printConstraint(Constraint constraint) {
    if (constraint.c == ConstraintRelation::Subset) {
        llvm::outs() << "(" << lookupNodeID(constraint.a).value_or(nullptr) << ") "
                     << visualizeConstraintOperand(constraint.a) << " <= "
                     << "(" << lookupNodeID(constraint.b).value_or(nullptr) << ") "
                     << visualizeConstraintOperand(constraint.b) << "\n";
    } else {
        llvm::outs() << "(" << lookupNodeID(constraint.b).value_or(nullptr) << ") "
                     << visualizeConstraintOperand(constraint.b) << " <= "
                     << "(" << lookupNodeID(constraint.a).value_or(nullptr) << ") "
                     << visualizeConstraintOperand(constraint.a) << "\n";
    }
}

void ConstraintSystem::printConstraints() {
    for (const Constraint &constraint : constraints) {
        printConstraint(constraint);
    }
}

/*
void ConstraintSystem::run() {
    nodes = {2, 6, 9, 12, 15, 25, 26, 27};
    constraints.emplace_back(9, 27, ConstraintRelation::Subset);
    constraints.emplace_back(15, 27, ConstraintRelation::Subset);
    constraints.emplace_back(9, 2, ConstraintRelation::Subset);
    constraints.emplace_back(15, 2, ConstraintRelation::Subset);
    constraints.emplace_back(9, 6, ConstraintRelation::Subset);
    constraints.emplace_back(6, 25, ConstraintRelation::Subset);
    constraints.emplace_back(15, 12, ConstraintRelation::Subset);
    constraints.emplace_back(12, 26, ConstraintRelation::Subset);
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
