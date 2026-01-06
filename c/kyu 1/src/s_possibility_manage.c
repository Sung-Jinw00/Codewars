/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_possibility_manage.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 00:32:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

//─────────────────────────────
// Manage possibilities
//─────────────────────────────

int	highest_low_nb(reading_way way, int ref, int line, int col, int **solution, int ***available_nbs)
{
	int high_low_nb = ref, nb_tmp;

	if (way == LTR)
	{
		for (int inc_col = 1; !solution[line][inc_col]; inc_col++)
		{
			for (int nb = 0; nb < TAB_SIZE; nb++)
			{
				if ((nb_tmp = available_nbs[nb][line][inc_col]))
				{
					if (high_low_nb < nb_tmp)
						high_low_nb = nb_tmp;
					break ;
				}
			}
		}
	}
	else if (way == RTL)
	{
		for (int inc_col = TAB_SIZE - 2; !solution[line][inc_col]; inc_col--)
		{
			for (int nb = 0; nb < TAB_SIZE; nb++)
			{
				if ((nb_tmp = available_nbs[nb][line][inc_col]))
				{
					if (high_low_nb < nb_tmp)
						high_low_nb = nb_tmp;
					break ;
				}
			}
		}
	}
	else if (way == TTB)
	{
		for (int inc_line = 1; !solution[inc_line][col]; inc_line++)
		{
			for (int nb = 0; nb < TAB_SIZE; nb++)
			{
				if ((nb_tmp = available_nbs[nb][inc_line][col]))
				{
					if (high_low_nb < nb_tmp)
						high_low_nb = nb_tmp;
					break ;
				}
			}
		}
	}
	else
	{
		for (int inc_line = TAB_SIZE - 2; !solution[inc_line][col]; inc_line--)
		{
			for (int nb = 0; nb < TAB_SIZE; nb++)
			{
				if ((nb_tmp = available_nbs[nb][inc_line][col]))
				{
					if (high_low_nb < nb_tmp)
						high_low_nb = nb_tmp;
					break ;
				}
			}
		}
	}
	return (ref == high_low_nb) ? 0 : high_low_nb;
}

void	remove_possibilities_onlfc(reading_way way, int line, int col, int **solution, int ***available_nbs)
{
	int high_low_nb, ref;

	if (way == RTL)
		col = 0;
	else if (way == LTR)
		col = TAB_SIZE - 1;
	else if (way == TTB)
		line = 0;
	else
		line = TAB_SIZE - 1;
	if (solution[line][col])
		return ;
	for (int nb = NB(1); nb < TAB_SIZE; nb++)
		if ((ref = available_nbs[nb][line][col]))
			break ;
	high_low_nb = highest_low_nb(way, ref, line, col, solution, available_nbs);
	if (!high_low_nb)
		return ;
	while (--high_low_nb >= 0)
	{
		if (available_nbs[high_low_nb][line][col])
			available_nbs[high_low_nb][line][col] = 0;
	}
}

bool	one_nb_left_for_clue(reading_way way, int line, int col, int *clues, int **solution)
{
	int clue, last_nb = 0, towers_seen = 1;

	if (way == LTR)
	{
		clue = clues[left_cond_nb(line)];
		for (int inc_col = 0; solution[line][inc_col] != TAB_SIZE; inc_col++)
		{
			if (last_nb < solution[line][inc_col])
			{
				towers_seen++;
				last_nb = solution[line][inc_col];
			}
		}
	}
	else if (way == RTL)
	{
		clue = clues[right_cond_nb(line)];
		for (int inc_col = TAB_SIZE; solution[line][inc_col] != TAB_SIZE; inc_col--)
		{
			if (last_nb < solution[line][inc_col])
			{
				towers_seen++;
				last_nb = solution[line][inc_col];
			}
		}
	}
	else if (way == TTB)
	{
		clue = clues[col];
		for (int inc_line = 0; solution[inc_line][col] != TAB_SIZE; inc_line++)
		{
			if (last_nb < solution[inc_line][col])
			{
				towers_seen++;
				last_nb = solution[inc_line][col];
			}
		}
	}
	else
	{
		clue = clues[bottom_cond_nb(col)];
		for (int inc_line = TAB_SIZE - 1; solution[inc_line][col] != TAB_SIZE; inc_line--)
		{
			if (last_nb < solution[inc_line][col])
			{
				towers_seen++;
				last_nb = solution[inc_line][col];
			}
		}
	}
	return (towers_seen == clue - 1);
}

void	remv_six_or_put_fst_nb(reading_way way, int pos_7, int line, int col, int ***available_nbs, int **solution)
{
	if (way == LTR)
	{
		if (pos_7 > 1 && !solution[line][pos_7 - 1] && available_nbs[NB(TAB_SIZE - 1)][line][pos_7 - 1])
			available_nbs[NB(TAB_SIZE - 1)][line][pos_7 - 1] = 0;
		if (!solution[line][0])
		{
			if (last_boxs_are_filled(way, solution, line, col))
			{
				int nb = TAB_SIZE - 2;
				while (nb >= 0 && !available_nbs[nb][line][0])
					nb--;
				actualise_valid_pos(nb, line, 0, available_nbs, solution);
			}
			else if (last_boxs_arent_filled(way, solution, line, col))
			{
				int low_limit = -1;
				for (int inc_col = pos_7 - 1; inc_col >= 0; inc_col--)
					low_limit++;
				while (--low_limit >= 0)
					available_nbs[low_limit][0][col] = 0;
			}
		}
	}
	else if (way == RTL)
	{
		if (pos_7 < TAB_SIZE - 2 && !solution[line][pos_7 + 1] && available_nbs[NB(TAB_SIZE - 1)][line][pos_7 + 1])
			available_nbs[NB(TAB_SIZE - 1)][line][pos_7 + 1] = 0;
		if (!solution[line][TAB_SIZE - 1])
		{
			if (last_boxs_are_filled(way, solution, line, col))
			{
				int nb = TAB_SIZE - 2;
				while (nb >= 0 && !available_nbs[nb][line][TAB_SIZE - 1])
					nb--;
				actualise_valid_pos(nb, line, TAB_SIZE - 1, available_nbs, solution);
			}
			else if (last_boxs_arent_filled(way, solution, line, col))
			{
				int low_limit = -1;
				for (int inc_line = pos_7 + 1; inc_line <= TAB_SIZE - 1; inc_line++)
					low_limit++;
				while (--low_limit >= 0)
					available_nbs[low_limit][line][TAB_SIZE - 1] = 0;
			}
		}
	}
	else if (way == TTB)
	{
		if (pos_7 > 1 && !solution[pos_7 - 1][col] && available_nbs[NB(TAB_SIZE - 1)][pos_7 - 1][col])
			available_nbs[NB(TAB_SIZE - 1)][pos_7 - 1][col] = 0;
		if (!solution[0][col])
		{
			if (last_boxs_are_filled(way, solution, line, col))
			{
				int nb = TAB_SIZE - 2;
				while (nb >= 0 && !available_nbs[nb][0][col])
					nb--;
				actualise_valid_pos(nb, 0, col, available_nbs, solution);
			}
			else if (last_boxs_arent_filled(way, solution, line, col))
			{
				int low_limit = -1;
				for (int inc_line = pos_7 - 1; inc_line >= 0; inc_line--)
					low_limit++;
				while (--low_limit >= 0)
					available_nbs[low_limit][line][0] = 0;
			}
		}
	}
	else
	{
		if (pos_7 < TAB_SIZE - 2 && !solution[pos_7 + 1][col] && available_nbs[NB(TAB_SIZE - 1)][pos_7 + 1][col])
			available_nbs[NB(TAB_SIZE - 1)][pos_7 + 1][col] = 0;
		if (!solution[TAB_SIZE - 1][col])
		{
			if (last_boxs_are_filled(way, solution, line, col))
			{
				int nb = TAB_SIZE - 2;
				while (nb >= 0 && !available_nbs[nb][TAB_SIZE - 1][col])
					nb--;
				actualise_valid_pos(nb, TAB_SIZE - 1, col, available_nbs, solution);
			}
			else if (last_boxs_arent_filled(way, solution, line, col))
			{
				int low_limit = -1;
				for (int inc_line = pos_7 + 1; inc_line <= TAB_SIZE - 1; inc_line++)
					low_limit++;
				while (--low_limit >= 0)
					available_nbs[low_limit][TAB_SIZE - 1][col] = 0;
			}
		}
	}
}

void	reduce_possibilities(int ***available_nbs, int **solution, int *clues)
{
	int line, col, pos_line, pos_col;

	for (line = 0, col = 0; line < TAB_SIZE; line++, col++)
	{
		if (nbs_found[0][line] != TAB_SIZE && (pos_col = is_nb_on_line(TAB_SIZE, line, solution)))
		{
			if (!clues_fullfilled[left_cond_nb(line)] && one_nb_left_for_clue(LTR, line, col, clues, solution))
				remove_possibilities_onlfc(LTR, line, col, solution, available_nbs);
			if (!clues_fullfilled[right_cond_nb(line)] && one_nb_left_for_clue(RTL, line, col, clues, solution))
				remove_possibilities_onlfc(RTL, line, col, solution, available_nbs);
			if (clues[left_cond_nb(line)] == 2)
				remv_six_or_put_fst_nb(LTR, pos_col, line, col, available_nbs, solution);
			if (clues[right_cond_nb(line)] == 2)
				remv_six_or_put_fst_nb(RTL, pos_col, line, col, available_nbs, solution);
		}
		if (nbs_found[1][col] != TAB_SIZE && (pos_line = is_nb_on_col(TAB_SIZE, col, solution)))
		{
			if (!clues_fullfilled[col] && one_nb_left_for_clue(TTB, line, col, clues, solution))
				remove_possibilities_onlfc(TTB, line, col, solution, available_nbs);
			if (!clues_fullfilled[bottom_cond_nb(col)] && one_nb_left_for_clue(BTT, line, col, clues, solution))
				remove_possibilities_onlfc(BTT, line, col, solution, available_nbs);
			if (clues[col] == 2)
				remv_six_or_put_fst_nb(TTB, pos_line, line, col, available_nbs, solution);
			if (clues[bottom_cond_nb(col)] == 2)
				remv_six_or_put_fst_nb(BTT, pos_line, line, col, available_nbs, solution);
		}
	}
}
