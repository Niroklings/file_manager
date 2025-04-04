#include "FileManager.h"
#include "helpers.h"
#include <fstream>

FileManager::FileManager() : current_path(fs::current_path()) {}

void FileManager::run() {
    std::string command;
    while (true) {
        display_current_directory();
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command.empty()) continue;

        if (command == "exit" || command == "quit") {
            break;
        } else if (command == "ls" || command == "dir") {
            list_directory();
        } else if (command == "pwd") {
            std::cout << current_path << std::endl;
        } else if (command.substr(0, 2) == "cd") {
            change_directory(command.substr(3));
        } else if (command.substr(0, 5) == "mkdir") {
            create_directory(command.substr(6));
        } else if (command.substr(0, 6) == "rmdir") {
            remove_directory(command.substr(7));
        } else if (command.substr(0, 4) == "rm ") {
            remove_file(command.substr(3));
        } else if (command.substr(0, 4) == "cp ") {
            size_t space_pos = command.find(' ', 4);
            if (space_pos != std::string::npos) {
                copy_file(command.substr(3, space_pos - 3), command.substr(space_pos + 1));
            } else {
                std::cout << "Invalid cp command format. Use: cp source destination" << std::endl;
            }
        } else if (command.substr(0, 4) == "cat ") {
            view_file(command.substr(4));
        } else if (command == "help") {
            display_help();
        } else {
            std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
        }
    }
}

void FileManager::display_current_directory() const {
    std::cout << "\nCurrent directory: " << current_path << "\n";
}

void FileManager::list_directory() const {
    std::cout << "\nContents of " << current_path << ":\n";
    std::cout << std::left << std::setw(40) << "Name" << std::setw(15) << "Type" << "Size\n";
    std::cout << std::string(70, '-') << std::endl;

    for (const auto& entry : fs::directory_iterator(current_path)) {
        try {
            std::string type = entry.is_directory() ? "Directory" : "File";
            std::string size = entry.is_directory() ? "" : std::to_string(entry.file_size()) + " bytes";
            std::cout << std::left << std::setw(40) << entry.path().filename().string() 
                      << std::setw(15) << type << size << std::endl;
        } catch (const fs::filesystem_error& e) {
            std::cout << "Error accessing: " << entry.path().filename() << " - " << e.what() << std::endl;
        }
    }
}

void FileManager::change_directory(const std::string& path) {
    try {
        fs::path new_path = path.empty() ? current_path.root_path() : current_path / path;
        if (fs::exists(new_path) && fs::is_directory(new_path)) {
            current_path = fs::canonical(new_path);
        } else {
            std::cout << "Directory not found: " << new_path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error changing directory: " << e.what() << std::endl;
    }
}

void FileManager::create_directory(const std::string& dir_name) {
    try {
        fs::path dir_path = current_path / dir_name;
        if (fs::create_directory(dir_path)) {
            std::cout << "Directory created: " << dir_path << std::endl;
        } else {
            std::cout << "Directory already exists or couldn't be created: " << dir_path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error creating directory: " << e.what() << std::endl;
    }
}

void FileManager::remove_directory(const std::string& dir_name) {
    try {
        fs::path dir_path = current_path / dir_name;
        if (fs::remove_all(dir_path) > 0) {
            std::cout << "Directory removed: " << dir_path << std::endl;
        } else {
            std::cout << "Directory not found or couldn't be removed: " << dir_path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error removing directory: " << e.what() << std::endl;
    }
}

void FileManager::remove_file(const std::string& file_name) {
    try {
        fs::path file_path = current_path / file_name;
        if (fs::remove(file_path)) {
            std::cout << "File removed: " << file_path << std::endl;
        } else {
            std::cout << "File not found or couldn't be removed: " << file_path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error removing file: " << e.what() << std::endl;
    }
}

void FileManager::copy_file(const std::string& source, const std::string& destination) {
    try {
        fs::path source_path = current_path / source;
        fs::path dest_path = current_path / destination;

        if (!fs::exists(source_path)) {
            std::cout << "Source file not found: " << source_path << std::endl;
            return;
        }

        if (fs::is_directory(dest_path)) {
            dest_path /= source_path.filename();
        }

        fs::copy(source_path, dest_path, fs::copy_options::overwrite_existing);
        std::cout << "File copied from " << source_path << " to " << dest_path << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error copying file: " << e.what() << std::endl;
    }
}

void FileManager::view_file(const std::string& file_name) {
    try {
        fs::path file_path = current_path / file_name;
        if (!fs::exists(file_path)) {
            std::cout << "File not found: " << file_path << std::endl;
            return;
        }

        if (fs::is_directory(file_path)) {
            std::cout << "Cannot view directory as file: " << file_path << std::endl;
            return;
        }

        std::ifstream file(file_path);
        if (file.is_open()) {
            std::cout << "\nContents of " << file_path << ":\n";
            std::cout << std::string(70, '-') << std::endl;
            std::string line;
            while (std::getline(file, line)) {
                std::cout << line << std::endl;
            }
            file.close();
        } else {
            std::cout << "Could not open file: " << file_path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error viewing file: " << e.what() << std::endl;
    }
}

void FileManager::display_help() const {
    std::cout << "\nAvailable commands:\n";
    std::cout << "ls, dir       - List directory contents\n";
    std::cout << "pwd           - Show current directory\n";
    std::cout << "cd <path>     - Change directory\n";
    std::cout << "mkdir <name>  - Create directory\n";
    std::cout << "rmdir <name>  - Remove directory\n";
    std::cout << "rm <name>     - Remove file\n";
    std::cout << "cp <src> <dst> - Copy file\n";
    std::cout << "cat <file>    - View file contents\n";
    std::cout << "help          - Show this help\n";
    std::cout << "exit, quit    - Exit program\n";
}