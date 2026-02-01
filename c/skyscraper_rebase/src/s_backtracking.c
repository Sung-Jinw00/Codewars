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
int	**backtracking_solve(int ***available_nbs, int **solution, int *clues, int depth, int prev_empty_box)
{
	if (depth > N * N || find_empty_box(solution, -1) == -1)//avoid going too deep in the research
		return (solution);
	int empty_box, **solution_dup = calloc(N, sizeof(int *)), ***avail_nbs_dup = available_nbs_dup(available_nbs);
	bool newline = false;

	for (int i = 0; i < N; i++)
		solution_dup[i] = calloc(N, sizeof(int));
	sol_dup(solution_dup, solution);//i get a duplicate to save my initial progression
	if (prev_empty_box != -1 && prev_empty_box % N != find_empty_box(solution, prev_empty_box + 1) % N)//if the new empty box is not on the same line as the one before
	{
		set_guessable_nbs(avail_nbs_dup, solution_dup, clues);//i try to guess with a new full line
		newline = true;
	}
	if ((empty_box = find_empty_box(solution_dup, prev_empty_box + 1)) == -1)//all boxes are filled
	{
		sol_dup(solution, solution_dup);
		return (free_array3(avail_nbs_dup), free_array2(solution_dup), solution);
	}
	else if (no_possible_numbers(solution_dup, avail_nbs_dup))//no possible numbers has been found in a box, stop the searching here
		return (free_array3(avail_nbs_dup), free_array2(solution_dup), solution);
	else//i can still place numbers
	{
		int len_array, nbs_for_box[N] = {0};
		get_available_nbs_in_box(avail_nbs_dup, empty_box, nbs_for_box, &len_array);//i get the possible solutions
		while (--len_array >= 0)//while i didn't got through all the numbers
		{
			sol_dup(solution_dup, solution);//set back the available numbers if one failed
			copy_available(avail_nbs_dup, available_nbs);//set back the available numbers if one failed
			if (newline)
				set_guessable_nbs(avail_nbs_dup, solution_dup, clues);
			set_valid_pos(NB(nbs_for_box[len_array]), empty_box / N, empty_box % N, avail_nbs_dup, solution_dup);//i put the highest number because they are the ones with the least amount of positions, easy find
			int **result = backtracking_solve(avail_nbs_dup, solution_dup, clues, depth + 1, empty_box);//i give the solution found to solution
			if (!result)
				continue;
			sol_dup(solution, result);
			if (find_empty_box(solution, prev_empty_box + 1) == -1 && clues_respected(solution, clues) && different_towers(solution))//if i've found all the numbers
				return (free_array3(avail_nbs_dup), free_array2(solution_dup), solution);//i return the solution
		}
	}
	if (!depth)
		free_array2(solution);
	free_array2(solution_dup);
	free_array3(avail_nbs_dup);
	return NULL;//no solutions found
}
