#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

std::string read_binary_file(const std::string &path, std::streampos seekPos=0, bool error=true) {
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

int main(int argc, char* argv[]){
    std::string path;
    std::string content;
    bool error = true;
    int seek = 0;

    int mode = 1;

    if (argc > 1) {
        for (int cmd; cmd <= argc; cmd++){
            switch (argv[cmd]) {
                case "-f":
                    try{
                        path = argv[cmd + 1];
                    } catch (const std::exception &e) {
                        std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#001\n\n" << e << std::endl;
                        return -991;
                    }
                case "-error:false":
                    error = false;
                case "-error:true":
                    error = true;
                case "-r":
                    mode = 1;
                case "-w":
                    mode = 2;
                    try{
                        path = argv[cmd + 1];
                    } catch (const std::exception &e) {
                        std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#002\n\n" << e << std::endl;
                        return -992;
                    }
                case "-a":
                    mode = 3;
                    try{
                        path = argv[cmd + 1];
                    } catch (const std::exception &e) {
                        std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#003\n\n" << e << std::endl;
                        return -993;
                    }
                case "-seek":
                    try{
                        seek = argc[cmd + 1];
                    } catch (const std::exception &e) {
                        std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#003\n\n" << e << std::endl;
                        return -993;
                    }
                case "-content":
                    try{
                        content = argc[cmd + 1];
                    } catch (const std::exception &e) {
                        std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#003\n\n" << e << std::endl;
                        return -993;
                    }
            }
        }

        if (mode == 1){
            cout << read_binary_file(path, seek, error) << std::endl;
        }
    }

    return 0;
}