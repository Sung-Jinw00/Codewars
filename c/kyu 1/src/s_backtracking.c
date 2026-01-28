#include "skyscraper.h"

/**
 * @brief
 * Iteratively place all deterministically guessable numbers in the solution grid.
 *
 * This function repeatedly applies deduction rules and clue-based reductions
 * until no further changes can be made.
 *
 * @param available_nbs  the array of possible numbers
 * @param solution       The solution grid
 * @param clues          The array of clues
 */
void	put_guessable_nbs(int ***available_nbs, int **solution, int *clues)
{
	for (bool changes = true; changes != false;)
	{
		changes = set_one_possibility_clue(available_nbs, solution, clues);
		if (!changes)
			changes = set_one_possibility_rules(available_nbs, solution, clues);
		reduce_possibilities(available_nbs, solution, clues);
	}
	print_all_available_each_box(available_nbs, clues, solution);
}

/**
 * @brief
 * Return the next available number for the cell with the least possibilities.
 *
 * This function iterates over the available numbers of a given position and
 * returns them one by one across successive calls.
 *
 * @param available_nbs     the array of possible numbers
 * @param available_amount The number of possibilities for each cell
 * @param pos               The position {line, column}
 *
 * @return The selected available number, or -1 if none is available
 */
int	least_available_nb(int ***available_nbs, int available_amount[N][N], int pos[2])
{
	static int nb;
	static int save_pos[2] = {-1};

	if (available_amount[pos[0]][pos[1]] == 1)
		return (-1);
	if (save_pos[0] != pos[0] || save_pos[1] != pos[0])
	{
		save_pos[1] = pos[1];
		save_pos[0] = pos[0];
		nb = 0;
	}
	while (nb < N)
	{
		if (available_nbs[nb][pos[0]][pos[1]])
			return (available_nbs[nb][pos[0]][pos[1]]);
		nb++;
	}
	if (nb == N)
		nb = 0;
	return (-1);
}

/**
 * @brief
 * Check whether all cells of the solution grid are filled.
 *
 * @param solution The solution grid
 *
 * @return true if all boxes are filled, false otherwise
 */
bool	all_boxes_filled(int **solution)
{
	for (int line = 0; line < N - 1; line++)
	{
		for (int col = 0; col < N - 1; col++)
		{
			if (!solution[line][col])
				return (false);
		}
	}
	return (true);
}

/**
 * @brief
 * Check if the number of visible towers from a given direction matches a clue.
 *
 * @param way      The direction of observation
 * @param line     The starting line index
 * @param col      The starting column index
 * @param solution The solution grid
 * @param clue     The expected number of visible towers
 *
 * @return true if the clue is respected, false otherwise
 */
bool	towers_visible(Direction way, int line, int col, int **solution, int clue)
{
	int towers_visibl = 2, prev_tower = solution[line][col];

	if (prev_tower == N)
		return (clue == 1);
	if (way == TTB)
	{
		while (solution[++line][col] != N)
		{
			if (prev_tower < solution[line][col])
			{
				prev_tower = solution[line][col];
				towers_visibl++;
			}
		}
	}
	else if (way == RTL)
	{
		while (solution[line][--col] != N)
		{
			if (prev_tower < solution[line][col])
			{
				prev_tower = solution[line][col];
				towers_visibl++;
			}
		}
	}
	else if (way == BTT)
	{
		while (solution[--line][col] != N)
		{
			if (prev_tower < solution[line][col])
			{
				prev_tower = solution[line][col];
				towers_visibl++;
			}
		}
	}
	else
	{
		while (solution[line][++col] != N)
		{
			if (prev_tower < solution[line][col])
			{
				prev_tower = solution[line][col];
				towers_visibl++;
			}
		}
	}
	return (towers_visibl == clue);
}

/**
 * @brief
 * Check whether all visibility clues are respected by the current solution.
 *
 * @param solution The solution grid
 * @param clues    The array of clues
 *
 * @return true if all conditions are respected, false otherwise
 */
bool	all_conditions_respected(int **solution, int *clues)
{
	for (int i = 0; i < N * 4; i++)
	{
		if (clues[i])
		{
			if (i < N && !towers_visible(TTB, 0, i, solution, clues[i]))
				return (false);
			else if (i < N * 2 && !towers_visible(RTL, i % N, N - 1, solution, clues[i]))
				return (false);
			else if (i < N * 3 && !towers_visible(BTT, N - 1, i % N, solution, clues[i]))
				return (false);
			else if (!towers_visible(LTR, i % N, 0, solution, clues[i]))
				return (false);
		}
	}
	return (true);
}

/**
 * @brief
 * Try to solve the grid by choosing a number in the cell with the least possibilities.
 *
 * This function applies a recursive backtracking strategy combined with
 * deterministic deductions.
 *
 * @param available_nbs the array of possible numbers
 * @param solution      The solution grid
 * @param clues         The array of clues
 *
 * @return true if a valid solution is found, false otherwise
 */
bool	put_random_nb(int ***available_nbs, int **solution, int *clues)
{
	int available_amount[N][N] = {0}, pos[2] = {0};
	set_available_amount(available_amount, available_nbs);

	while (least_available_nb(available_nbs, available_amount, pos) == -1)
		get_pos_least_amount(pos[0], pos[1], pos, available_amount);
	if (pos[0] >= N && pos[1] >= N)
		return (false);
	solution[pos[0]][pos[1]] = least_available_nb(available_nbs, available_amount, pos);
	put_guessable_nbs(available_nbs, solution, clues);
	if (!all_boxes_filled(solution))
		return (put_random_nb(available_nbs, solution, clues));
	return (all_conditions_respected(solution, clues));
}

/**
 * @brief
 * Solve the skyscraper puzzle using backtracking.
 *
 * The current solution is saved before attempting recursive resolution.
 *
 * @param available_nbs the array of possible numbers
 * @param solution      The solution grid
 * @param clues         The array of clues
 *
 * @return A pointer to the solved grid
 */
int	**backtracking_solve(int ***available_nbs, int **solution, int *clues)
{
	int sol_save[N][N] = {0};
	sol_dup(sol_save, solution, 0);
	if (put_random_nb(available_nbs, solution, clues))
		return (solution);
	sol_dup(sol_save, solution, 1);
	return (solution);
}
