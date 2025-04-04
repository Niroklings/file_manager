#pragma once
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class FileManager {
public:
    FileManager();
    void run();

private:
    fs::path current_path;

    void display_current_directory() const;
    void list_directory() const;
    void change_directory(const std::string& path);
    void create_directory(const std::string& dir_name);
    void remove_directory(const std::string& dir_name);
    void remove_file(const std::string& file_name);
    void copy_file(const std::string& source, const std::string& destination);
    void view_file(const std::string& file_name);
    void display_help() const;
};