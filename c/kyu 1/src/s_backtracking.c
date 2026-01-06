/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_backtracking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/07 20:19:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

void	put_guessable_nbs(int ***available_nbs, int **solution, int *clues)
{
	for (bool changes = true; changes != false;)
	{
		changes = set_one_possibility_clue(available_nbs, solution, clues);
		if (!changes)
			changes = set_one_possibility_rules(available_nbs, solution, clues);
		if (changes)
			reduce_possibilities(available_nbs, solution, clues);
	}
}

int	least_available_nb(int ***available_nbs, int available_amount[TAB_SIZE][TAB_SIZE], int pos[2])
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
	while (nb < TAB_SIZE)
	{
		if (available_nbs[nb][pos[0]][pos[1]])
			return (available_nbs[nb][pos[0]][pos[1]]);
		nb++;
	}
	if (nb == TAB_SIZE)
		nb = 0;
	return (-1);
}

bool	all_boxes_filled(int **solution)
{
	for (int line = 0; line < TAB_SIZE - 1; line++)
	{
		for (int col = 0; col < TAB_SIZE - 1; col++)
		{
			if (!solution[line][col])
				return (false);
		}
	}
	return (true);
}

bool	towers_visible(reading_way way, int line, int col, int **solution, int clue)
{
	int towers_visibl = 2, prev_tower = solution[line][col];

	if (prev_tower == TAB_SIZE)
		return (clue == 1);
	if (way == TTB)
	{
		while (solution[++line][col] != TAB_SIZE)
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
		while (solution[line][--col] != TAB_SIZE)
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
		while (solution[--line][col] != TAB_SIZE)
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
		while (solution[line][++col] != TAB_SIZE)
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
	for (int i = 0; i < TAB_SIZE * 4; i++)
	{
		if (clues[i])
		{
			if (i < TAB_SIZE && !towers_visible(TTB, 0, i, solution, clues[i]))
				return (false);
			else if (i < TAB_SIZE * 2 && !towers_visible(RTL, i % TAB_SIZE, TAB_SIZE - 1, solution, clues[i]))
				return (false);
			else if (i < TAB_SIZE * 3 && !towers_visible(BTT, TAB_SIZE - 1, i % TAB_SIZE, solution, clues[i]))
				return (false);
			else if (!towers_visible(LTR, i % TAB_SIZE, 0, solution, clues[i]))
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
	print_array(solution, 0, clues);
	int available_amount[TAB_SIZE][TAB_SIZE] = {0}, pos[2] = {0};
	set_available_amount(available_amount, available_nbs);

	while (least_available_nb(available_nbs, available_amount, pos) == -1)
		get_pos_least_amount(pos[0], pos[1], pos, available_amount);
	if (pos[0] >= TAB_SIZE && pos[1] >= TAB_SIZE)
		return (false);
	solution[pos[0]][pos[1]] = least_available_nb(available_nbs, available_amount, pos);
	put_guessable_nbs(available_nbs, solution, clues);
	if (!all_boxes_filled(solution))
		return (put_random_nb(available_nbs, solution, clues));
	return (all_conditions_respected(solution, clues));
}

int	**backtracking_solve(int ***available_nbs, int **solution, int *clues)
{
	int sol_save[TAB_SIZE][TAB_SIZE] = {0};
	sol_dup(sol_save, solution, 0);
	if (put_random_nb(available_nbs, solution, clues))
		return (solution);
	sol_dup(sol_save, solution, 1);
	return (solution);
}
