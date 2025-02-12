#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>

bool write_binary_file(const std::string &path, char data[], bool error=true){
    std::ofstream file(path, std::ios::binary);

    if (!file){
        std::string error_1 = "Issue Opening File. CODE: CLT#src#binIO#write_binary_file#001";
        if (error){
            std::cerr << error_1 << std::endl;
        }

        return false;
    }

    for (int i=0; i < 1000; i++) {
        file.write(data, sizeof(data));
    }

    file.close();
    return true;
}

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
    int bufferSize=1024;

    int mode = 1;

    if (argc > 1) {
        for (int cmd; cmd <= argc; cmd++){
            if (argv[cmd] == "-f"){
                try{
                    path = argv[cmd + 1];
                } catch (const std::exception &e) {
                    std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#001\n\n" << e.what() << std::endl;
                    return -991;
                }
            }
            else if (argv[cmd] == "-error:false"){
                error = false;
            }
            else if (argv[cmd] == "-error:true"){
                error = true;
            }
            else if (argv[cmd] == "-buffer-size"){
                try{
                    bufferSize = std::stoi(argv[cmd + 1]);
                } catch (const std::exception &e) {
                    std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#002\n\n" << e.what() << std::endl;
                    return -992;
                }
            }
            else if (argv[cmd] == "-r"){
                mode = 1;
            }
            else if (argv[cmd] == "-w"){
                mode = 2;
                try{
                    path = argv[cmd + 1];
                } catch (const std::exception &e) {
                    std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#002\n\n" << e.what() << std::endl;
                    return -992;
                }
            }
            else if (argv[cmd] == "-a"){
                mode = 3;
                try{
                    path = argv[cmd + 1];
                } catch (const std::exception &e) {
                    std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#003\n\n" << e.what() << std::endl;
                    return -993;
                }
            }
            else if (argv[cmd] == "-seek"){
                try{
                    seek = std::stoi(argv[cmd + 1]);
                } catch (const std::exception &e) {
                    std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#003\n\n" << e.what() << std::endl;
                    return -993;
                }
            }
            else if (argv[cmd] == "-content"){
                try{
                    content = "";
                    for (int j=cmd;j <= argc; j++){
                        content.append(argv[j]);
                    }

                    break;
                } catch (const std::exception &e) {
                    std::cerr << "Usage: Error\nCODE: CLT#src#binIO#main#003\n\n" << e.what() << std::endl;
                    return -993;
                }
            }
        }

        if (mode == 1){
            std::string return_ = read_binary_file(path, seek, error);

            std::cout << return_ << std::endl;
        } else if (mode == 2) {
            char buffer[bufferSize] = {0};

            strncpy(buffer, content.c_str(), sizeof(buffer) - 1);
            buffer[sizeof(buffer) - 1] = '\0';

            if (write_binary_file(path, buffer, error)) {
                std::cout << "Successfull!" << std::endl;
            } else {
                std::cout << "Failed!" << std::endl;
                return -994;
            }
        }
    }

    return 0;
}