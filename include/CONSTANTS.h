#pragma once

#define FILE_READ_ALL_FILES         1
#define FILE_READ_MULTIPLE_FILES    2
#define FILE_READ_SINGLE_FILE       3

#define CODE_EXIT   0
#define CODE_ERROR  -1
#define CODE_GOOD   1

#define OUTPUT_SPACES   2
#define OUTPUT_BULLET   '-'

#define PARSE_ERROR     0xfff
#define PARSE_EMPTY     0xaa
#define PARSE_HEADER    0xab
#define PARSE_LINE      0xac

#define LAYER_ERROR         0xaa
#define LAYER_EMPTY         0xab
#define LAYER_HEADER        0xfff
#define LAYER_HEADER_HIDDEN 0xffff

#define ADD_SUCCESS     1
#define ADD_FAILURE     -1
#define ADD_EMPTY       2
#define ADD_SPECIAL     3

// Display colours
#define BLACK   30
#define RED     31
#define GREEN   32
#define YELLOW  33
#define BLUE    34
#define MAGENTA 35
#define CYAN    36
#define WHITE   37

// Bright Colours
#define BRIGHT  60
#define RESET_COLOUR    0

