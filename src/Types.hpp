//
// Created by Furkat MALLABAEV on 2019-04-14.
//

#ifndef EXPERT_SYSTEM_TYPES_HPP
#define EXPERT_SYSTEM_TYPES_HPP

#include "Fact.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

using Rule = std::pair<std::string, std::string>;
using RuleInst = std::shared_ptr<Rule>;
using Rules = std::vector<RuleInst>;
using FactInst = std::shared_ptr<std::pair<Fact, Rules>>;
using Facts = std::map<char, FactInst>;
using Queries = std::string;

#endif  // EXPERT_SYSTEM_TYPES_HPP
