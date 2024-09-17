#include <iostream>

#include "../include/FileHandler.h"

FileHandler::FileHandler() {
    // Nothing todo
}

std::vector<DataFile> FileHandler::read(std::string const& path) {
    // Starts by reading file names in path
    std::vector<std::string> filenames = this->readFileNames(path);
    std::cout << "Found " << filenames.size() << " files..." << std::endl;

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

std::vector<std::string> FileHandler::readFileNames(std::string const& path) {
    std::vector<std::string> filenames;
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
    return filenames;
}

DataFile FileHandler::open(std::string const& path, std::string& filename) {
    std::ifstream file;
    DataFile dataFile(filename);

    file.open(path + filename);
    if (!file.is_open()) {
        std::cout << "Could not open file..." << std::endl;
        return dataFile;
    }

    std::string contents;
    DataSection dataSection;
    int reads = 0;
    while(getline(file, contents)) {
        // D
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

int FileHandler::parse(DataSection& dataSection, std::string& line) {
    int layer = 0;
    std::istringstream linestream(line);
    std::string data;
    

    // Deals with empty line
    if (line.size() == 0) {
        return PARSE_EMPTY;
    }

    // Deals with line being a section header
    if (line[0] == ':') {
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

    getline(linestream, data);
    // Deals with actual datapoints (lines that have '-'). Reads until space 
    for(int i = 0; i < data.length(); i++) {
        if (data[i] == '-') {
            layer++;
            continue;
        }
        break;
    }

    // Set file to after the formatting, then get the line and add it to the dataSection
    data = data.substr(layer, data.length());
    dataSection.addPoint(data, layer);

    return PARSE_LINE;
}

FileHandler::~FileHandler() {
    // Nothing todo
}

