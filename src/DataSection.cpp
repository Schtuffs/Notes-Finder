#include "../include/DataSection.h"

extern bool DEBUG;

DataSection::DataSection() {
    // Nothing todo
}

void DataSection::setColour(int colour) {
    if (colour == RESET_COLOUR) {
        this->resetColour();
        return;
    }
    

    std::cout << "\033[" << colour << "m";
}

void DataSection::resetColour() {
    std::cout << "\033[0m";
}

void DataSection::display() {
    // Checks this datasection 
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

        // Add print data, parsing for '*'
        this->printPoint(this->points[i]);
    }
}

void DataSection::printPoint(std::string& point) {
    for(int i = 0; i < point.size(); i++) {
        if (point[i] == '*') {
            this->setColour(this->findColour(point, i));
        }
        std::cout << point[i];
    }
    std::cout << std::endl;
    this->resetColour();
}

int DataSection::findColour(std::string& point, int& index) {
    // Increase past the asterick
    index++;
    int startIndex = index;

    std::string textColour = "";
    while(index < point.size()) {
        if (point[index] == ' ') {
            break;
        }
        textColour += point[index];
        index++;
    }

    // Determine which colour was typed

    // First, check if bright colour
    int colour = RESET_COLOUR;
    bool bright = false;
    if (textColour[0] == 'B') {
        colour = BRIGHT;
        textColour = textColour.substr(1);
    }

    // Then check the colour
    bool coloured = false;
    if (textColour == "BLACK") {
        colour += BLACK;
        coloured = true;
    }
    else if (textColour == "RED") {
        colour += RED;
        coloured = true;
    }
    else if (textColour == "GREEN") {
        colour += GREEN;
        coloured = true;
    }
    else if (textColour == "YELLOW") {
        colour += YELLOW;
        coloured = true;
    }
    else if (textColour == "BLUE") {
        colour += BLUE;
        coloured = true;
    }
    else if (textColour == "MAGENTA") {
        colour += MAGENTA;
        coloured = true;
    }
    else if (textColour == "CYAN") {
        colour += CYAN;
        coloured = true;
    }
    else if (textColour == "WHITE") {
        colour += WHITE;
        coloured = true;
    }
    
    // Only returns colour if actual colour is set
    if (coloured) {
        // Increase index to remove printing extra space
        index++;
        return colour;
    }
    // Prevent incorrect colours from deleting data in case of random '*'
    index = startIndex;
    return RESET_COLOUR;
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

