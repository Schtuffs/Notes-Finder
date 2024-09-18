#include <iostream>

#include "../include/CONSTANTS.h"
#include "../include/DataHandler.h"
#include "../include/args.h"

extern bool DEBUG;

// Show user all menu options
void mainMenu(void) {
    std::cout << "X---------------X" << std::endl;
    std::cout << "|   Main Menu   |" << std::endl;
    std::cout << "X---------------X" << std::endl;
    std::cout << "1. Read all files" << std::endl;
    std::cout << "2. Read one file" << std::endl;
    std::cout << CODE_EXIT << ". Exit" << std::endl;
}

int getIntInput(int min, int max) {
    int userInput = -1;
    std::cout << "Enter an option between " << min << " and " << max << std::endl;
    std::cin >> userInput;
    while(userInput != CODE_EXIT && (max < userInput || userInput < min)) {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Enter an option between " << min << " and " << max << std::endl;
        std::cin >> userInput;
    }

    return userInput;
}

void readSelectedFiles(DataHandler& dataHandler) {
    std::cout << "Enter one of the filenames displayed below: " << std::endl;
    dataHandler.displayFilenames();
    std::string file;
    std::cin >> file;
    dataHandler.diplay(file);
}

bool determineChoice(DataHandler& dataHandler, int value) {
    switch(value) {
    case FILE_READ_ALL_FILES:
        dataHandler.diplay();
        break;
    case FILE_READ_SINGLE_FILE: {
        readSelectedFiles(dataHandler);
        break;
    }
    case FILE_FIND_SINGLE_SECTION:
        break;
    case CODE_EXIT:
        return false;
        break;
    default:
        break;
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::string path = "../files/";
    if (argc != 1) {
        // Setup object to be passed to functions
        args::parse(argc, argv, path);
    }
    else {
        std::cout << std::endl << "Add argument '-h' to show command line arguments" << std::endl << std::endl;
    }

    DataHandler dataHandler(path);

    // Main loop for user input
    int programShouldRun = CODE_GOOD;
    do {
        mainMenu();
        int userInput = getIntInput(1, 2);
        programShouldRun = determineChoice(dataHandler, userInput);
    } while (programShouldRun != CODE_EXIT);

    return 0;
}

