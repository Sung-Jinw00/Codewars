/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 01:32:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

int	rev_pos(int pos)
{
	return (TAB_SIZE - pos - 1);
}

int	left_cond_nb(int line)
{
	return (TAB_SIZE * 3 + rev_pos(line));
}

int	right_cond_nb(int line)
{
	return (TAB_SIZE + line);
}

int	bottom_cond_nb(int col)
{
	return (TAB_SIZE * 2 + rev_pos(col));
}

int	is_nb_on_line(int nb, int line, int **solution)
{
	for (int col = 0; col < TAB_SIZE; col++)
		if (solution[line][col] == nb)
			return (col);
	return (0);
}

int	is_nb_on_col(int nb, int col, int **solution)
{
	for (int line = 0; line < TAB_SIZE; line++)
		if (solution[line][col] == nb)
			return (line);
	return (0);
}

bool	lacking_towers(reading_way way, int line, int col, int **solution)
{
	if (way == LTR)
	{
		for (int inc_col = 0; inc_col < TAB_SIZE && solution[line][inc_col] != TAB_SIZE; inc_col++)
			if (!solution[line][inc_col])
				return (true);
	}
	else if (way == RTL)
	{
		for (int inc_col = TAB_SIZE - 1; inc_col >= 0 && solution[line][inc_col] != TAB_SIZE; inc_col--)
			if (!solution[line][inc_col])
				return (true);
	}
	else if (way == TTB)
	{
	for (int inc_line = 0; line < TAB_SIZE && solution[inc_line][col] != TAB_SIZE; inc_line++)
		if (!solution[inc_line][col])
			return (true);
	}
	else
	{
		for (int inc_line = TAB_SIZE - 1; inc_line >= 0 && solution[inc_line][col] != TAB_SIZE; inc_line--)
			if (!solution[inc_line][col])
				return (true);
	}
	return (false);
}

bool	last_boxs_are_filled(reading_way way, int **solution, int line, int col)
{
	if (way == LTR)
	{
		while (col < TAB_SIZE)
			if (!solution[line][col++])
				return (false);
	}
	else if (way == RTL)
	{
		while (col >= 0)
			if (!solution[line][col--])
				return (false);
	}
	else if (way == BTT)
	{
		while (line >= 0)
			if (!solution[line--][col])
				return (false);
	}
	else
	{
		while (line < TAB_SIZE)
			if (!solution[line++][col])
				return (false);
	}
	return (true);
}

bool	last_boxs_arent_filled(reading_way way, int **solution, int line, int col)
{
	if (way == LTR)
	{
		while (--col >= 0)
			if (solution[line][col])
				return (false);
	}
	else if (way == RTL)
	{
		while (++col < TAB_SIZE)
			if (solution[line][col])
				return (false);
	}
	else if (way == BTT)
	{
		while (++line < TAB_SIZE)
			if (solution[line][col])
				return (false);
	}
	else
	{
		while (--line >= 0)
			if (solution[line][col])
				return (false);
	}
	return (true);
}

int	tiniest_nb_in_box(int ***available_nbs, int start_nb, int line, int col)
{
	for (int nb = start_nb; nb < TAB_SIZE; nb++)
		if (available_nbs[nb][line][col])
			return (available_nbs[nb][line][col]);
	return (0);
}

int	***init_availability(void)
{
	int ***available_nbs = malloc(sizeof(int **) * TAB_SIZE);

	for (int i = 0; i < TAB_SIZE; i++)
	{
		available_nbs[i] = malloc(sizeof(int *) * TAB_SIZE);
		for (int j = 0; j < TAB_SIZE; j++)
		{
			available_nbs[i][j] = malloc(sizeof(int) * TAB_SIZE);
			for (int k = 0; k < TAB_SIZE; k++)
				available_nbs[i][j][k] = i + 1;
		}
	}
	return (available_nbs);
}
