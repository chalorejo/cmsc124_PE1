/*
 * CMSC 124 - Programming Exercise 1
 * 
 * Developers:
 *   Joe Hanna Cantero
 *   Charisse Lorejo
 *   Michael James Mangaron
 * 
 * Description:
 *   Main entry point for the application. Handles the main menu
 *   and delegates tasks to specific modules.
 */

#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
#include "string_ops.h"

/* Menu-related functions */
void displayMainMenu(void);
int getMenuChoice(void);

/* Menu handlers */
/* Menu handlers */
void handleProgramDescription(void);
/* Other handlers are already in headers or will be linked */

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

void handleProgramDescription(void)
{
    printf("\n--------------------------------------------------------------------------------\n");
    printf("PROGRAM DESCRIPTION\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Developers:\n");
    printf("  - Joe Hanna Cantero (Student No. 202X-XXXXX)\n");
    printf("  - Charisse Lorejo (Student No. 2024-03304)\n");
    printf("  - Michael James Mangaron (Student No. 202X-XXXXX)\n\n");
    
    printf("Module Descriptions:\n");
    printf("  [2] Expression Evaluator: Converts infix to postfix and evaluates it.\n");
    printf("  [3] String Compression: Compresses strings (e.g., 'aaabb' -> 'a3b2').\n");
    printf("  [4] String Expansion: Expands compressed strings (e.g., 'a3b2' -> 'aaabb').\n\n");
    
    printf("Work Distribution:\n");
    printf("  - Cantero: Expression Evaluator Logic\n");
    printf("  - Lorejo: Main Menu and Integration\n");
    printf("  - Mangaron: String Operations Logic\n\n");
    
    printf("Press Enter to return to the main menu...");
    while (getchar() != '\n'); 
    getchar(); /* Wait for Enter */
}
