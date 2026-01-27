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
	static int clues[][N * 4] = {
	  { 7, 0, 0, 0, 2, 2, 3,
		0, 0, 3, 0, 0, 0, 0,
		3, 0, 3, 0, 0, 5, 0,
		0, 0, 0, 0, 5, 0, 4 },
	  { 0, 2, 3, 0, 2, 0, 0,
		5, 0, 4, 5, 0, 4, 0,
		0, 4, 2, 0, 0, 0, 6,
		5, 2, 2, 2, 2, 4, 1 }
	};
	
	static int expected[][N][N] = {
		{{ 1, 5, 6, 7, 4, 3, 2 },
		 { 2, 7, 4, 5, 3, 1, 6 },
		 { 3, 4, 5, 6, 7, 2, 1 },
		 { 4, 6, 3, 1, 2, 7, 5 },
		 { 5, 3, 1, 2, 6, 4, 7 },
		 { 6, 2, 7, 3, 1, 5, 4 },
		 { 7, 1, 2, 4, 5, 6, 3 }},
		{{ 7, 6, 2, 1, 5, 4, 3 },
		 { 1, 3, 5, 4, 2, 7, 6 },
		 { 6, 5, 4, 7, 3, 2, 1 },
		 { 5, 1, 7, 6, 4, 3, 2 },
		 { 4, 2, 1, 3, 7, 6, 5 },
		 { 3, 7, 6, 2, 1, 5, 4 },
		 { 2, 4, 3, 5, 6, 1, 7 }}
	};
	int diff = 0;

	for (int i = 0; i < 1; i++)
	{
		int **result = SolvePuzzle(clues[i]);
		printf(CYAN UNDERLINE BOLD"Test %d :\n"RESET, i);
		for (int j = 0; j < N; j++)
		{
			if (!result || memcmp(result, expected[i], N * sizeof(int)))
			{
				diff = 1;
				printf(RED "diff !\n"/* CYAN UNDERLINE"result of :" */RESET);
				/* print_indices(clues[i]); */
				print_answer(result, wrapped_array(expected[i]), clues[i]);
				printf(RESET);
				break ;
			}
		}
		if (!diff)
			printf(GREEN"no diff !"CYAN" congrats !\n"RESET);
		printf("\n\n");
		diff = 0;
		free_array(result);
		memset(clues_fullfilled, 0, sizeof(bool) * N * 4);
		memset(nbs_found, 0, sizeof(int) * N);
		for (int i = 0; i < 2; i++)
			memset(nbs_found[i], 0, sizeof(int) * N);
	}
	return (0);
}
