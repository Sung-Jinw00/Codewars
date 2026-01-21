/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_backtracking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2026/01/19 16:55:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

/**
 * @brief
 * find all one possibilities numbers in the answer sheet and actualise available numbers
 * 
 * @param available_nbs	the array of possible numbers
 * @param solution		the solution board
 * @param clues			the array of clues
 */
void	put_guessable_nbs(int ***available_nbs, int **solution, int *clues)
{
	for (bool changes = true; changes != false;)
	{
		changes = set_one_possibility_clue(available_nbs, solution, clues);
		if (!changes)
			changes = set_one_possibility_rules(available_nbs, solution, clues);
		else
			reduce_possibilities(available_nbs, solution, clues);
	}
	print_all_available_each_box(available_nbs, clues, solution);
}

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

/* 
display *solution[0]@7
display *solution[1]@7
display *solution[2]@7
display *solution[3]@7
display *solution[4]@7
display *solution[5]@7
display *solution[6]@7

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

int	**backtracking_solve(int ***available_nbs, int **solution, int *clues)
{
	int sol_save[N][N] = {0};
	sol_dup(sol_save, solution, 0);
	if (put_random_nb(available_nbs, solution, clues))
		return (solution);
	sol_dup(sol_save, solution, 1);
	return (solution);
}
