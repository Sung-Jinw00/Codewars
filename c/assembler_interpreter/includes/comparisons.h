#ifndef COMPARISONS_H
# define COMPARISONS_H

# include <stdbool.h>
# include "movements.h"
# include "assembler_interpreter.h"

// ──────────────────────────────────────────────
// Comparison and conditional jump instructions
// ──────────────────────────────────────────────

char *exec_label(char *label);  // forward declaration instead of including assembler_interpreter.h

char *jmp(const char *instruction);        // Unconditional jump
char *jne(const char *instruction);        // Jump if not equal
char *je(const char *instruction);         // Jump if equal
char *jge(const char *instruction);        // Jump if greater or equal
char *jg(const char *instruction);         // Jump if greater
char *jle(const char *instruction);        // Jump if less or equal
char *jl(const char *instruction);         // Jump if less

#endif
