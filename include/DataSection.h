#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../include/CONSTANTS.h"

class DataSection {
private:
    // Hold the layer of the point, the points at this layer, and any subpoints contained within
    std::vector<int> layers;
    std::vector<std::string> points;

    std::string& formatPoint(std::string& point);

public:
    DataSection();

    // Shows formatted datasection
    void display();
    
    // Adds point to the datasection
    void addPoint(std::string& point, int layer);

    void clear();

    bool isEmpty();

    ~DataSection();
};

