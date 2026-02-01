#include "skyscraper.h"

/**
 * @brief
 * Solve the skyscraper puzzle using backtracking.
 *
 * The current solution is saved before attempting recursive resolution.
 *
 * @param available_nbs the array of possible numbers
 * @param solution      The solution grid
 * @param clues         The array of clues
 * @param depth         The level of depth in my recursivity
 * @param prev_empty_box The position of the previous empty box, start at -1
 *
 * @return The solved grid or NULL if no solutions was found
 */
int	**backtracking_solve(int ***available_nbs, int **solution, int *clues, int depth)
{
	if (depth > N * N)//avoid going too deep in the research
		return (solution);
	
	int line, col;
	empty_box_coords(solution, &line, &col);//get empty box coordinates
	if (line == -1 && col == -1)//no empty box
		return solution;
	int nb_try = lowest_available(available_nbs, line, col);
	if (!nb_try)
		return NULL;
	int available_nbs_dup[N][N][N], **solution_dup = init_solution();
	sol_dup(solution_dup, solution);
	available_dup(available_nbs_dup, available_nbs);
	while (nb_try > 0)
	{
		solution[line][col] = nb_try;
		backtracking_solve(available_nbs_dup, solution_dup, clues, depth + 1);
		nb_try--;
	}
	return solution;
}
