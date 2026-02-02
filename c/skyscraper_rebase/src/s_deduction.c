#include "skyscraper.h"

/**
 * @brief
 * Handle a clue equal to N by placing all numbers in ascending order
 * along the corresponding line or column.
 *
 * Also applies additional constraints related to clue 2 if applicable.
 *
 * @param cur_clue       The index of the current clue
 * @param available_nbs the array of possible numbers
 * @param solution      The solution grid
 * @param clues         The array of clues
 */
void	actualise_min_clue(int cur_clue, int available_nbs[N][N][N], int **solution)
{
	int way = cur_clue / N;// to know on which side the clue is

	if (way == 0)// if the clue is at the top
		set_valid_pos(N, 0, top_cond_nb(cur_clue), available_nbs, solution);
	else if (way == 1)// if the clue is on the right
		set_valid_pos(N, right_cond_nb(cur_clue), N - 1, available_nbs, solution);
	else if (way == 2)// if the clue is at the bottom
		set_valid_pos(N, N - 1, bottom_cond_nb(cur_clue), available_nbs, solution);
	else// if the clue is on the left
		set_valid_pos(N, left_cond_nb(cur_clue), 0, available_nbs, solution);
}

/**
 * @brief
 * Handle a clue equal to N by placing all numbers in ascending order
 * along the corresponding line or column.
 *
 * Also applies additional constraints related to clue 2 if applicable.
 *
 * @param cur_clue       The index of the current clue
 * @param available_nbs the array of possible numbers
 * @param solution      The solution grid
 * @param clues         The array of clues
 */
void	actualise_max_clue(int cur_clue, int available_nbs[N][N][N], int **solution)
{
	int way = cur_clue / N;// to know on which side the clue is
	/* {upper clue, right clue, lower clue, left clue} */
	int nbs[4] = {1, N, N, 1};//starting number
	int cur_clues[4] = {top_cond_nb(cur_clue), right_cond_nb(cur_clue), bottom_cond_nb(cur_clue), left_cond_nb(cur_clue)};// the clue position on a line (0 to N - 1)

	const int i = (nbs[way] == 0) ? 1 : -1;
	// if the clue is on a column
	if (way == 0 || way == 2)
	{
		for (int line = 0; line < N; line++)
		{
			set_valid_pos(nbs[way], line, cur_clues[way], available_nbs, solution);
			nbs[way] += i;
		}
	}
	// if the clue is on a line
	else
	{
		for (int col = 0; col < N; col++)
		{
			set_valid_pos(nbs[way], cur_clues[way], col, available_nbs, solution);
			nbs[way] += i;
		}
	}
}

void    put_towers_deduced(int available_nbs[N][N][N], int **solution, int *clues)
{
	for (int i = 0; i < N * 4; i++)
	{
		if (clues[i] == N)//if max clue found, put every tower in ascending order from the clue
			actualise_max_clue(clues[i], available_nbs, solution);
		else if (clues[i] == 1)//if min clue found, put N close to the clue
			actualise_min_clue(clues[i], available_nbs, solution);
	}
}