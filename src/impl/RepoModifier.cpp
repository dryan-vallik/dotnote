#include "../headers/RepoModifier.hpp"
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
    std::fstream new_note(m_directory / name);

    if(not new_note){
        std::cerr << ".note new: Unknown failure when creating the note, make sure you have write permision over the repository." << name << std::endl;
        return fs::path();
    }

    new_note.close();

    return m_directory / name;
}

fs::path RepoModifier::EditNote(const std::string& name) const {
    if(fs::exists(m_directory/name))
        return m_directory/name;

    std::cerr << ".note edit: Note doesn't exists." << std::endl;

    return fs::path();
}

void RepoModifier::RemoveNote(const std::string& name) const {
    if(not fs::remove(m_directory/name)){
        std::cout << ".note rm: Note doesn't exist." << std::endl;
    }
}

void RepoModifier::RemoveNote(std::time_t maximum_creation_date) const {
    std::cerr << ".note rm: Removing based on time is not implemented yet." << std::endl;
}

fs::path RepoModifier::AddNote(const std::filesystem::path& location, AddingMethod adding_method) const {

    if(not fs::exists(location)){
        std::cerr << ".note add: Couldn't find any note in " << location.string() << std::endl;
        return fs::path();
    }

    if(not fs::is_regular_file(location)){
        std::cerr << ".note add: File in " << location.string() << " is not a regular file." << std::endl;
        return fs::path();
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



