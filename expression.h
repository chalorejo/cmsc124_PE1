/*
 * expression.h
 *
 * Header file for Expression Evaluator.
 * 
 * Developers:
 *   Joe Hanna Cantero
 *   Charisse Lorejo
 *   Michael James Mangaron
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#define MAX_EXPR_SIZE 256
#define MAX_STACK_SIZE 128

/*
 * Validates an infix expression.
 * Returns 1 if valid, 0 otherwise.
 */
int isValidInfix(const char *expr);

/*
 * Converts infix to postfix.
 */
void infixToPostfix(const char *infix, char *postfix);

/*
 * Evaluates a postfix expression (supports multi-digit).
 * Returns result.
 */
int evaluatePostfix(const char *postfix);

/*
 * Checks if char is an operator.
 */
int isOperator(char c);

/*
 * Returns operator precedence.
 */
int precedence(char op);

/*
 * Main handler for expression evaluation.
 */
void handleExpressionEvaluator(void);

#endif
