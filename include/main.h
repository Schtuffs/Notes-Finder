#include <iostream>

#include "../include/CONSTANTS.h"
#include "../include/DataHandler.h"
#include "../include/args.h"

void mainMenu();

int getIntInput(int min, int max);

// For selecting 1 file
void selectFile(DataHandler& dataHandler);

// For selecting multiple files
void selectFiles(DataHandler& dataHandler);

bool determineChoice(DataHandler& dataHandler, int value);

