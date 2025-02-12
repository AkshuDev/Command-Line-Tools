#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

std::string read_binary_file(const std::string &path, std::streampos seekPos, bool error=true) {
    std::ifstream file(path, std::ios::binary);

    // Check if file is open
    if (!file.is_open()) {
        std::string error_1 = "File is not opened successfully! CODE: CLT#src#windows#binReader#read_binary_file#001";
        if (error) {
            std::cerr << error_1 << std::endl;
        }
        return error_1;
    }

    // Do stuff
    file.seekg(0, std::ios::end);
    std::streampos fileSize1 = file.tellg();
    file.seekg(0, std::ios::beg);
    std::streampos fileSize = fileSize1 - seekPos;

    if (fileSize <= 0){
        std::string error_2 = "Seek Position is beyond file Size. CODE: CLT#src#windows#binReader#read_binary_file#002";
        if (error){
            std::cerr << error_2 << std::endl;
        }

        return error_2;
    }

    std::vector<char> buffer(fileSize);


    file.seekg(seekPos);
    file.read(buffer.data(), fileSize);

    file.close();

    std::string result(buffer.begin(), buffer.end());

    return result;
}

int main(int argc, char** argv){
    return 0;
}