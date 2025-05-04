/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_clues_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 01:47:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

void	clue_2_and_max_nb(int **solution, int ***available_nbs, int clues[TAB_SIZE * 4], int pos[2])
{
	if (!((pos[0] == 0 || pos[0] == TAB_SIZE - 1) && (pos[1] == 0 || pos[1] == TAB_SIZE - 1)
		&& solution[pos[0]][pos[1]] == TAB_SIZE))
		return ;
	if (pos[0] == 0 && clues[bottom_cond_nb(pos[1])] == 2)
		actualise_valid_pos(NB(TAB_SIZE - 1), TAB_SIZE - 1, pos[1], available_nbs, solution);
	else if (pos[0] == TAB_SIZE - 1 && clues[rev_pos(pos[1])] == 2)
		actualise_valid_pos(NB(TAB_SIZE - 1),  0, pos[1],available_nbs, solution);
	else if (pos[1] == 0 && clues[right_cond_nb(pos[0])] == 2)
		actualise_valid_pos(NB(TAB_SIZE - 1), pos[0], TAB_SIZE - 1, available_nbs, solution);
	else if (pos[1] == TAB_SIZE - 1 && clues[left_cond_nb(pos[0])] == 2)
		actualise_valid_pos(NB(TAB_SIZE - 1), pos[0], 0, available_nbs, solution);
}

void	remv_before_max_nb(int cur_col_or_line, int ***available_nbs)
{
	if (cur_col_or_line < TAB_SIZE)//if it's from the upper clues
		available_nbs[NB(TAB_SIZE - 1)][1][cur_col_or_line] = 0;
	else if (cur_col_or_line < TAB_SIZE * 2)//if it's from the right clues
	{
		cur_col_or_line -= TAB_SIZE - 1;
		available_nbs[NB(TAB_SIZE - 1)][cur_col_or_line][1] = 0;
	}
	else if (cur_col_or_line < TAB_SIZE * 3)//if it's from the lower clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 2)) - 1;
		available_nbs[NB(TAB_SIZE - 1)][1][cur_col_or_line] = 0;
	}
	else//if it's from the left clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 3)) - 1;
		available_nbs[NB(TAB_SIZE - 1)][cur_col_or_line][1] = 0;
	}
}

void	actualise_max_clue(int cur_col_or_line, int ***available_nbs, int **solution, int *clues)
{
	clues_fullfilled[cur_col_or_line] = true;
	if (cur_col_or_line < TAB_SIZE)//if it's from the upper clues
	{
		actualise_all_lines(NB(1), cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){0, cur_col_or_line});
	}
	else if (cur_col_or_line < TAB_SIZE * 2)//if it's from the right clues
	{
		cur_col_or_line -= TAB_SIZE;
		actualise_all_cols(NB(7), cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){cur_col_or_line, 0});
	}
	else if (cur_col_or_line < TAB_SIZE * 3)//if it's from the lower clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 2));
		actualise_all_lines(NB(7), cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){0, cur_col_or_line});
	}
	else//if it's from the left clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 3));
		actualise_all_cols(NB(1), cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){cur_col_or_line, 0});
	}
}

void	actualise_max_nb(int cur_col_or_line, int ***available_nbs, int **solution, int *clues)
{
	if (cur_col_or_line < TAB_SIZE)//if it's from the upper clues
	{
		actualise_valid_pos(NB(TAB_SIZE), 0, cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){0, cur_col_or_line});
	}
	else if (cur_col_or_line < TAB_SIZE * 2)//if it's from the right clues
	{
		cur_col_or_line -= TAB_SIZE - 1;
		actualise_valid_pos(NB(TAB_SIZE), cur_col_or_line, 0, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){cur_col_or_line, 0});
	}
	else if (cur_col_or_line < TAB_SIZE * 3)//if it's from the lower clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 2)) - 1;
		actualise_valid_pos(NB(TAB_SIZE), 0, cur_col_or_line, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){0, cur_col_or_line});
	}
	else//if it's from the left clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 3)) - 1;
		actualise_valid_pos(NB(TAB_SIZE), cur_col_or_line, 0, available_nbs, solution);
		clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){cur_col_or_line, 0});
	}
}
/* set the limit on all numbers depending on their distance with the clue border */
void	set_limit_nbs(int nb_clue, int cur_col_or_line, int ***available_nbs)
{
	int	max_limit = (TAB_SIZE - nb_clue) + 1;// no tower can be above this limit or it will 100% hide more towers than wanted

	if (cur_col_or_line < TAB_SIZE)//if it's from the upper clues
	{
		for (int i = 0; i < nb_clue; i++)//we put the limit until nb_clue boxes, then you can have whatever value you want, it can work
		{
			for (int nb = max_limit; nb < TAB_SIZE; nb++)
				available_nbs[nb][i][cur_col_or_line] = 0;
			max_limit++;//the more we step away from the border, the higher the limit is, in the ascending logic
		}
	}
	else if (cur_col_or_line < TAB_SIZE * 2)//if it's from the right clues
	{
		cur_col_or_line -= TAB_SIZE;
		for (int i = TAB_SIZE - 1; i > rev_pos(nb_clue); i--)
		{
			for (int nb = max_limit; nb < TAB_SIZE; nb++)
				available_nbs[nb][cur_col_or_line][i] = 0;
			max_limit++;//the more we step away from the border, the higher the limit is, in the ascending logic
		}
	}
	else if (cur_col_or_line < TAB_SIZE * 3)//if it's from the lower clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 2)) - 1;
		for (int i = TAB_SIZE - 1; i > rev_pos(nb_clue); i--)
		{
			for (int nb = max_limit; nb < TAB_SIZE; nb++)
				available_nbs[nb][i][cur_col_or_line] = 0;
			max_limit++;//the more we step away from the border, the higher the limit is, in the ascending logic
		}
	}
	else//if it's from the left clues
	{
		cur_col_or_line = TAB_SIZE - (cur_col_or_line - (TAB_SIZE * 3)) - 1;
		for (int i = 0; i < nb_clue; i++)
		{
			for (int nb = max_limit; nb < TAB_SIZE; nb++)
				available_nbs[nb][cur_col_or_line][i] = 0;
			max_limit++;//the more we step away from the border, the higher the limit is, in the ascending logic
		}
	}
}

bool	only_one_possibility_clue(int **solution, int ***available_nbs, int nb, int *ptr_line, int *ptr_col)
{
	int	count = 0;
	int	dup_line = *ptr_line, dup_col = *ptr_col;

	if (nbs_found[0][dup_line] != TAB_SIZE)
	{
		for (int col = 0; col < TAB_SIZE; col++)
		{
			if (available_nbs[nb][dup_line][col] != 0 && !solution[dup_line][col])
			{
				*ptr_col = col;
				count++;
			}
		}
		if (count == 1)
			return (true);
		*ptr_col = dup_col;
		count = 0;
	}
	if (nbs_found[1][dup_col] != TAB_SIZE)
	{
		for (int line = 0; line < TAB_SIZE; line++)
		{
			if (available_nbs[nb][line][dup_col] != 0 && !solution[line][dup_col])
			{
				*ptr_line = line;
				count++;
			}
		}
		if (count == 1)
			return (true);
		*ptr_line = dup_line;
	}
	return (false);
}

/* look in diagonal if one line or column has only one possility for a number and set it in answer tab */
bool	set_one_possibility_clue(int ***available_nbs, int **solution, int *clues)
{
	bool changes = false;
	int line, col, actual_check;

	for (line = 0, col = 0; line < TAB_SIZE; line++, col++)
	{
		actual_check = line;
		for (int nb = 0; nb < TAB_SIZE; nb++)
		{
			if (only_one_possibility_clue(solution, available_nbs, nb, &line, &col))
			{
				actualise_valid_pos(nb, line, col, available_nbs, solution);
				clue_2_and_max_nb(solution, available_nbs, clues, (int[2]){line, col});
				changes = true;
				break;
			}
		}
		col = line = actual_check;
	}
	return (changes);
}
