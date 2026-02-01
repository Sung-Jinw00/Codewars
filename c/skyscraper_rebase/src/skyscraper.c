#include "skyscraper.h"

/* keep tracking the amount of clues fullfilled */
bool clues_fullfilled[N * 4] = {false};

/* keep tracking the amount of numbers found on lines and columns */
int nbs_found[2][7] = {
	{0, 0, 0, 0, 0, 0, 0},//lines
	{0, 0, 0, 0, 0, 0, 0}//cols
};

/**
 * @brief
 * Deduce all numbers that can be determined without backtracking.
 *
 * This function applies direct logical rules based on `clues`
 * and the current state of `solution` to reduce `available_nbs`.
 *
 * It handles special cases such as:
 * 
 * - a clue equal to `N`, which fully determines a row or column
 * 
 * - a clue equal to `1`, which forces the maximum number placement
 * 
 * - other clues, which restrict possible values near the clue
 *
 * Once all direct deductions are applied, it calls
 * `put_guessable_nbs` to propagate constraints.
 *
 * @param available_nbs  the array of possible numbers for each cell
 * @param solution       the current solution grid
 * @param clues          the array of clues
 */
void	set_guessable_nbs(int ***available_nbs, int **solution, int *clues)
{
	if (find_empty_box(solution, -1) == -1)
		return ;
	for (int i = 0; i < N * 4; i++)//while i didn't checked all clues
	{
		if (clues[i] != 0)//if a clue is found
		{
			if (clues[i] == N)//if clue = max nb
				actualise_max_clue(i, available_nbs, solution, clues);//i fill the line or column
			else if (clues[i] == 1)//else if clue = 1
				actualise_max_nb(i, available_nbs, solution, clues);//i put max nb
			else if (clues[i] == 2)//else if clue = 2
				remv_before_max_nb(i, available_nbs);//i remove N - 1 at the second box away from the clue
			if (!clues_fullfilled[i])//if the clue is not fullfilled
				set_limit_nbs(clues[i], i, available_nbs);//i set limits of possible numbers based on the clue
		}
	}
	//put_guessable_nbs(available_nbs, solution, clues);
}

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
	//set to 'true' empty clues
	for (int i = 0; i < N * 4; i++)
		if (!clues[i])
			clues_fullfilled[i] = true;
	//init the boards of available numbers
	int ***available_nbs = init_availability();
	//init the solution array of ints
	int **solution = calloc(sizeof(int *), N);
	for (int i = 0; i < N; i++)
		solution[i] = calloc(sizeof(int), N);
	//find guessable numbers before recursive search
	set_guessable_nbs(available_nbs, solution, clues);
	/* print_all_nb_arrays(available_nbs, clues);
	fprintf(stderr, "\n\n"); */
	//recursive search
	solution = backtracking_solve(available_nbs, solution, clues, 0, -1);
	//print the solution found
	print_all_available_each_box(available_nbs, clues, solution);
	free_array3(available_nbs);
	//return the solution
	return (solution);
}
