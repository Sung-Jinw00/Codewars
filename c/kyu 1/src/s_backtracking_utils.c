#include "skyscraper.h"

/**
 * @brief
 * Duplicate or restore a solution grid.
 *
 * Depending on the value of `dest`, this function either:
 * 
 * - saves the current `solution` into `sol_save`
 * 
 * - or restores `solution` from `sol_save`
 *
 * @param sol_save Backup solution array
 * @param solution Current solution grid
 * @param dest     0 to save `solution` → `sol_save`, non-zero to restore `sol_save` → `solution`
 */
void	sol_dup(int sol_save[N][N], int **solution, int dest)
{
	if (dest == 0)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				sol_save[i][j] = solution[i][j];
	}
	else
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				solution[i][j] = sol_save[i][j];
	}
}

/**
 * @brief
 * Compute the number of available possibilities for each cell.
 *
 * This function fills `available_amount` with the count of possible
 * numbers remaining for every box of the grid, based on `available_nbs`.
 *
 * @param available_amount 2D array storing the number of possibilities per cell
 * @param available_nbs    3D array of possible numbers
 */
void set_available_amount(int available_amount[N][N], int ***available_nbs)
{
	for (int line = 0; line < N; line++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int nb = 0; nb < N; nb++)
			{
				if (available_nbs[nb][line][col])
					available_amount[line][col]++;
			}
		}
	}
}

/**
 * @brief
 * Find the position of the cell with the least available possibilities.
 *
 * Starting from (`start_line`, `start_col`), this function scans the grid and
 * updates `pos` with the coordinates of the cell that has the smallest number
 * of possibilities greater than 1.
 *
 * @param start_line       Starting line index
 * @param start_col        Starting column index
 * @param pos              Output position `{line, column}`
 * @param available_amount 2D array of possibility counts
 */
void	get_pos_least_amount(int start_line, int start_col, int pos[2], int available_amount[N][N])
{
	int line = start_line, col = start_col;
	if (line || col)
	{
		if (col + 1 == N)
		{
			col = 0;
			line++;
		}
		else
			col++;
		if (line == N)
			return ;
	}
	while (line < N)
	{
		while (col < N)
		{
			if (available_amount[line][col] != 1)
				break ;
			col++;
		}
		if (available_amount[line][col] != 1)
				break ;
		line++;
		col = 0;
	}
	int least_amount = available_amount[line][col];
	while (line < N)
	{
		while (col < N)
		{
			int cur_amount = available_amount[line][col];
			if (cur_amount > 1 && cur_amount < least_amount)
			{
				least_amount = cur_amount;
				pos[0] = line;
				pos[1] = col;
				if (cur_amount == 2)
					return ;
			}
			col++;
		}
		line++;
		col = 0;
	}
}
