#ifndef H_S_SETTINGS
#define H_S_SETTINGS

#include <filesystem>
#include <string>

struct Settings{
    std::string editor = "nano";
    std::filesystem::path repository = "~/.note.d/";
};

#endif // H_S_SETTINGS
