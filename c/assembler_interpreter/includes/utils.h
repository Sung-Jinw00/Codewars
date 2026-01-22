#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include "movements.h"
# include "message.h"

// ──────────────────────────────────────────────
// Utility functions for string manipulation
// ──────────────────────────────────────────────

int skip_wspaces(char *str);               // Skip leading whitespaces
int strclen(char *program, char cut);      // Length until a cut character
int count_words(char *program, char cut, int limit); // Count words separated by 'cut'
char **split(char *program, char cut, int limit);    // Split string by 'cut'
char **remove_wspaces(char **array);       // Remove leading/trailing spaces in string array
int count_tabs(char **arr);                // Count number of strings in a string array
void free_array(char ***array);            // Free a 2D string array
void free_label_storages(char **array);    // Free label storage array

#endif
