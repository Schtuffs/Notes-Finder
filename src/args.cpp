#include "../include/args.h"

bool DEBUG = false;

void args::detail::help() {
    std::cout << "-h    shows all commands" << std::endl;
    std::cout << "-p    next argument is the path to find files in" << std::endl;
    std::cout << "-d    debug mode, should do nothing" << std::endl;
    std::cout << std::endl;
}

void args::detail::path(std::string& path, std::vector<std::string>& argv, int index) {
    if (index + 1 >= argv.size()) {
        std::cout << "No specified path given..." << std::endl;
        return;
    }

    // Debug left for GitHub
    if (DEBUG) {
        std::cout << "Path changed to: " << argv[index + 1] << std::endl;
    }
    path = argv[index + 1];
}

void args::detail::debug() {
    std::cout << std::endl << "-----ACTIVATED DEBUG MODE-----" << std::endl << std::endl;
    DEBUG = true;
}

void args::parse(int argc, char* argv[], std::string& path) {
    // Turn argv into strings
    std::vector<std::string> args;

    // Loop for each argument
    for(int i = 1; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }

    // Parse each argument
    for (int i = 0; i < args.size(); i++) {

        // Argument is too short
        if (args[i].length() < 2) {
            continue;
        }
        
        // Continue loop if item isn't an argument
        if (args[i][0] != '-') {
            continue;
        }

        // Determine which argument it is

        // Print menu of parsable commands
        if (args[i][1] == 'h') {
            args::detail::help();
        }
        // Allows user to specify another path
        else if (args[i][1] == 'p') {
            args::detail::path(path, args, i);
            i++;
        }
        // Activate debug mode which allows some print statements around the program.
        // Most should be deleted before upload to GitHub
        // There are a few still left on purpose as a showcase of sorts
        else if (args[i][1] == 'd') {
            args::detail::debug();
        }
    }
}

