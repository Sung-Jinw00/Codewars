#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/**
 * @brief Executes a simple assembly-like program.
 *
 * Interprets and runs a small set of instructions on an array of registers.
 * Supported instructions:
 * 
 * - "mov X Y" : moves the value Y (number or register) into register X
 * 
 * - "inc X"   : increments register X by 1
 * 
 * - "dec X"   : decrements register X by 1
 * 
 * - "jnz X Y" : jumps Y instructions forward/backward if X (value or register) is not zero
 *
 * Registers are accessed by their ASCII code (e.g., 'a' → registers['a']).
 *
 * @param n Number of instructions in the program.
 * @param program Array of strings containing the instructions.
 * @param registers Array of integers representing the registers (size >= 128 recommended).
 */
void simple_assembler(size_t n, const char *const program[n], int registers[])
{
	char arg1[16], arg2[16];

	for(size_t i = 0; i < n; i++)
	{
		if (!strncmp(program[i], "mov ", 4))
		{
			sscanf(program[i], "mov %s %s", arg1, arg2);
			registers[(int)arg1[0]] = isalpha(arg2[0]) ? registers[(int)arg2[0]] : atoi(arg2);
		}
		else if (!strncmp(program[i], "inc ", 4))
			registers[(int)program[i][4]]++;
		else if (!strncmp(program[i], "dec ", 4))
			registers[(int)program[i][4]]--;
		else if (!strncmp(program[i], "jnz ", 4))
		{
			sscanf(program[i], "jnz %s %s", arg1, arg2);
			int x = isalpha(arg1[0]) ? registers[(int)arg1[0]] : atoi(arg1);
			int y = isalpha(arg2[0]) ? registers[(int)arg2[0]] : atoi(arg2);
			if (x != 0)
				i += y - 1;
		}
	}
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 128

# ifndef RESET
#  define RESET				"\033[0m"
# endif

/* Bold text */
# ifndef BOLD
#  define BOLD				"\033[1m"
# endif

/* Underlined text */
# ifndef UNDERLINE
#  define UNDERLINE			"\033[4m"
# endif

int	check_scores(int regs[N], int *answer, size_t len_answer)
{
	for (size_t i = 0; i < len_answer; i += 2)
	{
		if (regs[answer[i]] != answer[i + 1])
			return (printf("\ndifference !\nexpected %c = %d, got %c = %d\n",
					answer[i], answer[i + 1], answer[i], regs[answer[i]]));
	}
	return (0);
}

int main(void)
{
	int regs[N] = {0};

	const char **instructions[] = {
		(const char *[]){"mov a -39", "mov v 69", "mov v -22", "inc a", "mov v 2", "jnz v 2", "jnz v v", "jnz 1 -1", "mov v 4", "dec v", "inc v", "mov a 2", "jnz a 2", "jnz a a", "jnz 1 -1", "jnz -53 1", "jnz 0 1", "mov v a"},
		(const char *[]){"mov a 5","inc a","dec a","dec a","jnz a -1", "inc a"},
		(const char *[]){"mov a -10","mov b a","inc a","dec b","jnz a -2"},
		(const char *[]){"mov a 1","mov b 1","mov c 0","mov d 26","jnz c 2","jnz 1 5","mov c 7","inc d","dec c","jnz c -2","mov c a","inc a","dec b","jnz b -2","mov b c","dec d","jnz d -6","mov c 18","mov d 11","inc a","dec d","jnz d -2","dec c","jnz c -5"},
		(const char *[]){"mov d 100","dec d","mov b d","jnz b -2","inc d","mov a d","jnz 5 10","mov c a"},
		(const char *[]){"mov c 12","mov b 0","mov a 200","dec a","inc b","jnz a -2","dec c","mov a b","jnz c -5","jnz 0 1","mov c a"},
		(const char **)0x0
	};
	size_t len_instructions[] = {18, 6, 5, 24, 8, 11};
	int *answer[] = {
		(int[]){'a', 2, 'v', 2},
		(int[]){'a',  1},
		(int[]){'a', 0, 'b', -20},
		(int[]){'a', 318009, 'b', 196418, 'c', 0, 'd', 0},
		(int[]){'d', 1, 'b', 0, 'a', 1},
		(int[]){'c', 409600, 'b', 409600, 'a', 409600}
	};
	size_t len_answer[] = {4, 2, 4, 8, 6, 6};
		
	for(size_t i = 0; instructions[i]; i++)
	{
		simple_assembler(len_instructions[i], instructions[i], regs);
		printf(UNDERLINE BOLD"\n\nTest %ld :\n"RESET, i + 1);
		if (!check_scores(regs, answer[i], len_answer[i]))
			printf("\nNo diff, congrats !\n");
		memset(regs, 0, 128 * 4);
	}
	return (0);
}
