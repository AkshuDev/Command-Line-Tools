# Command-Line-Tools
CLT or Command Line Tools allows to use as well as include these tools into other projects.

# About
CLT allows users to either use the programs that are pre built in this repository or include them in their code to use their functions. It is a powerful tool and makes sure that users don't spend too much time just to write specific functions that can be done easily by importing the specified file.

# Os Requirement
CLT can runs on multiple Operating Systems but many files are OS specific and there are only available to these OS -

Windows, Linux

# Windows
CLT uses the Windows header file and more to do various tasks that communicates with the OS itself such as making a window, gui, running apps, etc.

# Linux
CLT uses Linux in the same way as Windows.

# Cross Platform
CLT also has cross platform files which can run on any os as long as you build them for the specific os otherwise CLT build folder only offers Windows (.exe) and linux (.elf) pre-built files.

These cross platform files are supposed to work normally on any OS and can be included in any cpp file. These files work cross platform as it doesn't communicate with the OS itself but rather uses pre-made C++ libraries (built in) to do the job. Thanks to this the compiler can build the file in any os executable format and it would work normally.


# How to run

To run any file just open the build folder, then open the folder that matches your Operating System, then run the file you want to run.

If you don't see any folder matching your OS then you will have to Build the file itself. Go to section Building Files.

# How to include

To include any of these files, just open your .cpp file then type at the top '#include <fileName.h>' replace 'fileName' with the file you want to import.

Then during building make sure to add another compiler path 'path_to_CLT_folder/src/h' replace 'path_to_CLT_folder' with the path to the Command Line Tools folder. Also make sure to add the file you are including.

Example:

myFile.cpp ->

    #include <binIO.h>
    #include <iostream>

    int main() {
        std::string path = "myfile.bin";
        std::string content = read_binary_file(path);
        std::cout << content << std::endl;
        return 0;
    }


Build via g++ ->

    (main) $ g++ myFile.cpp -o myFile.exe CLT/src/binIO.cpp -I./CLT/src/h

    (main) $ ./myFile.exe
    
    Hello World!

    (main) $


The main command is broke down as follows ->

g++ -> actual program we are running for build

myFile.cpp -> The main program.

-o myFile.exe -> The output file we want '-o' stands for output.

CLT/src/binIO.cpp -> The linked binIO 'example' file. NOTE: The folder is renamed to CLT.

-I./CLT/src/h -> The added compiler path. '-I' is used for adding compiler path.

# Building the CLT files for custom OS

For building the files, you can use a number of programs. Recommended 'g++' or 'gcc'.

To build the files, you need to take an note that you can only build cross-platform files because the OS specific will require certain libraries to build that are OS specific.


Step 1. Use 'g++' or any compiler to compile every file

Step 2. Set the output to CLT/build/(your OS)/(the filename).(the os executable extension)

Step 3. Do this with every file and done!


g++ ->

    (main) $ g++ CLT/src/binIO.cpp -o CLT/build/MyOS/binIO.myOSexec

    (main) $


This is the meaning of the command ->

g++: The main program we will call.

CLT/src/binIO.cpp: Example Compilation file path.

-o CLT/build/MyOS/binIO.myOSexec: Example output path.