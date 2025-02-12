#include <iostream>
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <variant>

std::string read_binary_file(std::string characterSet, std::string path, bool error=true) {
    ifstream file(path);

    // Check if file is open
    if (!file.is_open() {
        std::string error = "File is not opened successfully! CODE: CLT#src#windows#binReader#11";
        if (error) {
            std::cerr << error << std::endl;
        }
        return error;
    })

    std::string content;
    std::string line;

    // Read Each Line
    while (getline(file, line)) {
        content += line;
    }

    file.close();

    return content;
}