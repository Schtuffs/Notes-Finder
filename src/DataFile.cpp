#include "../include/DataFile.h"

extern bool DEBUG;

DataFile::DataFile(std::string _filename) {
    this->filename = _filename;
}

void DataFile::display() {
    std::cout << "File: " << this->filename << std::endl << std::endl;
    for (DataSection& dataSection : this->sections) {
        dataSection.display();
        std::cout << std::endl;
    }
}

std::string DataFile::getFilename() {
    return this->filename;
}

void DataFile::add(DataSection section) {
    if (!section.isEmpty()) {
        this->sections.push_back(section);
    }
}

bool DataFile::isEmpty() {
    if (this->sections.size() == 0) {
        return true;
    }
    return false;
}

DataFile::~DataFile() {
    // Nothing todo
}

