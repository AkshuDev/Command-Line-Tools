#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

#ifdef _WIN32
    #define CLT_BINIO_LIB __declspec(dllexport)
#elif __linux__
    #define CLT_BINIO_LIB __attribute__((visibility("default")))
#else
    #define CLT_BINIO_LIB
#endif

extern "C" {
    // Function to append data to a binary file
    // Parameters:
    // - path: The path to the binary file
    // - data: The data to append to the file
    // - error: Flag to indicate whether to print error messages
    // Returns: True if the append operation was successful, false otherwise
    CLT_BINIO_LIB bool append_binary_file(const std::string &path, const std::vector<char> &data, bool error=true) {
        std::ofstream file(path, std::ios::binary | std::ios::app);

        if (!file) {
            std::string error_1 = "Issue Opening File for Append. CODE: CLT#src#binIO#append_binary_file#001";
            if (error) {
                std::cerr << error_1 << std::endl;
            }
            return false;
        }

        file.write(data.data(), data.size());
        file.close();
        return true;
    }

    // Function to delete a binary file
    // Parameters:
    // - path: The path to the binary file
    // - error: Flag to indicate whether to print error messages
    // Returns: True if the delete operation was successful, false otherwise
    CLT_BINIO_LIB bool delete_binary_file(const std::string &path, bool error=true) {
        if (std::remove(path.c_str()) != 0) {
            std::string error_1 = "Issue Deleting File. CODE: CLT#src#binIO#delete_binary_file#001";
            if (error) {
                std::cerr << error_1 << std::endl;
            }
            return false;
        }
        return true;
    }

    // Function to copy a binary file
    // Parameters:
    // - source: The path to the source binary file
    // - destination: The path to the destination binary file
    // - error: Flag to indicate whether to print error messages
    // Returns: True if the copy operation was successful, false otherwise
    CLT_BINIO_LIB bool copy_binary_file(const std::string &source, const std::string &destination, bool error=true) {
        std::ifstream src(source, std::ios::binary);
        std::ofstream dest(destination, std::ios::binary);

        if (!src || !dest) {
            std::string error_1 = "Issue Opening Files for Copy. CODE: CLT#src#binIO#copy_binary_file#001";
            if (error) {
                std::cerr << error_1 << std::endl;
            }
            return false;
        }

        dest << src.rdbuf();
        src.close();
        dest.close();
        return true;
    }

    // Function to move a binary file
    // Parameters:
    // - source: The path to the source binary file
    // - destination: The path to the destination binary file
    // - error: Flag to indicate whether to print error messages
    // Returns: True if the move operation was successful, false otherwise
    CLT_BINIO_LIB bool move_binary_file(const std::string &source, const std::string &destination, bool error=true) {
        if (std::rename(source.c_str(), destination.c_str()) != 0) {
            std::string error_1 = "Issue Moving File. CODE: CLT#src#binIO#move_binary_file#001";
            if (error) {
                std::cerr << error_1 << std::endl;
            }
            return false;
        }
        return true;
    }

    // Function to get the size of a binary file
    // Parameters:
    // - path: The path to the binary file
    // - error: Flag to indicate whether to print error messages
    // Returns: The size of the binary file
    CLT_BINIO_LIB std::streampos get_binary_file_size(const std::string &path, bool error=true) {
        std::ifstream file(path, std::ios::binary | std::ios::ate);

        if (!file) {
            std::string error_1 = "Issue Opening File to Get Size. CODE: CLT#src#binIO#get_binary_file_size#001";
            if (error) {
                std::cerr << error_1 << std::endl;
            }
            return -1;
        }

        std::streampos size = file.tellg();
        file.close();
        return size;
    }

    // Function to write data to a binary file
    // Parameters:
    // - path: The path to the binary file
    // - data: The data to write to the file
    // - error: Flag to indicate whether to print error messages
    // Returns: True if the write operation was successful, false otherwise
    CLT_BINIO_LIB bool write_binary_file(const std::string &path, const std::vector<char> &data, bool error=true) {
        std::ofstream file(path, std::ios::binary);

        if (!file) {
            std::string error_1 = "Issue Opening File. CODE: CLT#src#binIO#write_binary_file#001";
            if (error) {
                std::cerr << error_1 << std::endl;
            }
            return false;
        }

        file.write(data.data(), data.size());
        file.close();
        return true;
    }

    // Function to read data from a binary file
    // Parameters:
    // - path: The path to the binary file
    // - seekPos: The position to start reading from
    // - error: Flag to indicate whether to print error messages
    // Returns: The data read from the file as a string, or an error message if the operation failed
    CLT_BINIO_LIB std::string read_binary_file(const std::string &path, std::streampos seekPos=0, bool error=true) {
        std::ifstream file(path, std::ios::binary);

        if (!file.is_open()) {
            std::string error_1 = "File is not opened successfully! CODE: CLT#src#binIO#read_binary_file#001";
            if (error) {
                std::cerr << error_1 << std::endl;
            }
            return error_1;
        }

        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg();
        file.seekg(seekPos, std::ios::beg);

        if (seekPos >= fileSize) {
            std::string error_2 = "Seek Position is beyond file Size. CODE: CLT#src#binIO#read_binary_file#002";
            if (error) {
                std::cerr << error_2 << std::endl;
            }
            return error_2;
        }

        std::vector<char> buffer(fileSize - seekPos);
        file.read(buffer.data(), buffer.size());
        file.close();

        return std::string(buffer.begin(), buffer.end());
    }
}