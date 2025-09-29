#ifndef STRING_PARSER_H
#define STRING_PARSER_H
#define MAX_OP_VAL 10000
#define MIN_OP_VAL 0

#include <stdbool.h> 

typedef struct expression {
    float op1, op2;
    char operator;
    int quit;
    
} EXPRESSION;

void clean_input(char *input_str);

int quit(char *input_str);

bool valid_range(EXPRESSION * exp);

#endif