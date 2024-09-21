#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>

#include "DataFile.h"
#include "../include/CONSTANTS.h"

// Allows for reading of files, and returns the content of said files.
class FileHandler {
private:
    // Reads files in a specified path/folder
    std::vector<std::string> readFileNames(std::string path);
    
    // Open file
    DataFile open(std::string const& path, std::string& filename);

    // Checks file extension
    bool checkExtension(std::string const& filename);

public:
    FileHandler();

    // Receives a filepath and reads all files in the path. Returns all of the read data.
    std::vector<DataFile> read(std::string const& path = "../files/");

    ~FileHandler();
};

