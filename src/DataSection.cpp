#include "../include/DataSection.h"

extern bool DEBUG;

DataSection::DataSection() {
    // Nothing todo
}

void DataSection::display() {
    bool headerAdded = false;
    for(int i = 0; i < this->points.size(); i++) {
        // Print the header with different style
        while (this->layers[i] == 0) {
            // Adds the header points
            std::cout << this->points[i];

            // Determine if this is the last header point
            if (this->layers.size() >= i + 1 && this->layers[i + 1] == 0) {
                std::cout << ", ";
            }
            i++;
        }
        // After header is added, add the endline
        if (!headerAdded) {
            headerAdded = true;
            std::cout << std::endl;
        }

        // Print initial spaces
        int totalSpaces = this->layers[i] * OUTPUT_SPACES - 1;
        for(int j = 0; j < totalSpaces; j++) {
            std::cout << " ";
        }
        // Add bullet point
        std::cout << OUTPUT_BULLET << " ";

        // Add data
        std::cout << this->points[i] << std::endl;
    }
}

std::string& DataSection::formatPoint(std::string& point) {
    // Removes starting spaces
    int startIndex = 0, size = point.size();
    for(int i = 0; i < point.size(); i++) {
        if (point[i] == ' ') {
            startIndex++;
            continue;
        }
        if (point[i] == ':') {
            startIndex++;
            continue;
        }
        break;
    }

    // Remove trailing characters
    for(int i = size - 1; i > 0; i--) {
        if (point[i] == ' ' || point[i] == '\n') {
            size--;
            continue;
        }
        break;
    }
    point = point.substr(startIndex, size);
    return point;
}

void DataSection::addPoint(std::string& point, int layer) {
    this->formatPoint(point);

    if (point.size() == 0) {
        return;
    }

    // Check that the layer can only be increased by 1 from the previous element
    if (layers.size() != 0) {
        if (layer > layers[layers.size() - 1] + 1) {
            layer = layers[layers.size() - 1] + 1;
        }
    }

    this->points.push_back(point);
    this->layers.push_back(layer);
}

void DataSection::clear() {
    this->layers.clear();
    this->points.clear();
}

bool DataSection::isEmpty() {
    if (this->points.size() == 0) {
        return true;
    }
    return false;
}

DataSection::~DataSection() {
    // Nothing todo
}

