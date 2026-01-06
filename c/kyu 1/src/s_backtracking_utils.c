/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_backtracking_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/07 20:14:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

void	sol_dup(int sol_save[TAB_SIZE][TAB_SIZE], int **solution, int dest)
{
	if (dest == 0)
	{
		for (int i = 0; i < TAB_SIZE; i++)
			for (int j = 0; j < TAB_SIZE; j++)
				sol_save[i][j] = solution[i][j];
	}
	else
	{
		for (int i = 0; i < TAB_SIZE; i++)
			for (int j = 0; j < TAB_SIZE; j++)
				solution[i][j] = sol_save[i][j];
	}
}

/* 
display *available_amount[0]@7
display *available_amount[1]@7
display *available_amount[2]@7
display *available_amount[3]@7
display *available_amount[4]@7
display *available_amount[5]@7
display *available_amount[6]@7

*/

void set_available_amount(int available_amount[TAB_SIZE][TAB_SIZE], int ***available_nbs)
{
	for (int line = 0; line < TAB_SIZE; line++)
	{
		for (int col = 0; col < TAB_SIZE; col++)
		{
			for (int nb = 0; nb < TAB_SIZE; nb++)
			{
				if (available_nbs[nb][line][col])
					available_amount[line][col]++;
			}
		}
	}
}

void	get_pos_least_amount(int start_line, int start_col, int pos[2], int available_amount[TAB_SIZE][TAB_SIZE])
{
	int line = start_line, col = start_col;
	if (line || col)
	{
		if (col + 1 == TAB_SIZE)
		{
			col = 0;
			line++;
		}
		else
			col++;
		if (line == TAB_SIZE)
			return ;
	}
	while (line < TAB_SIZE)
	{
		while (col < TAB_SIZE)
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
	while (line < TAB_SIZE)
	{
		while (col < TAB_SIZE)
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
