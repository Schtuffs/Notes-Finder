#include "../include/DataHandler.h"

extern bool DEBUG;

DataHandler::DataHandler(std::string const& path) {
    FileHandler fileHandler;
    this->dataFiles = fileHandler.read(path);
}

bool DataHandler::isDuplicate(std::vector<int> const& previouslyDisplayed, int fileNo) {
    // Loop through each entry in the list
    for(int i = 0; i < previouslyDisplayed.size(); i++) {
        // Check against previous displays
        if (fileNo == previouslyDisplayed[i]) {
            return true;
        }
    }
    return false;
}

int DataHandler::isFilename(std::vector<int> const& previouslyDisplayed, std::string const& filename) {
    bool inList = false;
    // Loop through each entry in the list
    for (int i = 0; i < dataFiles.size(); i++) {
        std::string saved = this->dataFiles[i].getFilename();
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

void DataHandler::display(std::vector<std::string> const& filenames) {
    // Prevents same file from being displayed multiple times
    std::vector<int> previouslyDisplayed;

    // Loop through inputted filenames to check for duplicates
    for(int i = 0; i < filenames.size(); i++) {
        // Break after exit
        if (filenames[i] == "0") {
            break;
        }
        
        // Check if value is a number
        int fileNo = 0;
        try {
            fileNo = stoi(filenames[i]);
        }
        catch (std::invalid_argument e) {
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
            int index = this->isFilename(previouslyDisplayed, filenames[i]);
            if (index && !this->isDuplicate(previouslyDisplayed, index)) {
                previouslyDisplayed.push_back(index);
                this->display(filenames[index]);
            }
        }
    }
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

