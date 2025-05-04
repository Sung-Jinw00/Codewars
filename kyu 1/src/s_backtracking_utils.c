/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_backtracking_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 02:06:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

void	sol_dup(int sol_save[TAB_SIZE][TAB_SIZE], int **solution)
{
	for (int i = 0; i < TAB_SIZE; i++)
		for (int j = 0; j < TAB_SIZE; j++)
			sol_save[i][j] = solution[i][j];
}

void	set_available_amount(int available_amount[TAB_SIZE][TAB_SIZE], int ***available_nbs)
{
	for (int line = 0; line < TAB_SIZE - 1; line++)
	{
		for (int col = 0; col < TAB_SIZE - 1; col++)
		{
			for (int nb = 0; nb < TAB_SIZE - 1; nb++)
			{
				if (available_nbs[nb][line][col])
					available_amount[line][col]++;
			}
		}
	}
}

void	get_pos_least_amount(int start_line, int start_col, int pos[2], int available_amount[TAB_SIZE][TAB_SIZE])
{
	if (start_line || start_col)
	{
		if (start_col + 1 == TAB_SIZE)
		{
			start_col = 0;
			start_line++;
		}
		else
			start_col++;
		if (start_line == TAB_SIZE)
			return ;
	}
	int least_amount = available_amount[start_line][start_col];

	for (int line = start_line; line < TAB_SIZE - 1; line++)
	{
		for (int col = start_col; col < TAB_SIZE - 1; col++)
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
		}
	}
}
