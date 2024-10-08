#include "../include/args.h"

bool DEBUG = false;

void args::detail::help() {
    std::cout << "-h    shows all commands" << std::endl;
    std::cout << "-p    next argument is the path to find files in" << std::endl;
    std::cout << "-d    debug mode, should do nothing" << std::endl;
    std::cout << "-c    shows colour commands" << std::endl;
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

void args::detail::colours() {
    std::cout << std::endl;
    std::cout << "Entering a colour" << std::endl;
    std::cout << "Add a '*', a colour afterwards, and a space after the colour" << std::endl;
    std::cout << std::endl;
    std::cout << "available colours:" << std::endl;
    std::cout << "BLACK, RED, GREEN, YELLOW" << std::endl;
    std::cout << "BLUE, MAGENTA, CYAN, WHITE" << std::endl;
    std::cout << std::endl;
    std::cout << "Add a 'B' to make a colour bright" << std::endl;
    std::cout << "Ex: -*GREEN This would be green text" << std::endl;
    std::cout << "Ex: -*BGREEN This would be bright green text" << std::endl;
    std::cout << std::endl;
    std::cout << "Can also do individual sections of text" << std::endl;
    std::cout << "Ex: - This text is normal, but *RED this text is red* but not here" << std::endl;
    std::cout << std::endl;
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
        // Shows the colour commands for changing text colour
        else if (args[i][1] == 'c') {
            args::detail::colours();
        }
    }
}

