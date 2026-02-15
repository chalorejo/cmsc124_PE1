/*
 * string_ops.h
 *
 * Header file for string compression/expansion.
 *
 * Developers:
 *   Joe Hanna Cantero
 *   Charisse Lorejo
 *   Michael James Mangaron
 */

#ifndef STRING_OPS_H
#define STRING_OPS_H

/* Validates input string */
int isValidString(const char *str);

/* Validates compressed string */
int isValidCompressedString(const char *str);

/* Compresses string */
void compressString(const char *input, char *output);

/* Expands string */
void expandString(const char *input, char *output);

/* Menu handlers */
void handleStringCompression(void);
void handleStringExpansion(void);

#endif