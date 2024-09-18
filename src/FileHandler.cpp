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

    // Remove beginning '\'
    if (filename[0] == '\\') {
        filename = filename.substr(1);
    }
    DataFile dataFile(filename);

    std::string contents;
    DataSection dataSection;
    int reads = 0;
    while(getline(file, contents)) {
        // Determine what kind of data was received in line
        int parsed = this->parse(dataSection, contents);
        switch(parsed) {
        case PARSE_EMPTY:
            dataFile.add(dataSection);
            dataSection.clear();
            break;
        case PARSE_HEADER:
        case PARSE_LINE:
            break;
        }
    }

    dataFile.add(dataSection);

    file.close();
    return dataFile;
}

bool FileHandler::checkExtension(std::string const& filename) {
    int extensionStart = 0;
    // Find where the period is
    for(int i = filename.length() - 1; i >= 0; i--) {
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

int FileHandler::parse(DataSection& dataSection, std::string const& line) {
    int layer = 0;

    // Deals with empty line
    if (line.size() == 0) {
        return PARSE_EMPTY;
    }

    // Deals with line being a section header
    if (line[0] == ':') {
        std::string data;
        std::istringstream linestream(line);
        while (getline(linestream, data, ':')) {
            if (data.length() != 0) {
                dataSection.addPoint(data, layer);
            }
            
            if (linestream.tellg() > line.length() || linestream.tellg() < 0) {
                break;
            }
        }
        return PARSE_HEADER;
    }

    // Deals with actual datapoints (lines that have '-'). Reads until space 
    for(int i = 0; i < line.length(); i++) {
        if (line[i] == '-') {
            layer++;
            continue;
        }
        break;
    }

    // Set file to after the formatting, then get the line and add it to the dataSection
    std::string data = line.substr(layer, line.length());
    dataSection.addPoint(data, layer);

    return PARSE_LINE;
}

FileHandler::~FileHandler() {
    // Nothing todo
}

