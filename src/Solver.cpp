//
// Created by Furkat MALLABAEV on 2019-04-14.
//

#include <iostream>
#include <stack>

#include "Solver.hpp"

bool Solver::solveExpression(FactInst &fact, Facts &facts)
{
    if (fact->first.isInitial()) {
        std::cout << fact->first.getLabel() << " is initial true\n";
        return true;
    }

    auto &rules = fact->second;
    if (rules.empty()) {
        std::cout << "There are no rules related " << fact->first.getLabel()
                  << std::endl;
    }
    for (auto &rule : rules) {
        std::cout << "Evaluate rule: \'" << rule->first << "\' to find "
                  << fact->first.getLabel() << std::endl;
        if (rule->second.front() == 0) {
            if (_loop) {
                std::cout << "WARNING: There is internal loop in rules"
                          << std::endl;
                return fact->first;
            } else {
                throw std::runtime_error("There is internal loop in rules");
            }
        }
        char tmp = rule->second.front();
        rule->second.front() = 0;
        auto res = evaluateRule(rule, facts);
        rule->second.front() = tmp;
        if (res) {
            setTrue(fact, rule);
        }
    }
    return fact->first;
}

void Solver::setTrue(FactInst fact, RuleInst rule)
{
    bool set = true;
    if (rule->second.find("!" + std::string(1, fact->first.getLabel()), 0) !=
        std::string::npos) {
        set = false;
    }
    if (fact->first.getStatus() && fact->first != set) {
        throw std::runtime_error("There is a contradiction with: " +
                                 std::string(1, fact->first.getLabel()));
    }
    fact->first.setStatus();
    fact->first = set;
}

bool Solver::performOp(char c, bool f, bool s)
{
    switch (c) {
        case '+':
            return f && s;
        case '|':
            return f || s;
        case '^':
            return f ^ s;
        default:
            return false;
    }
}

bool Solver::evaluateRule(RuleInst rule, Facts &facts)
{
    std::stack<bool> data;
    for (auto it = rule->first.begin(); it != rule->first.end(); ++it) {
        if (std::isupper(*it)) {
            auto fact = facts[*it];
            if (fact->first.getStatus()) {
                std::cout << *it << " already evaluated as "
                          << ((fact->first) ? "TRUE" : "FALSE") << std::endl;
                data.push(fact->first);
            } else {
                if (*(it + 1) == '|' && data.top()) {
                    data.push(false);
                } else {
                    fact->first = solveExpression(fact, facts);
                    data.push(fact->first);
                }
            }
        } else if (*it == '!') {
            auto f = data.top();
            data.pop();
            data.push(!f);
        } else {
            if (data.size() < 2) {
                throw std::runtime_error("Wrong expression: " + rule->first);
            }
            auto f = data.top();
            data.pop();
            auto s = data.top();
            data.pop();
            data.push(performOp(*it, f, s));
        }
    }
    if (data.size() != 1) {
        throw std::runtime_error("Wrong expression: " + rule->first);
    }
    return data.top();
}
