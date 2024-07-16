#ifndef H_CONFIGURATION
#define H_CONFIGURATION

#include <filesystem>
#include <string>
#include "Settings.hpp"


class Configuration{
    public:
        // Builds the configuration
        Configuration();
        std::string getFileEditor();
        std::filesystem::path getRepoDirectory();

    private:
        std::filesystem::path getStandardConfigFile();
        Settings m_settings;
        
};

#endif // H_CONFIGURATION
