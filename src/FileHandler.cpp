#include <iostream>

#include "../include/FileHandler.h"

extern bool DEBUG;

FileHandler::FileHandler() {
    // Nothing todo
}

std::vector<DataFile> FileHandler::read(std::string const& path) {
    // Starts by reading file names in path
    std::vector<std::string> filenames = this->readFileNames(path);

    // Debug left for GitHub
    if (DEBUG) {
        std::cout << "Found " << filenames.size() << " files..." << std::endl;
    }

    // Begins creating list of DataFiles
    std::vector<DataFile> dataFiles;
    for(std::string& filename : filenames) {
        DataFile checkFile = this->open(path, filename);

        // Check there is data in the file
        if (!checkFile.isEmpty()) {
            dataFiles.push_back(checkFile);
        }
    }

    return dataFiles;
}

std::vector<std::string> FileHandler::readFileNames(std::string path) {
    std::vector<std::string> filenames;
    
    // Remove the quotes around path if it was added via commandline argument
    if (path[path.length() - 1] == '"') {
        path[path.length() - 1] = '\\';
    }
    try {
        // Debug left for GitHub
        if (DEBUG) {
            std::cout << "Opening directory: " << path << std::endl;
        }

        // Get each filename from the specified path, and add to objects vector
        for(const auto& entry : std::filesystem::directory_iterator(path)) {
            std::string filename = entry.path().string();
            
            // Check if there is more than just filepath
            if (filename <= path) {
                continue;
            }

            // Shrink string to just filename and add to list
            filename = filename.substr(path.length());
            filenames.push_back(filename);
        }
    }
    catch (std::filesystem::filesystem_error e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    return filenames;
}

DataFile FileHandler::open(std::string const& path, std::string& filename) {
    std::ifstream file;
    
    if (!this->checkExtension(filename)) {
        std::cout << "Invalid file extension: " << filename << std::endl;
        return DataFile("<INVALID_EXTENSION>");
    }
    
    file.open(path + filename);
    if (!file.is_open()) {
        std::cout << "Could not open file: " << filename << std::endl;
        return DataFile("<EMPTY_FILE>");
    }

    // Remove beginning '\', sometimes has 1 or 2
    while (filename[0] == '\\') {
        filename = filename.substr(1);
    }

    DataFile dataFile(filename);

    std::string contents;
    DataSection dataSection;
    while(getline(file, contents)) {
        // Determine what kind of data was received in line
        int parsed = dataSection.add(contents);
        if (parsed == ADD_EMPTY) {
            dataFile.add(dataSection);
            dataSection.clear();
        }
    }

    dataFile.add(dataSection);

    file.close();
    return dataFile;
}

bool FileHandler::checkExtension(std::string const& filename) {
    int extensionStart = 0;
    // Find where the period is
    for (int i = filename.length() - 1; i >= 0; i--) {
        if (filename[i] == '.') {
            extensionStart = i;
            break;
        }
    }

    // Create substring with only extension for easy checking
    std::string extension = filename.substr(extensionStart);

    // Hard coded, acceptable file extensions
    // If I add more readable file extensions, easy to add a check
    if (extension == ".txt") {
        return true;
    }

    return false;
}

FileHandler::~FileHandler() {
    // Nothing todo
}

