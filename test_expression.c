/*
 * test_expression.c
 * Simple test driver for Expression Evaluator Module
 *
 * CMSC 124: Program Exercise 1
 *
 * This is a standalone main file that only calls
 * handleExpressionEvaluator() as specified in requirements.
 *
 * To compile and run:
 *   gcc -o test_expression test_expression.c expression.c
 *   ./test_expression
 */

#include "expression.h"
#include <stdio.h>

int main(void)
{
    int continueProgram = 1;
    
    do {
        handleExpressionEvaluator();
        
        // Ask user if they want to continue
        printf("Enter 1 to continue, 0 to exit: ");
        scanf("%d", &continueProgram);
        
    } while (continueProgram == 1);
    
    return 0;
}