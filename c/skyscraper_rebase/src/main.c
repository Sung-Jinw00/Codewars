#include "main.h"

/**
 * @brief
 * Entry point of the Skyscraper solver test program.
 *
 * This function runs predefined test cases for the Skyscraper puzzle solver.
 * For each test case:
 * 
 * - it calls `SolvePuzzle` with a set of `clues`
 * 
 * - compares the returned solution with the expected grid
 * 
 * - prints the result and highlights any difference
 *
 * After each test:
 * 
 * - allocated memory is freed
 * 
 * - global state (`clues_fullfilled`, `nbs_found`) is reset
 *
 * The program exits with status 0 after all tests are executed.
 *
 * @return 0 on normal execution
 */
int main(void)
{
	static int clues[][4 * 4] = {
	  { 1, 3, 2, 2,
		3, 1, 2, 2,
		2, 2, 1, 3,
		2, 3, 2, 1 },
	  { 2, 2, 1, 3,
		2, 2, 1, 3,
		2, 3, 2, 1,
		1, 3, 2, 2 }
	};
	
	static int expected[][4][4] = {
		{{ 4, 2, 3, 1 },
		 { 3, 1, 2, 4 },
		 { 1, 3, 4, 2 },
		 { 2, 4, 1, 3 }},
		{{ 3, 2, 4, 1 },
		 { 1, 4, 2, 3 },
		 { 2, 1, 3, 4 },
		 { 4, 3, 1, 2 }}
	};
	int diff = 0;

	for (int i = 0; i < 2; i++)
	{
		int **result = SolvePuzzle(clues[i]);
		fprintf(stderr, CYAN UNDERLINE BOLD"Test %d :\n"RESET, i);
		for (int j = 0; j < 4; j++)
		{
			if (!result || memcmp(result, expected[i], 4 * sizeof(int)))
			{
				diff = 1;
				fprintf(stderr, RED "diff !\n"RESET);
				print_answer(result, wrapped_array(expected[i]), clues[i]);
				fprintf(stderr, RESET);
				break ;
			}
		}
		if (!diff)
			fprintf(stderr, GREEN"no diff !"CYAN" congrats !\n"RESET);
		fprintf(stderr, "\n\n");
		diff = 0;
		if (result)
			free_array2(result);
	}
	return (0);
}
