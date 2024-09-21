#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "DataFile.h"
#include "FileHandler.h"

class DataHandler {
private:
    std::vector<DataFile> dataFiles;

    // Returns if item is a duplicate
    bool isDuplicate(std::vector<int> const& previouslyDisplayed, int fileNo);

    // Returns index of item if it is a duplicate
    int isFilename(std::vector<int> const& previouslyDisplayed, std::string const& filename);

public:
    DataHandler(std::string const& path);

    void display(std::string const& filename = "");
    void display(std::vector<std::string> const& filenames);
    void displayFilenames();

    ~DataHandler();
};

