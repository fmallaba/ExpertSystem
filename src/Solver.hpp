//
// Created by Furkat MALLABAEV on 2019-04-13.
//

#ifndef EXPERT_SYSTEM_RPN_HPP
#define EXPERT_SYSTEM_RPN_HPP

#include <string>

#include "Types.hpp"

class Solver {
   public:
    explicit Solver(bool loop = false) : _loop(loop)
    {
    }

    bool solveExpression(FactInst &fact, Facts &facts);

   private:
    void setTrue(FactInst fact, RuleInst rule);
    bool performOp(char c, bool f, bool s);
    bool evaluateRule(RuleInst rule, Facts &facts);

    bool _loop;
};

#endif  // EXPERT_SYSTEM_RPN_HPP
