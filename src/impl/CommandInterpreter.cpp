#include "../headers/CommandInterpreter.hpp"
#include <iostream>
#include <string>
#include <vector>

void CommandInterpreter::Execute(const std::vector<std::string>& arguments){
    const std::string& first_argument = arguments.front();

    if( arguments.size() == 0
     || first_argument   == "--help"){
        PrintUsage();
        return;
    }

    if(first_argument == "new"){
        ActionNewNote(arguments);
        return;
    }

    if(first_argument == "search"){
        ActionSearchNote(arguments);
        return;
    }

    if(first_argument == "rm"){
        ActionRemoveNote(arguments);
        return;
    }

    if(first_argument == "edit"){
        ActionEditNote(arguments);
        return;
    }

    if(first_argument == "add"){
        ActionAddNote(arguments);
        return;
    }

    // Not known command

    std::cerr << "Bad usage: the command " << first_argument << " is not known." << std::endl;
    PrintUsage();
}



void CommandInterpreter::PrintUsage(){
    const char *USAGE_STR =
        "Usage: .note [command] [-[flags]] [path]\n"
        "Commands available are:\n"
        "\tnew\n"
        "\tsearch\n"
        "\tadd\n"
        "\trm\n"
        "\tedit\n"
        "For more information consult the man pages (man dotnote)\n";
    std::cout << USAGE_STR << std::endl;
    return;
}

void CommandInterpreter::ActionAddNote(const std::vector<std::string>& arguments){
    std::cout << "Adding notes not implemented" << std::endl;
}

void CommandInterpreter::ActionRemoveNote(const std::vector<std::string>& arguments){
    std::cout << "Removing notes not implemented" << std::endl;
}

void CommandInterpreter::ActionEditNote(const std::vector<std::string>& arguments){
    std::cout << "Editing notes not implemented" << std::endl;
}

void CommandInterpreter::ActionNewNote(const std::vector<std::string>& arguments){
    std::cout << "Creating notes not implemented" << std::endl;
}

void CommandInterpreter::ActionSearchNote(const std::vector<std::string>& arguments){
    std::cout << "Searching notes not implemented" << std::endl;
}

