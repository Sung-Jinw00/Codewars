/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_rules_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/03 21:35:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

//─────────────────────────────
// Find with rules
//─────────────────────────────

void	all_boxs_empty_ltr(int clue, int line, int **solution, int ***available_nbs, bool lbaf)
{
	int	remaining_nb[TAB_SIZE] = {0};
	int remaining_nbs = TAB_SIZE;

	for (int i = 0; i < TAB_SIZE; i++)
		remaining_nb[i] = i + 1;
	for (int col = 0; col < TAB_SIZE; col++)
	{
		if (solution[line][col])
		{
			remaining_nb[NB(solution[line][col])] = 0;
			remaining_nbs--;
		}
	}
	if (remaining_nbs == clue - 1 || lbaf)
	{
		int i = 0;
		for (int col = 0; !solution[line][col]; col++)
		{
			while (i < TAB_SIZE && !remaining_nb[i])
				i++;
			actualise_valid_pos(NB(remaining_nb[i]), line, col, available_nbs, solution);
			i++;
		}
		clues_fullfilled[line] = true;
	}
}

bool	ascending_rule_works_ltr(int *clues, int line, int **solution, int ***available_nbs)
{
	int	clue = clues[left_cond_nb(line)], prev_nb, col = 0, next_nb, empty_boxs;
	bool lbaf = false;

	if (!clue || is_nb_on_line(TAB_SIZE, line, solution) + 1 < clue)
		return (false);
	while (!solution[line][col])
		col++;
	if (solution[line][col] == TAB_SIZE || (lbaf = last_boxs_are_filled(LTR, solution, line, col)))
		return (all_boxs_empty_ltr(clue, line, solution, available_nbs, lbaf), false);
	prev_nb = solution[line][col];
	while (solution[line][col] != TAB_SIZE)
	{
		if (!solution[line][col])
		{
			empty_boxs = 1;
			while (!solution[line][col + empty_boxs])
				empty_boxs++;
			next_nb = solution[line][col + empty_boxs];
			if (empty_boxs != (next_nb - prev_nb - 1))
				return (false);
			col += empty_boxs;
		}
		prev_nb = solution[line][col];
		if (solution[line][col] != TAB_SIZE)
			col++;
	}
	clues_fullfilled[line] = true;
	return (true);
}

void	all_boxs_empty_ttb(int clue, int col, int **solution, int ***available_nbs, bool lbaf)
{
	int	remaining_nb[TAB_SIZE] = {0};
	int remaining_nbs = TAB_SIZE;

	for (int i = 0; i < TAB_SIZE; i++)
		remaining_nb[i] = i + 1;
	for (int line = 0; line < TAB_SIZE; line++)
	{
		if (solution[line][col])
		{
			remaining_nb[NB(solution[line][col])] = 0;
			remaining_nbs--;
		}
	}
	if (remaining_nbs == clue - 1 || lbaf)
	{
		int i = 0;
		for (int line = 0; !solution[line][col]; line++)
		{
			while (i < TAB_SIZE && !remaining_nb[i])
				i++;
			actualise_valid_pos(NB(remaining_nb[i]), line, col, available_nbs, solution);
			i++;
		}
		clues_fullfilled[col] = true;
	}
}

bool	ascending_rule_works_ttb(int *clues, int col, int **solution, int ***available_nbs)
{
	int	clue = clues[col], prev_nb, line = 0, next_nb, empty_boxs;
	bool lbaf = false;

	if (!clue || is_nb_on_col(TAB_SIZE, col, solution) + 1 < clue)
		return (false);
	while (!solution[line][col])
		line++;
	if (solution[line][col] == TAB_SIZE || (lbaf = last_boxs_are_filled(TTB, solution, line, col)))
		return (all_boxs_empty_ttb(clue, col, solution, available_nbs, lbaf), false);
	prev_nb = solution[line][col];
	while (solution[line][col] != TAB_SIZE)
	{
		if (!solution[line][col])
		{
			empty_boxs = 1;
			while (!solution[line + empty_boxs][col])
				empty_boxs++;
			next_nb = solution[line + empty_boxs][col];
			if (empty_boxs != (next_nb - prev_nb - 1))
				return (false);
			line += empty_boxs;
		}
		prev_nb = solution[line][col];
		if (solution[line][col] != TAB_SIZE)
			line++;
	}
	clues_fullfilled[col] = true;
	return (true);
}

void	all_boxs_empty_btt(int clue, int col, int **solution, int ***available_nbs, bool lbaf)
{
	int	remaining_nb[TAB_SIZE] = {0};
	int remaining_nbs = TAB_SIZE;

	for (int i = 0; i < TAB_SIZE; i++)
		remaining_nb[i] = i + 1;
	for (int line = TAB_SIZE - 1; line >= 0; line--)
	{
		if (solution[line][col])
		{
			remaining_nb[NB(solution[line][col])] = 0;
			remaining_nbs--;
		}
	}
	if (remaining_nbs == clue - 1 || lbaf)
	{
		int i = 0;
		for (int line = TAB_SIZE - 1; !solution[line][col]; line--)
		{
			while (i < TAB_SIZE && !remaining_nb[i])
				i++;
			actualise_valid_pos(NB(remaining_nb[i]), line, col, available_nbs, solution);
			i++;
		}
		clues_fullfilled[col] = true;
	}
}

bool	ascending_rule_works_btt(int *clues, int col, int **solution, int ***available_nbs)
{
	int	clue = clues[bottom_cond_nb(col)], prev_nb, line = TAB_SIZE - 1, next_nb, empty_boxs;
	bool lbaf = false;
	
	if (!clue || rev_pos(is_nb_on_col(TAB_SIZE, col, solution)) + 1 < clue)
		return (false);
	while (!solution[line][col])
		line--;
	if (solution[line][col] == TAB_SIZE || (lbaf = last_boxs_are_filled(BTT, solution, line, col)))
		return (all_boxs_empty_btt(clue, col, solution, available_nbs, lbaf), false);
	prev_nb = solution[line][col];
	while (solution[line][col] != TAB_SIZE)
	{
		if (!solution[line][col])
		{
			empty_boxs = 1;
			while (!solution[line - empty_boxs][col])
				empty_boxs++;
			next_nb = solution[line - empty_boxs][col];
			if (empty_boxs != (next_nb - prev_nb - 1))
				return (false);
			line -= empty_boxs;
		}
		prev_nb = solution[line][col];
		if (solution[line][col] != TAB_SIZE)
			line--;
	}
	clues_fullfilled[col] = true;
	return (true);
}

void	all_boxs_empty_rtl(int clue, int line, int **solution, int ***available_nbs, bool lbaf)
{
	int	remaining_nb[TAB_SIZE] = {0};
	int remaining_nbs = TAB_SIZE;

	for (int i = 0; i < TAB_SIZE; i++)
		remaining_nb[i] = i + 1;
	for (int col = TAB_SIZE - 1; col >= 0; col--)
	{
		if (solution[line][col])
		{
			remaining_nb[NB(solution[line][col])] = 0;
			remaining_nbs--;
		}
	}
	if (remaining_nbs == clue - 1 || lbaf)
	{
		int i = 0;
		for (int col = TAB_SIZE - 1; !solution[line][col]; col--)
		{
			while (i < TAB_SIZE && !remaining_nb[i])
				i++;
			actualise_valid_pos(NB(remaining_nb[i]), line, col, available_nbs, solution);
			i++;
		}
		clues_fullfilled[line] = true;
	}
}

bool	ascending_rule_works_rtl(int *clues, int line, int **solution, int ***available_nbs)
{
	int clue = clues[right_cond_nb(line)], prev_nb, col = TAB_SIZE - 1, next_nb, empty_boxs;
	bool lbaf = false;

	if (!clue || rev_pos(is_nb_on_line(TAB_SIZE, line, solution)) + 1 < clue)
		return (false);
	while (!solution[line][col])
		col--;
	if (solution[line][col] == TAB_SIZE || (lbaf = last_boxs_are_filled(RTL, solution, line, col)))
		return (all_boxs_empty_rtl(clue, line, solution, available_nbs, lbaf), false);
	prev_nb = solution[line][col];
	while (solution[line][col] != TAB_SIZE)
	{
		if (!solution[line][col])
		{
			empty_boxs = 1;
			while (!solution[line][col - empty_boxs])
				empty_boxs++;
			next_nb = solution[line][col - empty_boxs];
			if (empty_boxs != (next_nb - prev_nb - 1))
				return (false);
			col -= empty_boxs;
		}
		prev_nb = solution[line][col];
		if (solution[line][col] != TAB_SIZE)
			col--;
	}
	clues_fullfilled[line] = true;
	return (true);
}

void	put_ascending_nbs(reading_way way, int line, int col, int **solution, int ***available_nbs)
{
	int inc_col, inc_line = 0;

	if (way == LTR)
	{
		inc_col = 0;
		while (!solution[line][inc_col])
			inc_col++;
		while (solution[line][inc_col] != TAB_SIZE)
		{
			while (solution[line][inc_col] && solution[line][inc_col] != TAB_SIZE)
				inc_col++;
			while (!solution[line][inc_col])
			{
				actualise_valid_pos(NB(solution[line][inc_col - 1] + 1), line, inc_col, available_nbs, solution);
				inc_col++;
			}
		}
		clues_fullfilled[left_cond_nb(line)] = true;
	}
	else if (way == RTL)
	{
		inc_col = TAB_SIZE - 1;
		while (!solution[line][inc_col])
			inc_col--;
		while (solution[line][inc_col] != TAB_SIZE)
		{
			while (solution[line][inc_col] && solution[line][inc_col] != TAB_SIZE)
				inc_col--;
			while (!solution[line][inc_col])
			{
				actualise_valid_pos(NB(solution[line][inc_col + 1] + 1), line, inc_col, available_nbs, solution);
				inc_col--;
			}
		}
		clues_fullfilled[right_cond_nb(line)] = true;
	}
	else if (way == BTT)
	{
		inc_line = 0;
		while (!solution[inc_line][col])
			inc_line++;
		while (solution[inc_line][col] != TAB_SIZE)
		{
			while (solution[inc_line][col] && solution[inc_line][col] != TAB_SIZE)
				inc_line++;
			while (!solution[inc_line][col])
			{
				actualise_valid_pos(NB(solution[inc_line - 1][col] + 1), inc_line, col, available_nbs, solution);
				inc_line++;
			}
		}
		clues_fullfilled[bottom_cond_nb(col)] = true;
	}
	else
	{
		inc_line = TAB_SIZE - 1;
		while (!solution[inc_line][col])
			inc_line--;
		while (solution[inc_line][col] != TAB_SIZE)
		{
			while (solution[inc_line][col] && solution[inc_line][col] != TAB_SIZE)
				inc_line--;
			while (!solution[inc_line][col])
			{
				actualise_valid_pos(NB(solution[inc_line + 1][col] + 1), inc_line, col, available_nbs, solution);
				inc_line--;
			}
		}
		clues_fullfilled[col] = true;
	}
}

/* look in diagonal if one line or column has only one possility for a number and set it in answer tab */
bool	set_one_possibility_rules(int ***available_nbs, int **solution, int *clues)
{
	bool changes = false;
	int line, col;

	for (line = 0, col = 0; line < TAB_SIZE; line++, col++)
	{
		if (nbs_found[0][line] != TAB_SIZE && is_nb_on_line(TAB_SIZE, line, solution))
		{
			if (!clues_fullfilled[left_cond_nb(line)]
				&& lacking_towers(LTR, line, col, solution) && ascending_rule_works_ltr(clues, line, solution, available_nbs))
				put_ascending_nbs(LTR, line, col, solution, available_nbs), changes = true;
			if (!clues_fullfilled[right_cond_nb(line)]
				&& lacking_towers(RTL, line, col, solution) && ascending_rule_works_rtl(clues, line, solution, available_nbs))
				put_ascending_nbs(RTL, line, col, solution, available_nbs), changes = true;
		}
		if (nbs_found[1][col] != TAB_SIZE && is_nb_on_col(TAB_SIZE, col, solution))
		{
			if (!clues_fullfilled[bottom_cond_nb(col)]
				&& lacking_towers(BTT, line, col, solution) && ascending_rule_works_btt(clues, col, solution, available_nbs))
				put_ascending_nbs(BTT, line, col, solution, available_nbs), changes = true;
			if (!clues_fullfilled[col]
				&& lacking_towers(TTB, line, col, solution) && ascending_rule_works_ttb(clues, col, solution, available_nbs))
				put_ascending_nbs(TTB, line, col, solution, available_nbs), changes = true;
		}
	}
	return (changes);
}
