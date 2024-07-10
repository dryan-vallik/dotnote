#ifndef H_CONFIGURATION
#define H_CONFIGURATION


#include <filesystem>
#include <string>

struct Settings{
    std::string editor = "nano";
};

class Configuration{
    public:
        // Builds the configuration
        Configuration();

        std::string getFileEditor();

    private:
        std::filesystem::path getStandardConfigFile();
        Settings settings;
        
};

#endif // H_CONFIGURATION
