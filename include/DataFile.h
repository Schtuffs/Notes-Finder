#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "DataSection.h"

class DataFile {
private:
    std::vector<DataSection> sections;
    std::string filename;

public:
    DataFile(std::string _filename);

    void display();
    std::string getFilename();

    bool add(DataSection section);
    bool isEmpty();

    ~DataFile();
};

