#include "../headers/RepoModifier.hpp"
#include "../headers/Configuration.hpp"
#include "../headers/ERROR_CODES.hpp"
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

RepoModifier::RepoModifier(const fs::path& directory){
    this->m_directory = directory;
}

fs::path RepoModifier::NewNote(const std::string& name) const{
    std::ofstream new_note(m_directory / name);

    if(not new_note){
        std::cerr << ".note new: Unknown failure when creating the note, make sure you have write permision over the repository." << name << std::endl;
        throw E_UNKNOWN;
    }

    new_note.close();

    return m_directory / name;
}

void RepoModifier::EditNote(const std::string& name) const {
    if(not fs::exists(m_directory/name)){
        std::cerr << ".note edit: Note doesn't exists." << std::endl;
        throw E_NOT_FOUND;
    }

    Configuration config;
    const std::string editor = config.getFileEditor();

    execl(editor.c_str(), editor.c_str(), (m_directory/name).c_str(), NULL);

    std::cerr   << ".note edit: Failed to execute editor. Make sure the editor in the configuration is valid.\n"
                << "\tCommand attempted to execute: " << editor << ' ' << (m_directory/name).c_str() << std::endl;

    throw E_BAD_CONFIG;

}

void RepoModifier::RemoveNote(const std::string& name) const {
    if(not fs::remove(m_directory/name)){
        throw E_NOT_FOUND;
    }
}

void RepoModifier::RemoveNote(std::time_t maximum_creation_date) const {
    throw E_NOT_IMPLEMENTED;
}

fs::path RepoModifier::AddNote(const std::filesystem::path& location, AddingMethod adding_method) const {

    if(not fs::exists(location)){
        throw E_NOT_FOUND;
    }

    if(not fs::is_regular_file(location)){
        throw E_BAD_FILE;
    }

    const auto note_location = m_directory / location.filename();

    if(adding_method == AddingMethod::SYMLINK){
        fs::create_symlink(location, note_location);
    }
    else{ // Copy method selected
        fs::copy_file(location, note_location);
    }

    return note_location;
}

bool match_query(const std::string& query, const std::string& string){
    if(std::string::npos != string.find(query)) // Found
        return true;

    return false;
}

std::vector<fs::path> RepoModifier::SearchNotes(const std::string& query) const{
    std::vector<fs::path> results;
    
    for(const auto& file : fs::recursive_directory_iterator(m_directory)){
        
        const fs::path file_path = file.path();

        if(file.is_directory())
            continue;

        std::string note_name = file_path.filename().string();

        if(match_query(query, note_name)){
            results.push_back(file_path);
            continue;
        }

        if(not file.is_symlink())
            continue;

        fs::path symlink_path = fs::read_symlink(file_path);

        if(not fs::exists(symlink_path)){
            std::clog << "WARNING: Broken symlink: " << note_name << std::endl;
            continue;
        }

        note_name = symlink_path.filename().string();

        if(match_query(query, note_name)){
            results.push_back(file_path);
            continue;
        }

    }
    return results;
}
