/*
 * expression.h
 * Header file for Expression Evaluator Module
 *
 * CMSC 124: Program Exercise 1
 * Developers:
 *     Joe Hanna Cantero
 *     Charisse Lorejo
 *     Michael James Mangaron
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

/* Maximum size for expression and stack arrays */
#define MAX_EXPR_SIZE 256
#define MAX_STACK_SIZE 128

/* Function prototypes */

/*
 * Validates an infix expression.
 * Checks for:
 *   - Valid characters (operands, operators, parentheses)
 *   - Balanced parentheses
 *   - No consecutive operators
 *   - Expression does not start/end with operator
 *
 * @param expr The infix expression to validate
 * @return 1 if valid, 0 if invalid
 */
int isValidInfix(const char *expr);

/*
 * Converts an infix expression to postfix notation.
 * Uses array-based stack for operators.
 * Output is space-separated.
 *
 * @param infix  The input infix expression
 * @param postfix Buffer to store the resulting postfix expression
 */
void infixToPostfix(const char *infix, char *postfix);

/*
 * Evaluates a postfix expression.
 * Assumes operands are single-digit integers (0-9).
 *
 * @param postfix The postfix expression to evaluate
 * @return The integer result of the evaluation
 */
int evaluatePostfix(const char *postfix);

/*
 * Checks if a character is a valid operator.
 * Valid operators: + - * / %
 *
 * @param c The character to check
 * @return 1 if operator, 0 otherwise
 */
int isOperator(char c);

/*
 * Returns the precedence level of an operator.
 * Higher value = higher precedence.
 *
 * @param op The operator character
 * @return Precedence level (2 for * / %, 1 for + -, 0 otherwise)
 */
int precedence(char op);

/*
 * Main handler for the expression evaluator.
 * Prompts user for input, validates, converts to postfix,
 * evaluates, and displays results.
 */
void handleExpressionEvaluator(void);

#endif /* EXPRESSION_H */
