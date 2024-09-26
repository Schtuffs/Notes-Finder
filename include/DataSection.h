#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "../include/CONSTANTS.h"

class DataSection {
private:
    // Hold the layer of the point, the points at this layer, and any subpoints contained within
    std::vector<int> layers;
    std::vector<std::string> points;

    int parse(std::string const& line);
    std::string& formatPoint(std::string& point);

    void setColour(int colour);
    void resetColour();
    void printPoint(std::string& point);
    int findColour(std::string& point, int& index);

public:
    DataSection();

    // Shows formatted datasection
    void display();
    
    // Adds point to the datasection
    int add(std::string& point);

    void clear();

    bool isEmpty();

    ~DataSection();
};

