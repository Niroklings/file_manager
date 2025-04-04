#pragma once
#include <iostream>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

void print_file_info(const fs::directory_entry& entry);
void print_error(const std::string& operation, const std::exception& e);