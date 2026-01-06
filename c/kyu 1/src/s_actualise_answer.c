/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper copy 4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/03 19:49:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

void	actualise_valid_pos(int nb, int line, int col, int ***available_nbs, int **solution)
{
	for (int col_inc = 0; col_inc < TAB_SIZE; col_inc++)//set every other box on the same line to zero
	{
		if (col_inc != col)
			available_nbs[nb][line][col_inc] = 0;
	}
	for (int line_inc = 0; line_inc < TAB_SIZE; line_inc++)//set every other boxs on the same col to zero
	{
		if (line_inc != line)
			available_nbs[nb][line_inc][col] = 0;
	}
	for (int nb_inc = 0; nb_inc < TAB_SIZE; nb_inc++)//set every other numbers at this position invalid
	{
		if (nb_inc != nb)
			available_nbs[nb_inc][line][col] = 0;
	}
	solution[line][col] = nb + 1;
	nbs_found[0][line]++;
	nbs_found[1][col]++;
}

/* actualise lines from up to bottom and set the solution */
void	actualise_all_lines(int nb, int cur_col, int ***available_nbs, int **solution)
{
	if (nb == TAB_SIZE - 1)//if the max towers was on the bottom
	{
		for (int line = 0; line < TAB_SIZE; line++)
		{
			actualise_valid_pos(nb, line, cur_col, available_nbs, solution);
			nb--;
		}
	}
	else if (nb == 0)
	{
		for (int line = 0; line < TAB_SIZE; line++)
		{
			actualise_valid_pos(nb, line, cur_col, available_nbs, solution);
			nb++;
		}
	}
}

/* actualise columns from left to right and set the solution */
void	actualise_all_cols(int nb, int cur_line, int ***available_nbs, int **solution)
{
	if (nb == TAB_SIZE - 1)//if the max towers was on the right
	{
		for (int col = 0; col < TAB_SIZE; col++)
		{
			actualise_valid_pos(nb, cur_line, col, available_nbs, solution);
			nb--;
		}
	}
	else if (nb == 0)
	{
		for (int col = 0; col < TAB_SIZE; col++)
		{
			actualise_valid_pos(nb, cur_line, col, available_nbs, solution);
			nb++;
		}
	}
}
