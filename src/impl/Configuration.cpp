#include "../headers/Configuration.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <yaml-cpp/yaml.h>

void YamlReadSettingsSection(YAML::Node yamlSettingsNode, Settings& settingsObject);

Configuration::Configuration(){
    std::filesystem::path configFile;
    try{
        configFile = getStandardConfigFile();
    } catch (std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        return; // Defaults are defined in class header
    }

    if(not std::filesystem::exists(configFile)){
        std::cerr << "Config file non existent. Using default configuration" << std::endl;
        return;
    }

    YAML::Node configYaml = YAML::LoadFile(configFile);

    YamlReadSettingsSection(configYaml["settings"],this->settings);

}

std::string Configuration::getFileEditor(){
    return this->settings.editor;
}

void YamlReadSettingsSection(YAML::Node yamlSettingsNode, Settings& settingsObject){
    if(not yamlSettingsNode){
        std::clog << "Settings section not in config file" << std::endl;
        return;
    }

    if(not yamlSettingsNode["editor"]){
        std::clog << "  Using default editor: nano" << std::endl;
    }
    else
        settingsObject.editor = yamlSettingsNode["editor"].as<std::string>();

}

// Looks for the configuration file in standard locations. Does not check the existence of the file
std::filesystem::path Configuration::getStandardConfigFile(){
    const char* xdgConfigHome = std::getenv("XDG_CONFIG_HOME");

    if(xdgConfigHome){
        return std::filesystem::path(xdgConfigHome) / "dotnote" / "config.yaml";
    }
    // XDG_CONFIG_HOME not set
    const char* home = std::getenv("HOME");

    if(home)
        return std::filesystem::path(home) / ".config" / "dotnote" / "config.yaml";
    // HOME not set

    throw std::runtime_error("Couldn't locate config file, using default configuration");

}
