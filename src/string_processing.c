#include "string_processing.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void clean_input(char *input_str) {
    // remove white spaces  and lowers all cases
    
    size_t j = 0;
    for (size_t i = 0; input_str[i]; i++) {
        if (input_str[i] != ' ' && input_str[i] != '\n')
            input_str[j++] = tolower(input_str[i]);
    }
    input_str[j] = '\0';
    
}

int check_input (char * input_str, EXPRESSION * expression) { 
    // check if input has structure "op1 operator op2" 

    float op1, op2;
    char operator;

    if (sscanf(input_str, "%f%c%f", &op1, &operator, &op2) != 3) // this will do the trick for now
        return -1; // Parsing failed due to too much elements

    expression->op1 = op1;
    expression->op2 = op2;
    expression->operator = operator;

    if (strchr("+-*/",operator) == NULL) 
        return -1; // Operator invalid
    
    return 0;

}

int quit(char *input_str) {
    if (strcmp(input_str, "quit") == 0) // input is "quit"
        return 1;
    else
        return 0;
};



