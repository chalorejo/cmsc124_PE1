/*
CMSC 124: 
    Program Exercise 1
Developers:
    Joe Hanna Cantero
    Charisse Lorejo
    Michael James Mangaron
*/

#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
#include "string_ops.h"

/* Menu-related functions */
void displayMainMenu(void);
int getMenuChoice(void);

/* Menu handlers */
void handleProgramDescription(void);
void handleExpressionEvaluator(void);
void handleStringCompression(void);
void handleStringExpansion(void);

int main(void)
{
    int choice;

    do {
        displayMainMenu();
        choice = getMenuChoice();

        switch (choice) {
            case 1:
                handleProgramDescription();
                break;
            case 2:
                handleExpressionEvaluator();
                break;
            case 3:
                handleStringCompression();
                break;
            case 4:
                handleStringExpansion();
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

void displayMainMenu(void)
{
    printf("\nWelcome to this Expression Evaluator program!\n");
    printf("[1] Program Description\n");
    printf("[2] Evaluate Expression(s)\n");
    printf("[3] Compress String(s)\n");
    printf("[4] Expand String(s)\n");
    printf("[0] Exit\n");
}

int getMenuChoice(void)
{
    int choice;
    printf("Choice: ");
    scanf("%d", &choice);
    getchar(); /* clear newline */
    return choice;
}
