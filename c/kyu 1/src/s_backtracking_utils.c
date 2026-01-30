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
		col = empty_box % N - 1;
	}
	for (; line < N; line++)
	{
		for (; col < N; col++)
			if (!solution[line][col])
				return ((line + 1) * N - (N - (col + 1)));
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
	int line = empty_box / N, col = empty_box % N - 1;

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
	int empty_box = -2;
	
	while ((empty_box = find_empty_box(solution, empty_box + 1)) != -1)
	{
		for (int nb = NB(1); nb < N; nb++)
			if (available_nbs[nb][empty_box / N][empty_box % N - 1])
				return false;
	}
	return true;
}