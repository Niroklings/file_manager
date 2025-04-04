#include "FileManager.h"
#include <iostream>

int main() {
    std::cout << "Simple File Manager - C++\n";
    std::cout << "Type 'help' for available commands\n";

    FileManager manager;
    manager.run();

    return 0;
}