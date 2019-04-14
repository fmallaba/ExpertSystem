#include <iostream>

#include "Engine.hpp"

int main(int ac, char* av[])
{
    bool loops = false;

    if (ac < 2) {
        std::cout << "Usage: expert_system [file_name] [-l]\n";
        return 0;
    } else if (ac == 3) {
        if (av[2] == std::string("-l")) {
            loops = true;
        } else {
            std::cout << "Usage: expert_system [file_name] [-l]\n";
            return 0;
        }
    }

    try {
        Engine eng(av[1], loops);
        eng.run();
    } catch (std::runtime_error& err) {
        std::cout << "ERROR: " << err.what() << std::endl;
    }
    return 0;
}