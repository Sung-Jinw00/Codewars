#include "skyscraper.h"

/**
 * @brief
 * Copy `src` in `dest`
 *
 * @param dest		The solution duplicate
 * @param src		The source solution
 */
void	sol_dup(int **dest, int **src)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dest[i][j] = src[i][j];
}

/**
 * @brief
 * Copy the shittu
 * 
 * @param dest		The array duplicate
 * @param src		The source array
 * 
 */
void copy_available(int ***dest, int ***src)
{
	for (int nb = NB(1); nb < N; nb++)
		sol_dup(dest[nb], src[nb]);
}

/**
 *
 * @param available_nbs		The numbers available in the board
 * 
 * @return a duplicate of `available_nbs`
 */
int	***available_nbs_dup(int ***available_nbs)
{
	int ***dup_available_nbs = init_availability();
	for (int nb = NB(1); nb < N; nb++)
		sol_dup(dup_available_nbs[nb], available_nbs[nb]);
	return dup_available_nbs;
}

/**
 * @brief
 * Find the first empty box and return the position in an int.
 *
 * @param solution      The solution grid
 * @param start      	Where the function should start to search for empty boxes
 *
 * @return The position of the first empty box or -1 if everything is filled
 *
 * @note The position is returned as if the solution array was a simple array of ints, same for start.
 */
int find_empty_box(int **solution, int start)
{
	if (!solution)
		return -1;
	int empty_box = start, line = 0, col = 0;
	if (empty_box >= 0)
	{
		line = empty_box / N;
		col = empty_box % N;
	}
	for (; line < N; line++)
	{
		for (; col < N; col++)
			if (!solution[line][col])
				return (line * N + col);
		col = 0;
	}
	return -1;
}

/**
 * @brief
 * Get the numbers available in an empty box
 * 
 * @param available_nbs The numbers available in the board
 * @param empty_box		The position of the empty box
 * @param len			A pointer on an int that will get the len of the array returned
 * 
 * @return The array of available numbers in the box
 */
void	get_available_nbs_in_box(int ***available_nbs, int empty_box, int nbs[N], int *len)
{
	int line = empty_box / N, col = empty_box % N;

	*len = 0;
	for (int nb = NB(1); nb < N; nb++)
	{
		if (available_nbs[nb][line][col])
		{
			nbs[*len] = available_nbs[nb][line][col];
			(*len)++;
		}
	}
}

/**
 * @brief
 * Find if there's no possible numbers left in empty boxes
 * 
 * @param available_nbs The numbers available in the board
 * @param solution		The answer sheet
 * 
 * @return `false` if a number is usable in a box, else `true`
 */
bool no_possible_numbers(int **solution, int ***available_nbs)
{
	for (int line = 0; line < N; line++)
	{
		for (int col = 0; col < N; col++)
		{
			if (solution[line][col] != 0)
				continue;
			bool has_possible = false;
			for (int nb = 0; nb < N; nb++)
			{
				if (available_nbs[nb][line][col])
				{
					has_possible = true;
					break;
				}
			}
			if (!has_possible)
				return true;
		}
	}
	return false;
}

bool clues_respected(int **solution, int *clues)
{
	for (int i = 0; i < N * 4;i++)
	{
		if (!clues[i])
		continue;
		if (!((i < N && visible_towers(TTB, 0, i, solution) == clues[i])
			|| (i >= N && i < N * 2 && visible_towers(RTL, i - N, 0, solution) == clues[i])
			|| (i >= N * 2 && i < N * 3 && visible_towers(BTT, 0, rev_nb(i - N * 2), solution) == clues[i])
			|| (i >= N * 3 && i < N * 4 && visible_towers(LTR, rev_nb(i - N * 3), 0, solution) == clues[i])))
			return false;
	}
	return true;
}

bool	different_on_line(int **solution, int line)
{
	int start = 1, col = start, nb = solution[line][0];

	while (start < N)
	{
		if (solution[line][col] == nb)
			return false;
		col++;
		if (col == N)
		{
			col = ++start;
			nb = solution[line][col - 1];
		}
	}
	return true;
}

bool	different_on_col(int **solution, int col)
{
	int start = 1, line = start, nb = solution[0][col];

	while (start < N)
	{
		if (solution[line][col] == nb)
			return false;
		line++;
		if (line == N)
		{
			line = ++start;
			nb = solution[line - 1][col];
		}
	}
	return true;
}

bool	different_towers(int **solution)
{
	for (int i = 0; i < N; i++)
		if (!different_on_col(solution, i) || !different_on_line(solution, i))
			return false;
	return (true);
}