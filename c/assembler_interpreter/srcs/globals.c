#include "assembler_interpreter.h"
#include "message.h"
#include "movements.h"
#include "labels.h"

// Flags
bool ret = false;
bool end = false;

// Registers
int registers[26] = {0};

// Last comparison result
int last_cmp = 0;

// Command arrays
void (*command_functions[])(const char *) = {mov, inc, dec, add, sub, mul, div_func, cmp, NULL};
char *(*command_functions_return[])(const char *) = {jmp, jne, je, jge, jg, jle, jl, NULL};

// Labels and subroutines
char *label_storages[500] = {0};
char **label_sub_routines[500] = {0};
