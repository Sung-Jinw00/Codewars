#ifndef MOVEMENTS_H
# define MOVEMENTS_H

# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>

// ──────────────────────────────────────────────
// Assembly-like movement and arithmetic instructions
// ──────────────────────────────────────────────

void mov(const char *instruction);         // Move value into a register
void inc(const char *instruction);         // Increment register
void dec(const char *instruction);         // Decrement register
void add(const char *instruction);         // Add value to register
void sub(const char *instruction);         // Subtract value from register
void mul(const char *instruction);         // Multiply register by value
void div_func(const char *instruction);    // Divide register by value (integer division)
void cmp(const char *instruction);         // Compare two values

// Registers
extern int registers[26];

// Last comparison result
extern int last_cmp;

#endif
