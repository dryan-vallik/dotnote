#ifndef H_REPO_MODIFIER
#define H_REPO_MODIFIER

#include <ctime>
#include <filesystem>
#include <vector>
#include <string>

// Method of adding a note to the repository
enum class AddingMethod{
    // A symlink to the original location will be created
    SYMLINK,
    // The note will be copied over to the repository
    COPY
};

class RepoModifier{
public:
    explicit RepoModifier(const std::filesystem::path& repository_directory);

    // Creates a new note with the name specified
    std::filesystem::path NewNote(const std::string& name) const;

    // Edits the note with the name specified
    std::filesystem::path EditNote(const std::string& name) const;

    // Removes the note with the name specified
    void RemoveNote(const std::string& name) const;

    // Deletes all notes that were created before maximum_creation_date
    void RemoveNote(std::time_t maximum_creation_date) const;

    // Adds an existing note into the repository using the desired method
    std::filesystem::path AddNote(const std::filesystem::path& location, AddingMethod adding_method) const;

    // Filters existing notes using the query
    std::vector<std::filesystem::path> SearchNotes(const std::string& query) const;

private:
    // Directory of the note repository
    std::filesystem::path m_directory;
    
};

#endif // H_REPO_MODIFIER
