/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 01:22:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

bool clues_fullfilled[TAB_SIZE * 4] = {false};

int nbs_found[2][7] = {
	{0, 0, 0, 0, 0, 0, 0},//lines
	{0, 0, 0, 0, 0, 0, 0}//cols
};

void	set_guessable_nbs(int ***available_nbs, int **solution, int *clues)
{
	for (int i = 0; i < TAB_SIZE * 4; i++)//while i didn't checked all clues
	{
		if (clues[i] != 0)//if a clue is different than zero
		{
			if (clues[i] == TAB_SIZE)//if clue = max nb
				actualise_max_clue(i, available_nbs, solution, clues);//i put the line
			else if (clues[i] == 1)//else if clue = 1
				actualise_max_nb(i, available_nbs, solution, clues);//i put max nb
			else if (clues[i] == 2)//else if clue = 2
				remv_before_max_nb(i, available_nbs);//i put max nb
			if (!clues_fullfilled[i])
				set_limit_nbs(clues[i], i, available_nbs);//i set limits for nbs
		}
	}
	put_guessable_nbs(available_nbs, solution, clues);
}

int **SolvePuzzle(int *clues)
{
	if (!clues)
		return (NULL);
	for (int i = 0; i < TAB_SIZE * 4; i++)
		if (!clues[i])
			clues_fullfilled[i] = true;
	int ***available_nbs = init_availability();
	int **solution = calloc(sizeof(int *), TAB_SIZE);
	for (int i = 0; i < TAB_SIZE; i++)
		solution[i] = calloc(sizeof(int), TAB_SIZE);
	set_guessable_nbs(available_nbs, solution, clues);
	/* print_all_nb_arrays(available_nbs, clues);
	printf("\n\n"); */
	print_all_available_each_box(available_nbs, clues, solution);
	return (solution);
}
