#include "calculator.h"
#include <string.h>
#include <ctype.h>

void calculate(EXPRESSION * exp, RESULT * res)  {

    switch (exp->operator) {
    case '+':
        res->result = exp->op1 + exp->op2;
        strcpy(res->message,"Sum is: ");
        break;

    case '-':
        res->result = exp->op1 - exp->op2;
        strcpy(res->message,"Subtraction is: ");
        break;

    case '*':
        res->result = exp->op1 * exp->op2;
        strcpy(res->message,"Multiplication is: ");
        break;

    case '/':
        if (exp->op2 == 0) { // division by zero
            res->result = 0;
            strcpy(res->message,"KABOOM!");
        }
        else {
            res->result = exp->op1 / exp->op2;
            strcpy(res->message,"Division is: ");
        }
        break;

    default:
        res->result = 0;
        strcpy(res->message,"Calculator Error");
        break;
    
    }
}

bool valid_range(EXPRESSION * exp) {
    if (exp->op1 < 0 || exp->op1 > 10000 || exp->op2 < 0 || exp->op2 > 10000)
        return true;
    else
        return false;
}

bool quit(char *input_str) {
    to_lower(input_str);
    
    if (strcmp(input_str, "quit") == 0) // input is "quit"
        return true;
    else
        return false;
};