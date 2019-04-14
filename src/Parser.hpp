//
// Created by Furkat MALLABAEV on 2019-04-06.
//

#ifndef EXPERT_SYSTEMS_PARSER_HPP
#define EXPERT_SYSTEMS_PARSER_HPP

#include <list>
#include <map>
#include <string>
#include <vector>

#include "Fact.hpp"
#include "Types.hpp"

class Parser {
   public:
    Parser(std::string file) : _file(std::move(file))
    {
    }

    ~Parser() = default;

    void parse_file();

    Facts &getFacts()
    {
        return _facts;
    }

    Queries &getQueries()
    {
        return _queries;
    }

   private:
    void parse_rules(std::ifstream &inf);
    void parse_facts(std::ifstream &inf);
    void parse_queries(std::ifstream &inf);
    void clear_line(std::string &str);
    RuleInst create_rule(std::string &str);
    void check_expression(const std::string &str);
    void check_conclusion(const std::string &str);
    void add_facts(RuleInst rule);
    void set_initial_facts(const std::string &str);
    void convertToRPN(std::string &expression);
    int precedence(char x);

    std::string _file;
    std::shared_ptr<std::pair<std::string, std::string>> tmp;
    Rules _rules;
    Facts _facts;
    Queries _queries;
};

#endif  // EXPERT_SYSTEMS_PARSER_HPP
