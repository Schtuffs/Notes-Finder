#include <iostream>

#include "../include/main.h"
extern bool DEBUG;

// Show user all menu options
void mainMenu(void) {
    std::cout << "X---------------X" << std::endl;
    std::cout << "|   Main Menu   |" << std::endl;
    std::cout << "X---------------X" << std::endl;
    std::cout << FILE_READ_ALL_FILES << ". Read all files" << std::endl;
    std::cout << FILE_READ_MULTIPLE_FILES << ". Select and read files" << std::endl;
    std::cout << FILE_READ_SINGLE_FILE << ". Read one file" << std::endl;
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

void selectFile(DataHandler& dataHandler) {
    std::cout << "Enter one of the filenames displayed below: " << std::endl;
    dataHandler.displayFilenames();
    std::string file;
    std::cin >> file;
    dataHandler.display(file);
}

void selectFiles(DataHandler& dataHandler) {
    std::cout << "Select the files you would like to open (" << CODE_EXIT << " to exit):" << std::endl;
    dataHandler.displayFilenames();
    std::string input, exit = std::to_string(CODE_EXIT);
    std::vector<std::string> files;
    do {
        std::cin >> input;
        files.push_back(input);
    } while (input != exit);
    dataHandler.display(files);
}

bool determineChoice(DataHandler& dataHandler, int value) {
    switch(value) {
    case FILE_READ_ALL_FILES:
        dataHandler.display();
        break;
    case FILE_READ_SINGLE_FILE: {
        selectFile(dataHandler);
        break;
    }
    case FILE_READ_MULTIPLE_FILES:
        selectFiles(dataHandler);
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
        int userInput = getIntInput(1, 3);
        programShouldRun = determineChoice(dataHandler, userInput);
    } while (programShouldRun != CODE_EXIT);

    return 0;
}

