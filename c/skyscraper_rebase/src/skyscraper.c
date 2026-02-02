#include "skyscraper.h"

/**
 * @brief
 * Entry point of the skyscraper puzzle solver.
 *
 * This function initializes all required data structures:
 * 
 * - marks empty clues as already fulfilled
 * 
 * - allocates and initializes `available_nbs`
 * 
 * - allocates and initializes the `solution` grid
 *
 * It then applies all deterministic deductions before
 * entering the recursive backtracking phase.
 *
 * @param clues  the array of clues surrounding the board
 *
 * @return
 * A dynamically allocated 2D array representing the solution,
 * or `NULL` if `clues` is invalid.
 */
int **SolvePuzzle(int *clues)
{
	//return NULL if clues == NULL
	if (!clues)
		return (NULL);

	//init the boards of available numbers
	int available_nbs[N][N][N] = {0}, **solution = init_solution();
	init_availability(available_nbs);
	//return the solution
	return (backtracking_solve(available_nbs, solution, clues, 0));
}
