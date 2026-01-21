/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_clues_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2026/01/19 15:28:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

/**
 * @brief
 * Put all numbers in ascending order on the whole line or column that match the clue
 * 
 * @param solution		the solution board
 * @param available_nbs	the array of possible numbers
 * @param clues			the array of clues
 * @param pos			the current position {line, column}
 */
void	clue_2_and_max_nb(int **solution, int ***available_nbs, int clues[N * 4], int pos[2])
{
	//if i'm not on the sides of the board and the answer is N, i return
	if (!( (pos[0] == 0 || pos[0] == N - 1)
		&& (pos[1] == 0 || pos[1] == N - 1)
		&& solution[pos[0]][pos[1]] == N))
		return ;
	//check condition at the opposite side of my current N
	bool conditions[4] = {
		//if i'm on the first line and the bottom condition at the column is 2
		pos[0] == 0		&& clues[bottom_cond_nb(pos[1])] == 2,
		//if i'm on the last line and the top condition at the column is 2
		pos[0] == N - 1 && clues[rev_nb(pos[1])] == 2,
		//if i'm on the first column and the right condition at the line is 2
		pos[1] == 0		&& clues[right_cond_nb(pos[0])] == 2,
		//if i'm on the last column and the left condition at the line is 2
		pos[1] == N - 1 && clues[left_cond_nb(pos[0])] == 2
	};
	int lines[4]	=	{N - 1, 0, pos[0], pos[0]};
	int columns[4]	=	{pos[1], pos[1], N - 1, 0};
	for (int i = 0; i < 4; i++)
		if (conditions[i])
			set_valid_pos(NB(N - 1), lines[i], columns[i], available_nbs, solution);
}

/**
 * @brief
 * Remove N - 1 in the second box away from the clue containing 2,
 * if N - 1 is placed at this position the clue can't be fullfilled.
 */
void	remv_before_max_nb(int cur_clue, int ***available_nbs)
{
	//set the side
	int i = cur_clue / N;
	//{upper clue, right clue, lower clue, left clue}
	int *poss[4] = {
		(int[2]){1, cur_clue},
		(int[2]){cur_clue - N - 1, 1},
		(int[2]){1, N * 3 - cur_clue - 1},
		(int[2]){N * 4 - cur_clue - 1, 1}
	};
	available_nbs[NB(N - 1)][poss[i][0]][poss[i][1]] = 0;
}

/**
 * @brief
 * Put all numbers in ascending order on the whole line or column that match the clue
 * 
 * @param cur_clue		the current clue position
 * @param available_nbs	the array of possible numbers
 * @param solution		the solution board
 * @param clues			the array of clues
 */
void	actualise_max_clue(int cur_clue, int ***available_nbs, int **solution, int *clues)
{
	clues_fullfilled[cur_clue] = true;// clue is fullfilled
	int i = cur_clue / N;// to know on which side the clue is
	/* {upper clue, right clue, lower clue, left clue} */
	int nbs[4] = {1, N, N, 1};//starting number
	int cur_clues[4] = {cur_clue, cur_clue - N, N * 3 - cur_clue, N * 4 - cur_clue};// the clue position on a line (0 to N - 1)
	int *pos_range[4] = {
		(int[2]){0, cur_clue},
		(int[2]){cur_clue - N, 0},
		(int[2]){0, N * 3 - cur_clue},
		(int[2]){N * 4 - cur_clue, 0}}; //in which side the numbers will be placed
	// if the clue is on a column
	if (i == 0 || i == 3)
		actualise_all_column(NB(nbs[i]), cur_clues[i], available_nbs, solution);
	// if the clue is on a line
	else
		actualise_all_line(NB(nbs[i]), cur_clues[i], available_nbs, solution);
	clue_2_and_max_nb(solution, available_nbs, clues, pos_range[i]);
}

/**
 * @brief
 * This function put n on a line or column if 1 is found in the clues
 */
void	actualise_max_nb(int cur_clue, int ***available_nbs, int **solution, int *clues)
{
	clues_fullfilled[cur_clue] = true;//clue is fullfilled
	int i = cur_clue / N;//to know which clue side is it
	//{upper clue, right clue, lower clue, left clue}
	int *pos_range[4] = {
		(int[2]){0, cur_clue},
		(int[2]){cur_clue - N, 0},
		(int[2]){0, N * 3 - cur_clue},
		(int[2]){N * 4 - cur_clue, 0}}; //in which side the numbers will be placed
	int *cur_clues[4] = {
		(int[2]){0, cur_clue},
		(int[2]){cur_clue - N - 1, 0},
		(int[2]){0, N * 3 - cur_clue - 1},
		(int[2]){N * 4 - cur_clue - 1, 0}
	};
	set_valid_pos(NB(N), cur_clues[i][0], cur_clues[i][1], available_nbs, solution);
	clue_2_and_max_nb(solution, available_nbs, clues, pos_range[i]);
}

/**
 * @brief
 * The limit of possible numbers is set depending on the distance with the clue.
 * For example if the clue is 4, you can't have more than N - 3 in the first box because it would hide the towers behind.
 * By following this logic, the second box have a limit of N - 2, and the third box have a limit of N - 1.
 * 
 * so for `N` the max number, `clue` the amount of towers to show and `step` the number of box away from clue, starting at 1:
 * 
 * limit_in_box = `N` - `clue` + `step`
 * 
 * As long as `clue` is above `step`
 * 
 * @param clue			the clue
 * @param cur_clue		the clue pos
 * @param available_nbs	the array of possible numbers
 */
void	set_limit_nbs(int clue, int cur_clue, int ***available_nbs)
{
	//select which side the clue is
	int side = cur_clue / N;
	//get the position in a column or line
	int pos = cur_clue % N;

	for (int step = 0; step < clue; step++)
	{
		int line, col, limit_in_box = N - clue + (step + 1);//step start at 0 for lines and columns
		//move in the lines or columns with step
		if (side == 0)		{line = step;         col = pos;}
		else if (side == 1)	{line = pos;          col = N - 1 - step;}
		else if (side == 2)	{line = N - 1 - step; col = N - 1 - pos;}
		else				{line = N - 1 - pos;  col = step;}
		//remove all numbers above limit_in_box (included because our array start at 0)
		for (int nb = limit_in_box; nb < N; nb++)
			available_nbs[nb][line][col] = 0;
	}
}

/**
 * @brief
 * Check if only one number is available in the current box
 * 
 * @param solution		the solution board
 * @param available_nbs	the array of possible numbers
 * @param nb			the number to test
 * @param ptr_line		a pointer on line
 * @param ptr_col		a pointer on column
 */
bool	only_one_possibility_clue(int **solution, int ***available_nbs, int nb, int *ptr_line, int *ptr_col)
{
	int	count = 0, valid_pos, dup_line = *ptr_line, dup_col = *ptr_col;

	// if not all numbers has been found on the line
	if (nbs_found[0][dup_line] != N)
	{
		for (int col = 0; col < N; col++)
		{
			//if the number is available and solution is empty
			if (available_nbs[nb][dup_line][col] != 0 && !solution[dup_line][col])
			{
				//i put the pointer on the column
				valid_pos = col;
				count++;
			}
		}
		//if there's only one number
		if (count == 1)
			return (*ptr_col = valid_pos, true);//i return
	}
	// if not all numbers has been found on the column
	if (nbs_found[1][dup_col] != N)
	{
		//same for columns
		for (int line = 0; line < N; line++)
		{
			if (available_nbs[nb][line][dup_col] != 0 && !solution[line][dup_col])
			{
				valid_pos = line;
				count++;
			}
		}
		if (count == 1)
			return (*ptr_line = valid_pos, true);
	}
	return (false);
}

/**
 * @brief
 * Look in diagonal if one line or column has only one possility for a number and set it in answer tab
 * 
 * @param available_nbs	the array of possible numbers
 * @param solution		the solution board
 * @param clues			the array of clues
 */
bool	set_one_possibility_clue(int ***available_nbs, int **solution, int *clues)
{
	bool changes = false;
	int line_backup;

	for (int line = 0, col = 0; line < N; line++, col++)
	{
		line_backup = line;
		for (int nb = 0; nb < N; nb++)
		{
			//if there's only one possible number
			if (only_one_possibility_clue(solution, available_nbs, nb, &line, &col))
			{
				//the pointers already have the right coordinates
				set_valid_pos(nb, line, col, available_nbs, solution);
				if (solution[line][col] == N)
					clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){line, col});
				changes = true;
				break;
			}
		}
		col = line = line_backup;
	}
	return (changes);
}
