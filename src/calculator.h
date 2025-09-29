#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h> 

#define MSG_LEN 32

typedef struct expression {
    float op1, op2;
    char operator;
    int quit;
    
} EXPRESSION;

typedef struct result {
    float result;
    char * message[MSG_LEN];
    
} RESULT;

void calculate(EXPRESSION * expression, RESULT * result);

bool valid_range(EXPRESSION * exp);

bool quit(char *input_str);

#endif