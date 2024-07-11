#ifndef H_COMMAND_INTERPRETER
#define H_COMMAND_INTERPRETER

#include <string>
#include <vector>
class CommandInterpreter{
public:
    static void Execute(const std::vector<std::string>& arguments);
private:
    static void ActionNewNote(const std::vector<std::string>& arguments);
    static void ActionSearchNote(const std::vector<std::string>& arguments);
    static void ActionRemoveNote(const std::vector<std::string>& arguments);
    static void ActionEditNote(const std::vector<std::string>& arguments);
    static void ActionAddNote(const std::vector<std::string>& arguments);
    static void PrintUsage();
};


#endif //H_COMMAND_INTERPRETER
