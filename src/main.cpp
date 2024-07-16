#include "headers/CommandInterpreter.hpp"
#include <string>
#include <vector>

int main(int argc, char** argv){   
    std::vector<std::string> arguments;
    for(int i = 1; i < argc; i++){
        arguments.push_back(argv[i]);
    }

    CommandInterpreter::Execute(arguments);
    return 0;
}
