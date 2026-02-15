/*
 * string_ops.c
 *
 * Implements string compression and expansion.
 *
 * Developers:
 *   Joe Hanna Cantero
 *   Charisse Lorejo
 *   Michael James Mangaron
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "string_ops.h"

/* Validation */
int isValidString(const char *str) {
    int i;

    if (str == NULL || *str == '\0') {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidCompressedString(const char *str) {
    int i = 0;
    int hasDigit;

    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (str[i] != '\0') {
        hasDigit = 0;
        
        if (isdigit(str[i])) {
            hasDigit = 1;
            if (str[i] == '0') {
                return 0;
            }

            /* Check if the number is exactly "1" */
            if (str[i] == '1' && !isdigit(str[i+1])) {
                return 0;
            }
            
            /* Skip digits */
            while (isdigit(str[i])) {
                i++;
            }
        }
        
        /* Must be followed by a letter */
        if (!isalpha(str[i])) {
            return 0;
        }

        /* Check for n=1 case (if digit exists, it implies n>1, but logic here checks if previous was 0?? 
           Wait, logic says: if hasDigit and str[i-1] == '0'. 
           Actually, the "no leading zero" check above handles '0' start. 
           But '10' is valid. '05' is invalid. 
           The logic `if (hasDigit && str[i - 1] == '0')` checks if the LAST digit was 0? 
           No, `str[i-1]` is the last digit. 
           If number was "10", `str[i-1]` is '0'. This would fail valid numbers like 10, 20.
           
           Let's look at the original code:
           if (hasDigit) { ... while (isdigit) i++; }
           if (!isalpha) return 0;
           if (hasDigit && str[i-1] == '0') return 0; 
           
           If input is "10a". 
           i points to '1'. isdigit('1') -> true.
           inner loop: skips '1', '0'. i points to 'a'.
           hasDigit = ? (Original code didn't set hasDigit inside the `if` block properly? 
           Wait, original code:
           `hasDigit = 0;`
           `if (isdigit(str[i])) { ... while... i++; }` -> It DOES NOT set hasDigit = 1.
           So `hasDigit` is ALWAYS 0.
           The check `if (hasDigit && ...)` is always false.
           So "10a" works by accident?
           Or was `hasDigit` supposed to be set?
           
           Actually, looking at the original code provided in previous turn:
           `int hasDigit;` (uninitialized? No, declared at top).
           `while (...) { hasDigit = 0; if (isdigit) { ... } ... }`
           It seems `hasDigit` is indeed always 0 when reaching the check.
           
           The user wants me to FIX logic if broken. 
           "10a" should be valid. 
           "0a" should be invalid (caught by `if (str[i] == '0')`).
           
           The prompt says: "For n=1, the value of n should not be shown."
           So "1a" is INVALID. "a" is VALID.
           
           I need to detect if the number matches "1".
           
           Let's fix the logic and comments.
        */
        
        /* Move past the letter */
        i++;
    }
    return 1;
}

/* Operations */
void compressString(const char *input, char *output) {
    int i = 0, j = 0;
    int count;

    while (input[i] != '\0') {
        count = 1;
        
        while (input[i] == input[i + 1]) {
            count++;
            i++;
        }

        if (count > 1) {
            j += sprintf(&output[j], "%d", count);
        }

        /* Write letter */
        output[j++] = input[i];
        i++;
    }
    output[j] = '\0';
}

void expandString(const char *input, char *output) {
    int i = 0, j = 0;
    int count;

    while (input[i] != '\0') {
        count = 0;

        /* Read number if present */
        while (isdigit(input[i])) {
            count = count * 10 + (input[i] - '0');
            i++;
        }

        if (count == 0)
            count = 1;

        while (count-- > 0) {
            output[j++] = input[i];
        }
        i++;
    }
    output[j] = '\0';    
}

/* Menu handlers */
void handleStringCompression(void) {
    char input[256];
    char output[516];
    char repeat;

    do {
        printf("\nEnter string to compress : ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (!isValidString(input)) {
            printf("Invalid string input.\n");
        } else {
            compressString(input, output);
            printf("Compressed Form : %s\n", output);
        }

        printf("Repeat? (y/n) : ");
        scanf(" %c", &repeat);
        getchar();        
    } while (repeat == 'y' || repeat == 'Y');
}

void handleStringExpansion(void) {
    char input[256];
    char output[516];
    char repeat;

    do {
        printf("\nEnter string to expand : ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (!isValidCompressedString(input)) {
            printf("Invalid string input.\n");
        } else {
            expandString(input, output);
            printf("Expanded Form : %s\n", output);
        }

        printf("Repeat? (y/n) : ");
        scanf(" %c", &repeat);
        getchar();
    } while (repeat == 'y' || repeat == 'Y');
}