#ifndef ASSEMBLER_INTERPRETER_H
#define ASSEMBLER_INTERPRETER_H

# define _GNU_SOURCE
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdbool.h>

// Flags
extern bool ret;
extern bool end;

// Command arrays
extern void (*command_functions[])(const char *);
extern char *(*command_functions_return[])(const char *);

// ──────────────────────────────────────────────
// Include all supporting modules for the assembler interpreter
// ──────────────────────────────────────────────
# include "utils.h"        // String and array utilities
# include "movements.h"    // Register and arithmetic instructions
# include "comparisons.h"  // Comparison and conditional jumps
# include "labels.h"       // Label and subroutine management
# include "message.h"      // Msg instruction handling

// ──────────────────────────────────────────────
// Main assembler interpreter interface
// ──────────────────────────────────────────────

char	*exec_label(char *label);
char *assembler_interpreter(const char *program); // Execute the full program


#endif
