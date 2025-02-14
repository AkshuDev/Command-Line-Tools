#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

// Function to append data to a binary file
// Parameters:
// - path: The path to the binary file
// - data: The data to append to the file
// - error: Flag to indicate whether to print error messages
// Returns: True if the append operation was successful, false otherwise
bool append_binary_file(const std::string &path, const std::vector<char> &data, bool error=true) {
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
bool delete_binary_file(const std::string &path, bool error=true) {
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
bool copy_binary_file(const std::string &source, const std::string &destination, bool error=true) {
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
bool move_binary_file(const std::string &source, const std::string &destination, bool error=true) {
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
std::streampos get_binary_file_size(const std::string &path, bool error=true) {
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
bool write_binary_file(const std::string &path, const std::vector<char> &data, bool error=true) {
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
std::string read_binary_file(const std::string &path, std::streampos seekPos=0, bool error=true) {
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

int main(int argc, char* argv[]) {
    std::string path;
    std::string content;
    bool error = true;
    int seek = 0;
    int bufferSize = 1024;
    int mode = 0;
    bool convert = false;
    std::string convertion;

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-f" && i + 1 < argc) {
                path = argv[++i];
            } else if (arg == "-error:false") {
                error = false;
            } else if (arg == "-error:true") {
                error = true;
            } else if (arg == "-buffer-size" && i + 1 < argc) {
                bufferSize = std::stoi(argv[++i]);
            } else if (arg == "-r") {
                mode = 1;
            } else if (arg == "-w" && i + 1 < argc) {
                mode = 2;
                content = argv[++i];
            } else if (arg == "-a" && i + 1 < argc) {
                mode = 3;
                content = argv[++i];
            } else if (arg == "-seek" && i + 1 < argc) {
                seek = std::stoi(argv[++i]);
            } else if (arg == "-copy" && i + 2 < argc) {
                mode = 4;
                path = argv[++i];
                content = argv[++i]; // Using content to store destination path
            } else if (arg == "-move" && i + 2 < argc) {
                mode = 5;
                path = argv[++i];
                content = argv[++i]; // Using content to store destination path
            } else if (arg == "-delete" && i + 1 < argc) {
                mode = 6;
                path = argv[++i];
            } else if (arg == "-size" && i + 1 < argc) {
                mode = 7;
                path = argv[++i];
            } else if (arg == "-convert" && i + 1 < argc) {
                convertion = argv[++i];
                convert = true;
            }
        }

        switch (mode) {
            case 1: {
                std::string result = read_binary_file(path, seek, error);
                std::cout << result << std::endl;
                break;
            }
            case 2: {
                std::vector<char> data(content.begin(), content.end());
                if (write_binary_file(path, data, error)) {
                    std::cout << "Write Successful!" << std::endl;
                } else {
                    std::cout << "Write Failed!" << std::endl;
                }
                break;
            }
            case 3: {
                std::vector<char> data(content.begin(), content.end());
                if (append_binary_file(path, data, error)) {
                    std::cout << "Append Successful!" << std::endl;
                } else {
                    std::cout << "Append Failed!" << std::endl;
                }
                break;
            }
            case 4: {
                if (copy_binary_file(path, content, error)) {
                    std::cout << "Copy Successful!" << std::endl;
                } else {
                    std::cout << "Copy Failed!" << std::endl;
                }
                break;
            }
            case 5: {
                if (move_binary_file(path, content, error)) {
                    std::cout << "Move Successful!" << std::endl;
                } else {
                    std::cout << "Move Failed!" << std::endl;
                }
                break;
            }
            case 6: {
                if (delete_binary_file(path, error)) {
                    std::cout << "Delete Successful!" << std::endl;
                } else {
                    std::cout << "Delete Failed!" << std::endl;
                }
                break;
            }
            case 7: {
                std::streampos size = get_binary_file_size(path, error);
                if (size != -1) {
                    if (!convert) {
                        std::cout << "File Size: " << size << " bytes" << std::endl;
                    } else {
                        std::streampos convertedSize;
                        if (convertion == "KB") {
                            convertedSize = size / 1024;
                        } else if (convertion == "MB") {
                            convertedSize = size / (1024 * 1024);
                        } else if (convertion == "GB") {
                            convertedSize = size / (1024 * 1024 * 1024);
                        } else {
                            std::cerr << "Invalid conversion type!" << std::endl;
                            break;
                        }

                        std::cout << "File Size: " << convertedSize << " " << convertion << std::endl;
                    }
                } else {
                    std::cout << "Failed to get file size!" << std::endl;
                }
                break;
            }
            default:
                std::cerr << "Invalid mode or missing arguments!" << std::endl;
                break;
        }
    } else {
        std::cerr << "Usage: <program> -f <file_path> [options]" << std::endl;
    }

    return 0;
}