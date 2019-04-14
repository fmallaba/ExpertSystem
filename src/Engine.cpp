//
// Created by Furkat MALLABAEV on 2019-04-06.
//

#include "Engine.hpp"
#include <iostream>
#include "Solver.hpp"

void Engine::run()
{
    Solver solver(_loop);
    _parser.parse_file();

    auto queries = _parser.getQueries();
    auto facts = _parser.getFacts();

    for (auto c : queries) {
        auto it = facts.find(c);
        if (it == facts.end()) {
            throw std::runtime_error("Unknown query: " + std::string(1, c));
        }

        std::cout << "Find query: " << c << std::endl;
        if (!it->second->first.isInitial()) {
            solver.solveExpression(it->second, facts);
        } else {
            std::cout << "Query " << c << " initial true" << std::endl;
        }
        std::cout << std::endl;
    }

    print_results(queries, facts);
}

void Engine::print_results(Queries queries, Facts facts)
{
    for (auto c : queries) {
        std::cout << facts[c]->first.getLabel() << " = "
                  << ((facts[c]->first) ? "TRUE" : "FALSE") << std::endl;
    }
}
