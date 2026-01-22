#ifndef LABELS_H
# define LABELS_H

# include <stdbool.h>
# include <string.h>
# include "utils.h"

// ──────────────────────────────────────────────
// Labels and subroutine management
// ──────────────────────────────────────────────

int label(const char *program);                    // Store a label
void skip_sub_routine(char **arr_cmds, int *j);   // Skip lines of a subroutine
void get_labels_and_sub_routines(char *program);  // Parse labels and store subroutine code
bool label_exist(char *label);                     // Check if label exists

// Labels and subroutines
extern char *label_storages[500];
extern char **label_sub_routines[500];

#endif
