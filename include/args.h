#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "CONSTANTS.h"

namespace args {
    void parse(int argc, char* argv[], std::string& path);
    namespace detail {
        void help();
        void path(std::string& path, std::vector<std::string>& argv, int index);
        void debug();
        void colours();
        void recursive();
    }
}

