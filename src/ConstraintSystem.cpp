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

bool ConstraintSystem::Constraint::operator<(const Constraint &rhs) const {
    if (a != rhs.a) {
        return a < rhs.a;
    } else if (b != rhs.b) {
        return b < rhs.b;
    } else {
        return c < rhs.c;
    }
}

void ConstraintSystem::addConstraint(NodeID a, NodeID b, ConstraintRelation c) {
    nodes.insert(a);
    nodes.insert(b);
    constraints.insert(Constraint(a, b, c));
}

void ConstraintSystem::addLiteralConstraint(NodeID a, const ClassSet &literal,
                                            ConstraintRelation c) {
    nodes.insert(a);
    NodeID literalId = nextConstantId--;
    constraints.insert(Constraint(a, literalId, c));
    constants.insert({literalId, literal});
}

void ConstraintSystem::buildGraph() {
    for (const Constraint &constraint : constraints) {
        if (constraint.c == ConstraintRelation::Subset) {
            forwardEdges[constraint.a].insert(constraint.b);
            backwardEdges[constraint.b].insert(constraint.a);
        } else {
            forwardEdges[constraint.b].insert(constraint.a);
            backwardEdges[constraint.a].insert(constraint.b);
        }
    }
}

std::string ConstraintSystem::visualizeConstraintOperand(const NodeID id) {
    if (id >= 0) {
        return "%" + std::to_string(id);
    } else {
        return "{" + list_out(constants.at(id).toClasses()) + "}";
    }
}

void ConstraintSystem::printConstraint(Constraint constraint) {
    if (constraint.c == ConstraintRelation::Subset) {
        llvm::outs() << visualizeConstraintOperand(constraint.a)
                     << " <= " << visualizeConstraintOperand(constraint.b) << "\n";
    } else {
        llvm::outs() << visualizeConstraintOperand(constraint.b)
                     << " <= " << visualizeConstraintOperand(constraint.a) << "\n";
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
