/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_backtracking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 02:06:35 by marvin           ###   ########.fr       */
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

int	least_available_nb(int ***available_nbs, int pos[2])
{
	static int nb = 0;
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

bool	put_random_nb(int ***available_nbs, int **solution, int *clues)
{
	while (!all_boxes_filled(solution))
	{
		int available_amount[TAB_SIZE][TAB_SIZE] = {0}, pos[2] = {0};
		set_available_amount(available_amount, available_nbs);
		while ((solution[pos[0]][pos[1]] = least_available_nb(available_nbs, pos)) == -1)
			get_pos_least_amount(pos[0], pos[1], pos, available_amount);
		put_guessable_nbs(available_nbs, solution, clues);
	}
	return (false);
}

void	backtracking_solve(int ***available_nbs, int **solution, int *clues)
{
	int sol_save[TAB_SIZE][TAB_SIZE] = {0};
	sol_dup(sol_save, solution);
	put_random_nb(available_nbs, solution, clues);
}
