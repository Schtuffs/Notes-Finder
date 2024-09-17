#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "DataFile.h"
#include "FileHandler.h"

class DataHandler {
private:
    std::vector<DataFile> dataFiles;

public:
    DataHandler(std::string path);

    void diplay();

    ~DataHandler();
};

