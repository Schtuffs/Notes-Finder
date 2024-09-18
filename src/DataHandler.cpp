#include "../include/DataHandler.h"

extern bool DEBUG;

DataHandler::DataHandler(std::string const& path) {
    FileHandler fileHandler;
    this->dataFiles = fileHandler.read(path);
}

void DataHandler::diplay(std::string const& filename) {
    std::cout << std::endl;
    // User wants to exit
    if (filename == "0") {
        return;
    }
    
    // For printing all datafiles
    if (filename.length() == 0) {
        for(DataFile& dataFile : this->dataFiles) {
            dataFile.display();
            std::cout << std::endl << std::endl;
        }
        return;
    }

    // For finding and printing a single datafile

    // If user enters a number option
    int userVal = atoi(filename.c_str());
    if (userVal) {
        userVal--;
        if (0 <= userVal && userVal < this->dataFiles.size()) {
            this->dataFiles[userVal].display();
            return;
        }
    }

    // If user enters a filename
    for (DataFile& dataFile : this->dataFiles) {
        if (filename == dataFile.getFilename()) {
            dataFile.display();
            return;
        }
    }
    std::cout << "Could not show any files..." << std::endl;
}

void DataHandler::displayFilenames() {
    int i = 1;
    for (DataFile& dataFile : this->dataFiles) {
        std::cout << i++ << ". " << dataFile.getFilename() << std::endl;
    }
    std::cout << CODE_EXIT << ". Exit" << std::endl;
    std::cout << std::endl;
}

DataHandler::~DataHandler() {
    // Nothing todo
}

