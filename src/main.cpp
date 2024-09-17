#include <iostream>

#include "../include/CONSTANTS.h"
#include "../include/DataHandler.h"

// Show user all menu options
void mainMenu(void) {
    std::cout << "1. Read all files" << std::endl;
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

bool determineChoice(DataHandler& dataHandler, int value) {
    switch(value) {
    case FILE_READ_ALL_FILES:
        dataHandler.diplay();
        break;
    case FILE_READ_SINGLE_FILE: {
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

int main(void) {
    // Setup object to be passed to functions
    DataHandler dataHandler("../files/");

    // Main loop for user input
    int programShouldRun = CODE_GOOD;
    do {
        mainMenu();
        int userInput = getIntInput(1, 1);
        programShouldRun = determineChoice(dataHandler, userInput);
    } while (programShouldRun != CODE_EXIT);

    return 0;
}

