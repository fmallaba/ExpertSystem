//
// Created by Furkat MALLABAEV on 2019-04-06.
//

#include <fstream>
#include <iostream>
#include <stack>

#include "Parser.hpp"

void Parser::parse_file()
{
    std::ifstream inf(_file.c_str());

    parse_rules(inf);
    parse_facts(inf);
    parse_queries(inf);
}

void Parser::parse_rules(std::ifstream &inf)
{
    std::string line;

    while (inf.peek() != '=' && std::getline(inf, line)) {
        if (line.length() == 0 || line[0] == '#') {
            continue;
        }
        clear_line(line);
        _rules.emplace_back(create_rule(line));
        auto rule = _rules.back();
        check_expression(rule->first);
        check_conclusion(rule->second);
        convertToRPN(rule->first);
        add_facts(rule);
        std::cout << line << " -> " << rule->first << " and " << rule->second
                  << std::endl;
    }
}

void Parser::parse_facts(std::ifstream &inf)
{
    std::string line;

    if (inf.peek() != '=') {
        throw std::runtime_error("Facts are missing");
    }

    if (std::getline(inf, line)) {
        clear_line(line);
        line.erase(0, 1);
        set_initial_facts(line);
        std::cout << line << std::endl;
    }
}

void Parser::parse_queries(std::ifstream &inf)
{
    std::string line;

    while (inf.peek() != '?') {
        if (inf.peek() != '#' && inf.peek() != '\n') {
            throw std::runtime_error("Queries should start with '?'");
        }
        std::getline(inf, line);
    }

    if (inf.peek() != '?') {
        throw std::runtime_error("Queries are missing");
    }

    if (std::getline(inf, line)) {
        clear_line(line);
        line.erase(0, 1);
        _queries = line;
        for (auto c : _queries) {
            if (_facts.find(c) == _facts.end()) {
                _facts[c] =
                    std::make_shared<std::pair<Fact, Rules>>(Fact(c), Rules());
            }
        }
        std::cout << line << std::endl;
    }
}

void Parser::clear_line(std::string &str)
{
    str = str.substr(0, str.find_first_of('#', 0));
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
}

void Parser::check_expression(const std::string &str)
{
    std::for_each(str.begin(), str.end(), [&](char c) {
        if (c >= 'A' && c <= 'Z')
            return;
        if (c == '+' || c == '|' || c == '^' || c == '!' || c == '(' ||
            c == ')')
            return;
        throw std::runtime_error("Syntax error in: " + str);
    });
}

void Parser::check_conclusion(const std::string &str)
{
    std::for_each(str.begin(), str.end(), [&](char c) {
        if (c >= 'A' && c <= 'Z')
            return;
        if (c == '+' || c == '!')
            return;
        throw std::runtime_error("Syntax error in: " + str);
    });
}

RuleInst Parser::create_rule(std::string &str)
{
    RuleInst rule(new Rule);
    auto pos = std::string::npos;

    if ((pos = str.find("<=>", 0)) != std::string::npos) {
        rule->second = str.substr(0, pos);
        rule->first = str.substr(pos + 3, str.size());
    } else if ((pos = str.find("=>", 0)) != std::string::npos) {
        rule->first = str.substr(0, pos);
        rule->second = str.substr(pos + 2, str.size());
    }

    if (rule->first.empty() || rule->second.empty()) {
        throw std::runtime_error("Syntax error in: " + str);
    }
    return rule;
}

void Parser::add_facts(RuleInst rule)
{
    for (char c : rule->second) {
        if (std::isupper(c)) {
            auto it = _facts.end();
            if ((it = _facts.find(c)) == _facts.end()) {
                _facts[c] = std::make_shared<std::pair<Fact, Rules>>(
                    Fact(c), Rules{rule});
            } else {
                it->second->second.emplace_back(rule);
            }
        }
    }
    for (char c : rule->first) {
        if (std::isupper(c)) {
            if (_facts.find(c) == _facts.end()) {
                _facts[c] =
                    std::make_shared<std::pair<Fact, Rules>>(Fact(c), Rules());
            }
        }
    }
}

void Parser::set_initial_facts(const std::string &str)
{
    for (char c : str) {
        if (std::isupper(c)) {
            auto it = _facts.end();
            if ((it = _facts.find(c)) == _facts.end()) {
                Fact f(c);
                f = true;
                f.setStatus();
                f.setInitial();
                _facts[c] =
                    std::make_shared<std::pair<Fact, Rules>>(Fact(c), Rules());
            } else {
                _facts[c]->first = true;
                _facts[c]->first.setStatus();
                _facts[c]->first.setInitial();
            }
        } else {
            throw std::runtime_error("Syntax error in initial facts");
        }
    }
}

void Parser::convertToRPN(std::string &expression)
{
    std::stack<char> s;
    std::string postfix;
    for (auto tok : expression) {
        if (std::isupper(tok)) {
            postfix += tok;
        } else if (tok == '(') {
            s.emplace(tok);
        } else if (tok == ')') {
            while (!s.empty()) {
                tok = s.top();
                s.pop();
                if (tok == '(') {
                    break;
                }
                postfix += tok;
            }
        } else {
            while (!s.empty() && precedence(tok) <= precedence(s.top())) {
                postfix += s.top();
                s.pop();
            }
            s.emplace(tok);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    expression = postfix;
}

int Parser::precedence(char x)
{
    if (x == '(') {
        return 0;
    } else if (x != '!') {
        return 1;
    }
    return 2;
}
