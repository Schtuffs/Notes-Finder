#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../include/CONSTANTS.h"

namespace args {
    void parse(int argc, char* argv[], std::string& path);
    namespace detail {
        static void help();
        static void path(std::string& path, std::vector<std::string>& argv, int index);
        static void debug();
        static void colours();
    }
}

