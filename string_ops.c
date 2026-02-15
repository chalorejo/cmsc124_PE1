/*
 * string_ops.c
 *
 * Implements string compression and expansion.
 * Compression: "aaabbc" -> "3a2bc"
 * Expansion:   "3a2bc" -> "aaabbc"
 *
 * Developers:
 *   Joe Hanna Cantero
 *   Charisse Lorejo
 *   Michael James Mangonen
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "string_ops.h"

/* ============================================================
 * Function: isValidString
 * Validates a string for compression operation.
 * - Must not be NULL or empty
 * - Must contain only alphabetic characters (no digits, spaces, or symbols)
 * Returns 1 if valid, 0 otherwise.
 * 
 * Example of invalid input: "hello123" (contains digits)
 *                           "hello world" (contains space)
 *                           "hello!" (contains symbol)
 * ============================================================ */
int isValidString(const char *str) {
    int i;

    /* Check for NULL or empty string */
    if (str == NULL || *str == '\0') {
        return 0;
    }

    /* Verify each character is a letter */
    for (i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

/* ============================================================
 * Function: isValidCompressedString
 * Validates a compressed string for expansion operation.
 * Rules:
 *   - Must not be NULL or empty
 *   - Format: [count]letter where count > 1 (optional, omitted for count=1)
 *   - No leading zeros in counts (e.g., "05a" invalid)
 *   - Count of 1 must not be shown (e.g., "1a" invalid, should be "a")
 *   - Must end with a letter
 * Returns 1 if valid, 0 otherwise.
 * 
 * Examples of invalid inputs:
 *   "05a"     - Leading zero not allowed
 *   "1a"      - Count of 1 should not be shown
 *   "10"      - No letter at the end
 *   "a5"      - Count must come before letter
 *   "a b"     - Spaces not allowed
 *   "3a2"     - Ends with digit instead of letter
 * ============================================================ */
int isValidCompressedString(const char *str) {
    int i = 0;
    int hasDigit;

    /* Check for NULL or empty string */
    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (str[i] != '\0') {
        hasDigit = 0;
        
        /* Check for digit(s) indicating repeat count */
        if (isdigit(str[i])) {
            hasDigit = 1;
            
            /* No leading zeros allowed */
            if (str[i] == '0') {
                return 0;
            }

            /* Count of 1 must not be explicitly shown */
            if (str[i] == '1' && !isdigit(str[i+1])) {
                return 0;
            }
            
            /* Skip over all digits of the count */
            while (isdigit(str[i])) {
                i++;
            }
        }
        
        /* After digits (if any), must have a letter */
        if (!isalpha(str[i])) {
            return 0;
        }

        /* Move past the letter */
        i++;
    }
    return 1;
}

/* ============================================================
 * Function: compressString
 * Compresses a string by replacing consecutive repeated letters
 * with count + letter (e.g., "aaabb" -> "3a2b").
 * 
 * Algorithm:
 *   1. Traverse the input string character by character
 *   2. Count consecutive occurrences of each letter
 *   3. If count > 1, write the count followed by the letter
 *   4. If count == 1, write just the letter
 * 
 * Parameters:
 *   input  - Original uncompressed string (must be valid)
 *   output - Buffer to store compressed result
 * ============================================================ */
void compressString(const char *input, char *output) {
    int i = 0, j = 0;
    int count;

    while (input[i] != '\0') {
        count = 1;
        
        /* Count consecutive identical characters */
        while (input[i] == input[i + 1]) {
            count++;
            i++;
        }

        /* Write count if more than one occurrence */
        if (count > 1) {
            j += sprintf(&output[j], "%d", count);
        }

        /* Write the character itself */
        output[j++] = input[i];
        i++;
    }
    output[j] = '\0';
}

/* ============================================================
 * Function: expandString
 * Expands a compressed string back to its original form.
 * Handles multi-digit counts and single letters.
 * 
 * Algorithm:
 *   1. Traverse the compressed string
 *   2. If digits are found, parse them into a count
 *   3. If no digits, count defaults to 1
 *   4. Write the following letter 'count' times
 * 
 * Parameters:
 *   input  - Compressed string (must be valid)
 *   output - Buffer to store expanded result
 * ============================================================ */
void expandString(const char *input, char *output) {
    int i = 0, j = 0;
    int count;

    while (input[i] != '\0') {
        count = 0;

        /* Parse the count if digits are present */
        while (isdigit(input[i])) {
            count = count * 10 + (input[i] - '0');
            i++;
        }

        /* If no count specified, default to 1 */
        if (count == 0)
            count = 1;

        /* Write the letter 'count' times */
        while (count-- > 0) {
            output[j++] = input[i];
        }
        i++;
    }
    output[j] = '\0';    
}

/* ============================================================
 * Function: handleStringCompression
 * Main workflow for string compression operation.
 * Loops until user chooses to exit.
 * 
 * Steps:
 *   1. Prompt for input string
 *   2. Validate input (letters only)
 *   3. If invalid, show example of correct format
 *   4. Compress the string and display result
 *   5. Ask if user wants to compress another string
 * 
 * Example of valid input: "aaabbc" -> compresses to "3a2bc"
 * Example of invalid input: "aaabbc123" (contains digits)
 * ============================================================ */
void handleStringCompression(void) {
    char input[256];
    char output[516];  /* Expanded buffer for worst case (all single letters) */
    char repeat;

    do {
        printf("\nEnter string to compress : ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  /* Remove trailing newline */

        if (!isValidString(input)) {
            printf("Invalid string input.\n");
            printf("Instructions: Use only letters (A-Z or a-z).\n");
            printf("Example of valid input: \"aaabbc\"\n");
            printf("Example of invalid input: \"aaabbc123\" (contains digits)\n");
        } else {
            compressString(input, output);
            printf("Compressed Form : %s\n", output);
        }

        /* Ask if user wants to continue with validation */
        do {
            printf("Repeat? (y/n) : ");
            scanf(" %c", &repeat);
            getchar();  /* Clear newline from buffer */

            if (repeat != 'Y' && repeat != 'y' &&
                repeat != 'N' && repeat != 'n') {
                printf("Invalid input. Please enter y or n only.\n");
                printf("Example: Enter 'y' to continue, 'n' to exit\n");
            }
        } while (repeat != 'Y' && repeat != 'y' &&
                repeat != 'N' && repeat != 'n');
                       
    } while (repeat == 'y' || repeat == 'Y');
}

/* ============================================================
 * Function: handleStringExpansion
 * Main workflow for string expansion operation.
 * Loops until user chooses to exit.
 * 
 * Steps:
 *   1. Prompt for compressed string
 *   2. Validate compressed format
 *   3. If invalid, show example of correct format
 *   4. Expand the string and display result
 *   5. Ask if user wants to expand another string
 * 
 * Example of valid input: "3a2bc" -> expands to "aaabbc"
 * Examples of invalid inputs:
 *   "1a"  - Count of 1 should not be shown (should be "a")
 *   "05a" - Leading zeros not allowed
 *   "3a2" - Ends with digit instead of letter
 * ============================================================ */
void handleStringExpansion(void) {
    char input[256];
    char output[516];  /* Buffer for expanded result */
    char repeat;

    do {
        printf("\nEnter string to expand : ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  /* Remove trailing newline */

        if (!isValidCompressedString(input)) {
            printf("Invalid string input.\n");
            printf("Instructions: Format should be [count]letter where:\n");
            printf("  - count > 1 (optional, omitted for single letters)\n");
            printf("  - No leading zeros (e.g., \"05a\" is invalid)\n");
            printf("  - Count of 1 must NOT be shown (use \"a\" not \"1a\")\n");
            printf("  - Must end with a letter\n\n");
            printf("Examples of valid input: \"3a2bc\", \"a3b2c\", \"xyz\"\n");
            printf("Examples of invalid input:\n");
            printf("  \"1a\"  - Count of 1 should not be shown\n");
            printf("  \"05a\" - Leading zeros not allowed\n");
            printf("  \"3a2\" - Ends with digit instead of letter\n");
        } else {
            expandString(input, output);
            printf("Expanded Form : %s\n", output);
        }

        /* Ask if user wants to continue with validation */
        do {
            printf("Repeat? (y/n) : ");
            scanf(" %c", &repeat);
            getchar();  /* Clear newline from buffer */

            if (repeat != 'Y' && repeat != 'y' &&
                repeat != 'N' && repeat != 'n') {
                printf("Invalid input. Please enter y or n only.\n");
                printf("Example: Enter 'y' to continue, 'n' to exit\n");
            }
        } while (repeat != 'Y' && repeat != 'y' &&
                repeat != 'N' && repeat != 'n');

    } while (repeat == 'y' || repeat == 'Y');
}