//
// Created by Furkat MALLABAEV on 2019-04-06.
//

#ifndef EXPERT_SYSTEMS_ENGINE_HPP
#define EXPERT_SYSTEMS_ENGINE_HPP

#include <string>

#include "Parser.hpp"

class Engine {
   public:
    explicit Engine(const std::string &file, bool loop = false)
        : _parser(file), _loop(loop)
    {
    }

    void run();

   private:
    void print_results(Queries queries, Facts facts);
    Parser _parser;
    bool _loop;
};

#endif  // EXPERT_SYSTEMS_ENGINE_HPP
