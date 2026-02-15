/*
 * expression.c
 * 
 * Handles infix-to-postfix conversion and expression evaluation.
 *
 * Developers:
 *   Joe Hanna Cantero
 *   Charisse Lorejo
 *   Michael James Mangaron
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "expression.h"

/* Stack helpers */
#define PUSH(stack, top, val)    ((stack)[++(top)] = (val))
#define POP(stack, top)          ((stack)[(top)--])
#define PEEK(stack, top)         ((stack)[(top)])
#define IS_EMPTY(top)            ((top) < 0)

/* ============================================================
 * Function: isOperator
 * Checks if a character is a valid arithmetic operator.
 * ============================================================ */
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

/* ============================================================
 * Function: precedence
 * Returns operator precedence using lookup for efficiency.
 * High: * / % (2)  |  Low: + - (1)  |  Other: (0)
 * ============================================================ */
int precedence(char op)
{
    switch (op) {
        case '*': case '/': case '%': return 2;
        case '+': case '-':           return 1;
        default:                      return 0;
    }
}

/* 
 * Checks if the infix expression is valid.
 * - Balanced parentheses?
 * - Correct operator placement?
 * - Valid characters only?
 */
int isValidInfix(const char *expr)
{
    int parenDepth = 0;
    int expectOperand = 1;  /* 1 = expect operand, 0 = expect operator */
    int hasContent = 0;
    int inNumber = 0;       /* Track if we're inside a multi-digit number */
    const char *p;

    if (expr == NULL || *expr == '\0')
        return 0;

    for (p = expr; *p != '\0'; p++) {
        char c = *p;

        if (isspace((unsigned char)c)) {
            inNumber = 0;  /* Space ends a number */
            continue;
        }

        hasContent = 1;

        if (isdigit((unsigned char)c)) {
            if (!expectOperand && !inNumber)  /* Digit after operand without operator */
                return 0;
            inNumber = 1;
            expectOperand = 0;   /* Now expect an operator */
        }
        else if (isalpha((unsigned char)c)) {
            if (!expectOperand)  /* Letter after operand without operator */
                return 0;
            inNumber = 0;
            expectOperand = 0;   /* Now expect an operator */
        }
        else if (isOperator(c)) {
            if (expectOperand)   /* Operator when operand expected */
                return 0;
            inNumber = 0;
            expectOperand = 1;   /* Now expect an operand */
        }
        else if (c == '(') {
            if (!expectOperand)  /* '(' after operand without operator */
                return 0;
            inNumber = 0;
            parenDepth++;
            /* expectOperand stays 1 */
        }
        else if (c == ')') {
            if (expectOperand)   /* ')' when expecting operand */
                return 0;
            if (--parenDepth < 0)  /* Unmatched closing paren */
                return 0;
            inNumber = 0;
            /* expectOperand stays 0 */
        }
        else {
            return 0;  /* Invalid character */
        }
    }

    /* Must have content, balanced parens, and end with operand or ')' */
    return hasContent && (parenDepth == 0) && !expectOperand;
}

/* ============================================================
 * Helper: appendCharToPostfix
 * Appends a character to postfix with optional space separator
 * ============================================================ */
static void appendCharToPostfix(char *postfix, int *idx, int *needSpace, char c)
{
    if (*needSpace)
        postfix[(*idx)++] = ' ';
    postfix[(*idx)++] = c;
    *needSpace = 1;
}

/* ============================================================
 * Helper: appendNumberToPostfix
 * Appends a multi-digit number to postfix
 * Returns pointer to last digit processed
 * ============================================================ */
static const char* appendNumberToPostfix(const char *p, char *postfix, int *idx, int *needSpace)
{
    if (*needSpace)
        postfix[(*idx)++] = ' ';

    /* Copy all consecutive digits */
    while (*p != '\0' && isdigit((unsigned char)*p)) {
        postfix[(*idx)++] = *p;
        p++;
    }

    *needSpace = 1;
    return p - 1;  /* Return pointer to last digit (loop will increment) */
}

/* 
 * Converts infix to postfix using a stack.
 * Handles multi-digit numbers and spaces.
 */
void infixToPostfix(const char *infix, char *postfix)
{
    char opStack[MAX_STACK_SIZE];
    int top = -1;
    int idx = 0;
    int needSpace = 0;
    const char *p;

    for (p = infix; *p != '\0'; p++) {
        char c = *p;

        if (isspace((unsigned char)c))
            continue;

        /* Handle multi-digit numbers */
        if (isdigit((unsigned char)c)) {
            p = appendNumberToPostfix(p, postfix, &idx, &needSpace);
        }
        /* Handle single-letter variables */
        else if (isalpha((unsigned char)c)) {
            appendCharToPostfix(postfix, &idx, &needSpace, c);
        }
        else if (c == '(') {
            PUSH(opStack, top, c);
        }
        else if (c == ')') {
            /* Pop until matching '(' */
            while (!IS_EMPTY(top) && PEEK(opStack, top) != '(')
                appendCharToPostfix(postfix, &idx, &needSpace, POP(opStack, top));
            if (!IS_EMPTY(top))
                top--;  /* Discard the '(' */
        }
        else if (isOperator(c)) {
            /* Pop operators with >= precedence */
            while (!IS_EMPTY(top) &&
                   PEEK(opStack, top) != '(' &&
                   precedence(PEEK(opStack, top)) >= precedence(c)) {
                appendCharToPostfix(postfix, &idx, &needSpace, POP(opStack, top));
            }
            PUSH(opStack, top, c);
        }
    }

    /* Pop remaining operators */
    while (!IS_EMPTY(top))
        appendCharToPostfix(postfix, &idx, &needSpace, POP(opStack, top));

    postfix[idx] = '\0';
}

/* ============================================================
 * Helper: parseNumber
 * Parses a multi-digit number from string, returns the value
 * Updates pointer to point past the number
 * ============================================================ */
static int parseNumber(const char **p)
{
    int num = 0;
    while (**p != '\0' && isdigit((unsigned char)**p)) {
        num = num * 10 + (**p - '0');
        (*p)++;
    }
    (*p)--;  /* Back up one since the loop will increment */
    return num;
}

/*
 * Evaluates the postfix expression.
 * Returns the integer result.
 */
int evaluatePostfix(const char *postfix)
{
    int stack[MAX_STACK_SIZE];
    int top = -1;
    const char *p;

    for (p = postfix; *p != '\0'; p++) {
        char c = *p;

        if (isspace((unsigned char)c))
            continue;

        /* Handle multi-digit numbers */
        if (isdigit((unsigned char)c)) {
            PUSH(stack, top, parseNumber(&p));
        }
        else if (isOperator(c)) {
            int b = POP(stack, top);  /* Second operand (top of stack) */
            int a = POP(stack, top);  /* First operand */
            int result;

            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = (b != 0) ? a / b : 0; break;
                case '%': result = (b != 0) ? a % b : 0; break;
                default:  result = 0;
            }
            PUSH(stack, top, result);
        }
    }

    return IS_EMPTY(top) ? 0 : PEEK(stack, top);
}

/* ============================================================
 * Function: handleExpressionEvaluator
 * Main workflow: input -> validate -> convert -> evaluate
 * ============================================================ */
void handleExpressionEvaluator(void)
{
    char infix[MAX_EXPR_SIZE];
    char postfix[MAX_EXPR_SIZE];
    char *newline;

    printf("\n=== Expression Evaluator ===\n");
    printf("Enter an infix expression: ");

    if (fgets(infix, MAX_EXPR_SIZE, stdin) == NULL)
        return;

    /* Remove trailing newline */
    if ((newline = strchr(infix, '\n')) != NULL)
        *newline = '\0';

    printf("\nInfix   : %s\n", infix);

    if (!isValidInfix(infix)) {
        printf("Invalid infix expression.\n");
        return;
    }

    infixToPostfix(infix, postfix);
    printf("Postfix : %s\n", postfix);
    printf("Result  : %d\n", evaluatePostfix(postfix));
}
