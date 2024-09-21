#include "../include/DataSection.h"

extern bool DEBUG;

DataSection::DataSection() {
    // Nothing todo
}

void DataSection::display() {
    // Checks this datasection 
    bool headerAdded = false;
    for(int i = 0; i < this->points.size(); i++) {
        // Print the header with different style
        if (i == 0) {
            std::cout << this->points[0] << std::endl;
            continue;
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

int DataSection::parse(std::string const& line) {
    int layer = PARSE_ERROR;
    // Deals with empty line
    
    if (line.size() == 0) {
        return PARSE_EMPTY;
    }

    // Deals with line being a section header
    if (line[0] != '-') {
        return PARSE_HEADER;
    }

    // Deals with actual datapoints (lines that have '-'). Reads until space 
    layer = 0;
    for(int i = 0; i < line.length(); i++) {
        // Increase layer until not hyphen found
        if (line[i] != '-') {
            break;
        }
        layer++;
    }

    
    return layer;
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
        if (point[i] == '-') {
            startIndex++;
            continue;
        }
        break;
    }

    // Remove trailing characters
    for(int i = size - 1; i > 0; i--) {
        if (point[i] == ' ') {
            size--;
            continue;
        }
        if (point[i] == '\n') {
            size--;
            continue;
        }
        break;
    }
    point = point.substr(startIndex, size);
    return point;
}

int DataSection::add(std::string& point) {
    // Parse point data
    int layer = this->parse(point);

    // Ignore if error
    if (layer == PARSE_ERROR) {
        return ADD_FAILURE;
    }

    if (layer == PARSE_EMPTY) {
        return ADD_EMPTY;
    }

    // Format the point
    this->formatPoint(point);

    // Check point still exists
    if (point.size() == 0) {
        return ADD_EMPTY;
    }

    // Check if this is first item, forces to be header
    if (this->layers.size() == 0) {
        layer = LAYER_HEADER;
    }
    // Otherwise, check formatting
    else {
        // Check if item is a header when it shouldn't be
        if (layer == PARSE_HEADER) {
            layer = 1;
        }

        // Check that the layer can only be increased by 1 from the previous element
        if (layer > this->layers[this->layers.size() - 1] + 1) {
            layer = this->layers[this->layers.size() - 1] + 1;
        }
    }

    this->points.push_back(point);
    this->layers.push_back(layer);

    return ADD_SUCCESS;
}

void DataSection::clear() {
    this->layers.clear();
    this->points.clear();
}

bool DataSection::isEmpty() {
    // Checks that there are points in the section at all
    if (this->points.size() == 0) {
        return true;
    }

    // Ensures theres more than just a header
    for(int i = 0; i < this->layers.size(); i++) {
        if (this->layers[i] != LAYER_HEADER) {
            if (this->points[i].size() == 0) {
                return true;
            }
        }
    }
    return false;
}

DataSection::~DataSection() {
    // Nothing todo
}

