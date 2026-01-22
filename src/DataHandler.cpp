#include "DataHandler.h"

extern bool DEBUG;

DataHandler::DataHandler(std::string const& path) {
    mPath = path;
}

std::vector<DataFile> DataHandler::readFiles() {
    FileHandler handler;
    return handler.read(mPath);
}

bool DataHandler::isDuplicate(std::vector<int> const& previouslyDisplayed, int fileNo) {
    // Loop through each entry in the list
    for(size_t i = 0; i < previouslyDisplayed.size(); i++) {
        // Check against previous displays
        if (fileNo == previouslyDisplayed[i]) {
            return true;
        }
    }
    return false;
}

int DataHandler::isFilename(std::string const& filename) {
    // Loop through each entry in the list
    auto dataFiles = readFiles();
    for (size_t i = 0; i < dataFiles.size(); i++) {
        std::string saved = dataFiles[i].getFilename();
        if (filename == saved) {
            // Account for difference between loop vs user input
            return i + 1;
        }
    }
    return 0;
}

void DataHandler::display(std::string const& filename) {
    std::cout << std::endl;
    // User wants to exit
    if (filename == "0") {
        return;
    }

    // For printing all datafiles
    auto dataFiles = readFiles();
    if (filename.length() == 0) {
        for(DataFile& dataFile : dataFiles) {
            dataFile.display();
            std::cout << std::endl << std::endl;
        }
        return;
    }

    // For finding and printing a single datafile

    // If user enters a number option
    size_t userVal;
    try {
        userVal = std::stoull(filename);
    } catch(std::invalid_argument& e) {
        userVal = 0;
    }
    
    if (userVal) {
        userVal--;
        if (userVal < dataFiles.size()) {
            dataFiles[userVal].display();
            return;
        }
    }

    // If user enters a filename
    for (DataFile& dataFile : dataFiles) {
        if (filename == dataFile.getFilename()) {
            dataFile.display();
            return;
        }
    }
    std::cout << "Could not show any files..." << std::endl;
}

void DataHandler::display(std::vector<std::string> const& filenames) {
    // Prevents same file from being displayed multiple times
    std::vector<int> previouslyDisplayed;

    // Loop through inputted filenames to check for duplicates
    for(size_t i = 0; i < filenames.size(); i++) {
        // Break after exit
        if (filenames[i] == "0") {
            break;
        }
        
        // Check if value is a number
        int fileNo = 0;
        try {
            fileNo = stoi(filenames[i]);
        }
        catch (std::invalid_argument& e) {
            fileNo = 0;
        }
        
        // Check ints
        if (fileNo) {
            if (!this->isDuplicate(previouslyDisplayed, fileNo)) {
                previouslyDisplayed.push_back(fileNo);
                this->display(filenames[i]);
            }
        }
        // Check strings
        else {
            std::string file = filenames[i];
            int index = this->isFilename(file);
            if (index && !this->isDuplicate(previouslyDisplayed, index)) {
                previouslyDisplayed.push_back(index);
                this->display(file);
            }
        }
    }
}

void DataHandler::displayFilenames() {
    std::vector<DataFile> dataFiles = readFiles();
    int i = 1;
    for (DataFile& dataFile : dataFiles) {
        std::cout << i++ << ". " << dataFile.getFilename() << std::endl;
    }
    std::cout << CODE_EXIT << ". Exit" << std::endl;
    std::cout << std::endl;
}

DataHandler::~DataHandler() {
    // Nothing todo
}

