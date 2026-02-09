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
        
        /* if it encounter a digit, check for leading zeros */
        if (isdigit(str[i])) {
            if (str[i] == '0') {
                return 0;
            }
            
            /* Skip the rest of the digits in this number */
            while (isdigit(str[i])) {
                i++;
            }
        }
        
        /* the digit (or no digit) must followed by a letter */
        if (!isalpha(str[i])) {
            return 0;
        }

        /* if digit exists, it must be positive and not zero */
        if (hasDigit && str[i - 1] == '0') {
            return 0;
        }

        /* move past the letter */
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

        /* to write the letter itself after the number */
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

        /* read multi-digit if present */
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