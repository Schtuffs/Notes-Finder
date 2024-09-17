#include "../include/DataHandler.h"

DataHandler::DataHandler(std::string path) {
    FileHandler fileHandler;
    this->dataFiles = fileHandler.read(path);
}

void DataHandler::diplay() {
    std::cout << std::endl;
    
    // For printing all datafiles
    for(DataFile& dataFile : this->dataFiles) {
        dataFile.display();
        std::cout << std::endl << std::endl;
    }
}

DataHandler::~DataHandler() {
    // Nothing todo
}

