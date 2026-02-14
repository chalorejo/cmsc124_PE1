#ifndef STRING_OPS_H
#define STRING_OPS_H

/* Validation */
int isValidString(const char *str);
int isValidCompressedString(const char *str);

/* Operations */
void compressString(const char *input, char *output);
void expandString(const char *input, char *output);

/* Menu handlers */
void handleStringCompression(void);
void handleStringExpansion(void);

#endif