#include "skyscraper.h"

//─────────────────────────────
// Manage possibilities
//─────────────────────────────

/**
 * @brief
 * Find the highest possible lowest value reachable in a given direction.
 *
 * Starting from a reference value, this function scans forward in the given
 * direction and determines the maximum possible value that could still be
 * encountered based on the available numbers.
 *
 * Used to determine whether some low values can be safely removed.
 *
 * @param way             Direction to scan (LTR, RTL, TTB, BTT)
 * @param ref             Reference value (first possible value found)
 * @param line            Line index of the starting position
 * @param col             Column index of the starting position
 * @param solution        Current solution grid
 * @param available_nbs   3D array of available numbers
 *
 * @return
 * The highest possible value, or 0 if it does not exceed the reference.
 */
int	highest_low_nb(Direction way, int ref, int line, int col, int **solution, int ***available_nbs)
{
	int high_low_nb = ref, nb_tmp;

	if (way == LTR)
	{
		for (int inc_col = 1; !solution[line][inc_col]; inc_col++)
		{
			for (int nb = 0; nb < N; nb++)
			{
				if ((nb_tmp = available_nbs[nb][line][inc_col]))
				{
					if (high_low_nb < nb_tmp)
						high_low_nb = nb_tmp;
					break ;
				}
			}
		}
	}
	else if (way == RTL)
	{
		for (int inc_col = N - 2; !solution[line][inc_col]; inc_col--)
		{
			for (int nb = 0; nb < N; nb++)
			{
				if ((nb_tmp = available_nbs[nb][line][inc_col]))
				{
					if (high_low_nb < nb_tmp)
						high_low_nb = nb_tmp;
					break ;
				}
			}
		}
	}
	else if (way == TTB)
	{
		for (int inc_line = 1; !solution[inc_line][col]; inc_line++)
		{
			for (int nb = 0; nb < N; nb++)
			{
				if ((nb_tmp = available_nbs[nb][inc_line][col]))
				{
					if (high_low_nb < nb_tmp)
						high_low_nb = nb_tmp;
					break ;
				}
			}
		}
	}
	else
	{
		for (int inc_line = N - 2; !solution[inc_line][col]; inc_line--)
		{
			for (int nb = 0; nb < N; nb++)
			{
				if ((nb_tmp = available_nbs[nb][inc_line][col]))
				{
					if (high_low_nb < nb_tmp)
						high_low_nb = nb_tmp;
					break ;
				}
			}
		}
	}
	return (ref == high_low_nb) ? 0 : high_low_nb;
}

/**
 * @brief
 * Remove impossible values when only one number is left for a clue.
 *
 * Based on the direction and the current grid state, this function removes
 * values that would make it impossible to satisfy the corresponding clue.
 *
 * It targets the edge cell affected by the clue.
 *
 * @param way             Direction of the clue
 * @param line            Line index
 * @param col             Column index
 * @param solution        Current solution grid
 * @param available_nbs   3D array of available numbers
 */
void	remove_possibilities_onlfc(Direction way, int line, int col, int **solution, int ***available_nbs)
{
	int high_low_nb, ref;

	if (way == RTL)
		col = 0;
	else if (way == LTR)
		col = N - 1;
	else if (way == TTB)
		line = 0;
	else
		line = N - 1;
	if (solution[line][col])
		return ;
	for (int nb = NB(1); nb < N; nb++)
		if ((ref = available_nbs[nb][line][col]))
			break ;
	high_low_nb = highest_low_nb(way, ref, line, col, solution, available_nbs);
	if (!high_low_nb)
		return ;
	while (--high_low_nb >= 0)
	{
		if (available_nbs[high_low_nb][line][col])
			available_nbs[high_low_nb][line][col] = 0;
	}
}

/**
 * @brief
 * Check if only one additional tower can still satisfy a clue.
 *
 * Counts how many towers are already visible from a given direction.
 * If exactly one more tower is required to reach the clue value,
 * this function returns true.
 *
 * @param way         Direction of the clue
 * @param line        Line index
 * @param col         Column index
 * @param clues       Array of clues
 * @param solution    Current solution grid
 *
 * @return
 * true if only one tower is missing to satisfy the clue, false otherwise.
 */
bool	one_nb_left_for_clue(Direction way, int line, int col, int *clues, int **solution)
{
	int clue, last_nb = 0, towers_seen = 1;

	if (way == LTR)
	{
		clue = clues[left_cond_nb(line)];
		for (int inc_col = 0; solution[line][inc_col] != N; inc_col++)
		{
			if (last_nb < solution[line][inc_col])
			{
				towers_seen++;
				last_nb = solution[line][inc_col];
			}
		}
	}
	else if (way == RTL)
	{
		clue = clues[right_cond_nb(line)];
		for (int inc_col = N; solution[line][inc_col] != N; inc_col--)
		{
			if (last_nb < solution[line][inc_col])
			{
				towers_seen++;
				last_nb = solution[line][inc_col];
			}
		}
	}
	else if (way == TTB)
	{
		clue = clues[col];
		for (int inc_line = 0; solution[inc_line][col] != N; inc_line++)
		{
			if (last_nb < solution[inc_line][col])
			{
				towers_seen++;
				last_nb = solution[inc_line][col];
			}
		}
	}
	else
	{
		clue = clues[bottom_cond_nb(col)];
		for (int inc_line = N - 1; solution[inc_line][col] != N; inc_line--)
		{
			if (last_nb < solution[inc_line][col])
			{
				towers_seen++;
				last_nb = solution[inc_line][col];
			}
		}
	}
	return (towers_seen == clue - 1);
}

/**
 * @brief
 * Handle special case when the clue equals 2.
 *
 * Depending on the position of the tallest tower and the grid state,
 * this function:
 * 
 * - removes the tallest value from forbidden positions
 * 
 * - or directly places the only possible value if forced
 *
 * This applies to all four directions.
 *
 * @param way             Direction of the clue
 * @param pos_7           Position of the tallest number in the line/column
 * @param line            Line index
 * @param col             Column index
 * @param available_nbs   3D array of available numbers
 * @param solution        Current solution grid
 */
void	remv_six_or_put_fst_nb(Direction way, int pos_7, int line, int col, int ***available_nbs, int **solution)
{
	if (way == LTR)
	{
		if (pos_7 > 1 && !solution[line][pos_7 - 1] && available_nbs[NB(N - 1)][line][pos_7 - 1])
			available_nbs[NB(N - 1)][line][pos_7 - 1] = 0;
		if (!solution[line][0])
		{
			if (last_boxs_are_filled(way, solution, line, col))
			{
				int nb = N - 2;
				while (nb >= 0 && !available_nbs[nb][line][0])
					nb--;
				set_valid_pos(nb, line, 0, available_nbs, solution);
			}
			else if (last_boxs_arent_filled(way, solution, line, col))
			{
				int low_limit = -1;
				for (int inc_col = pos_7 - 1; inc_col >= 0; inc_col--)
					low_limit++;
				while (--low_limit >= 0)
					available_nbs[low_limit][0][col] = 0;
			}
		}
	}
	else if (way == RTL)
	{
		if (pos_7 < N - 2 && !solution[line][pos_7 + 1] && available_nbs[NB(N - 1)][line][pos_7 + 1])
			available_nbs[NB(N - 1)][line][pos_7 + 1] = 0;
		if (!solution[line][N - 1])
		{
			if (last_boxs_are_filled(way, solution, line, col))
			{
				int nb = N - 2;
				while (nb >= 0 && !available_nbs[nb][line][N - 1])
					nb--;
				set_valid_pos(nb, line, N - 1, available_nbs, solution);
			}
			else if (last_boxs_arent_filled(way, solution, line, col))
			{
				int low_limit = -1;
				for (int inc_line = pos_7 + 1; inc_line <= N - 1; inc_line++)
					low_limit++;
				while (--low_limit >= 0)
					available_nbs[low_limit][line][N - 1] = 0;
			}
		}
	}
	else if (way == TTB)
	{
		if (pos_7 > 1 && !solution[pos_7 - 1][col] && available_nbs[NB(N - 1)][pos_7 - 1][col])
			available_nbs[NB(N - 1)][pos_7 - 1][col] = 0;
		if (!solution[0][col])
		{
			if (last_boxs_are_filled(way, solution, line, col))
			{
				int nb = N - 2;
				while (nb >= 0 && !available_nbs[nb][0][col])
					nb--;
				set_valid_pos(nb, 0, col, available_nbs, solution);
			}
			else if (last_boxs_arent_filled(way, solution, line, col))
			{
				int low_limit = -1;
				for (int inc_line = pos_7 - 1; inc_line >= 0; inc_line--)
					low_limit++;
				while (--low_limit >= 0)
					available_nbs[low_limit][line][0] = 0;
			}
		}
	}
	else
	{
		if (pos_7 < N - 2 && !solution[pos_7 + 1][col] && available_nbs[NB(N - 1)][pos_7 + 1][col])
			available_nbs[NB(N - 1)][pos_7 + 1][col] = 0;
		if (!solution[N - 1][col])
		{
			if (last_boxs_are_filled(way, solution, line, col))
			{
				int nb = N - 2;
				while (nb >= 0 && !available_nbs[nb][N - 1][col])
					nb--;
				set_valid_pos(nb, N - 1, col, available_nbs, solution);
			}
			else if (last_boxs_arent_filled(way, solution, line, col))
			{
				int low_limit = -1;
				for (int inc_line = pos_7 + 1; inc_line <= N - 1; inc_line++)
					low_limit++;
				while (--low_limit >= 0)
					available_nbs[low_limit][N - 1][col] = 0;
			}
		}
	}
}

/**
 * @brief
 * Perform advanced possibility reduction on the grid.
 *
 * This function applies higher-level deduction rules using:
 * 
 * - clue constraints
 * 
 * - visibility logic
 * 
 * - special cases (e.g. clue == 2)
 *
 * It iterates over all lines and columns and progressively
 * reduces available possibilities.
 *
 * @param available_nbs   3D array of available numbers
 * @param solution        Current solution grid
 * @param clues           Array of clues
 */
void	reduce_possibilities(int ***available_nbs, int **solution, int *clues)
{
	int line, col, pos_line, pos_col;

	for (line = 0, col = 0; line < N; line++, col++)
	{
		if (nbs_found[0][line] != N && (pos_col = is_nb_on_line(N, line, solution)) != -1)
		{
			if (!clues_fullfilled[left_cond_nb(line)] && one_nb_left_for_clue(LTR, line, col, clues, solution))
				remove_possibilities_onlfc(LTR, line, col, solution, available_nbs);
			if (!clues_fullfilled[right_cond_nb(line)] && one_nb_left_for_clue(RTL, line, col, clues, solution))
				remove_possibilities_onlfc(RTL, line, col, solution, available_nbs);
			if (clues[left_cond_nb(line)] == 2)
				remv_six_or_put_fst_nb(LTR, pos_col, line, col, available_nbs, solution);
			if (clues[right_cond_nb(line)] == 2)
				remv_six_or_put_fst_nb(RTL, pos_col, line, col, available_nbs, solution);
		}
		if (nbs_found[1][col] != N && (pos_line = is_nb_on_col(N, col, solution)) != -1)
		{
			if (!clues_fullfilled[col] && one_nb_left_for_clue(TTB, line, col, clues, solution))
				remove_possibilities_onlfc(TTB, line, col, solution, available_nbs);
			if (!clues_fullfilled[bottom_cond_nb(col)] && one_nb_left_for_clue(BTT, line, col, clues, solution))
				remove_possibilities_onlfc(BTT, line, col, solution, available_nbs);
			if (clues[col] == 2)
				remv_six_or_put_fst_nb(TTB, pos_line, line, col, available_nbs, solution);
			if (clues[bottom_cond_nb(col)] == 2)
				remv_six_or_put_fst_nb(BTT, pos_line, line, col, available_nbs, solution);
		}
	}
}
