#include "../headers/RepoModifier.hpp"
#include "../headers/CommandInterpreter.hpp"
#include "../headers/Configuration.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

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
    Configuration config;
    RepoModifier repo(config.getRepoDirectory());

    if(arguments.size() > 3){
        std::cerr << ".note add: Too many arguments." << std::endl;
    }

    AddingMethod add_method = AddingMethod::COPY;
    fs::path original_path = arguments.back();

    if(arguments.at(1) == "-l"){
        add_method = AddingMethod::SYMLINK;
    }

    repo.AddNote(original_path, add_method);
}   

void CommandInterpreter::ActionRemoveNote(const std::vector<std::string>& arguments){
    Configuration config;
    RepoModifier repo(config.getRepoDirectory());

    for(std::string note : arguments)
        repo.RemoveNote(note);

}

void CommandInterpreter::ActionEditNote(const std::vector<std::string>& arguments){
    Configuration config;
    RepoModifier repo(config.getRepoDirectory());

    repo.EditNote(arguments.at(1));
}

void CommandInterpreter::ActionNewNote(const std::vector<std::string>& arguments){
    Configuration config;
    RepoModifier repo(config.getRepoDirectory());

    repo.NewNote(arguments.at(1));
}

void CommandInterpreter::ActionSearchNote(const std::vector<std::string>& arguments){
    Configuration config;
    RepoModifier repo(config.getRepoDirectory());

    // With this method of adding words to the query, we ensure no ending spaces will be in the query, unless specified by the user
    std::string query = arguments.at(1);

    for(size_t i = 2; i < arguments.size(); i++){
        query += ' ';
        query += arguments.at(i);
    }

    std::vector<fs::path> results = repo.SearchNotes(query);

    std::string result;
    for(const fs::path& note : results){
        result = note.filename().string();              
        std::cout << result << '\n';
    }
    std::cout.flush();
}

