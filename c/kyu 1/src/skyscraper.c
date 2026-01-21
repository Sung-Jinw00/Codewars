/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2026/01/19 16:54:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

/* keep tracking the amount of clues fullfilled */
bool clues_fullfilled[N * 4] = {false};

/* keep tracking the amount of numbers found on lines and columns */
int nbs_found[2][7] = {
	{0, 0, 0, 0, 0, 0, 0},//lines
	{0, 0, 0, 0, 0, 0, 0}//cols
};

/**
 * @brief
 * Find the solutions that can be determined solely by the conditions and numbers already present in the grid.
 * 
 * @param available_nbs	the array of possible numbers
 * @param solution		the solution board
 * @param clues			the array of clues
 */
void	set_guessable_nbs(int ***available_nbs, int **solution, int *clues)
{
	for (int i = 0; i < N * 4; i++)//while i didn't checked all clues
	{
		if (clues[i] != 0)//if a clue is found
		{
			if (clues[i] == N)//if clue = max nb
				actualise_max_clue(i, available_nbs, solution, clues);//i fill the line or column
			else if (clues[i] == 1)//else if clue = 1
				actualise_max_nb(i, available_nbs, solution, clues);//i put max nb
			else if (clues[i] == 2)//else if clue = 2
				remv_before_max_nb(i, available_nbs);//i remove N - 1 at the second box away from the clue
			if (!clues_fullfilled[i])//if the clue is not fullfilled
				set_limit_nbs(clues[i], i, available_nbs);//i set limits of possible numbers based on the clue
		}
	}
	put_guessable_nbs(available_nbs, solution, clues);
}

/**
 * @brief
 * start of the solving program that will find the solution for a nxn skyscraper.
 * 
 * @return
 * A memory allocated array of arrays of int
 */
int **SolvePuzzle(int *clues)
{
	//return NULL if clues == NULL
	if (!clues)
		return (NULL);
	//set to 'true' empty clues
	for (int i = 0; i < N * 4; i++)
		if (!clues[i])
			clues_fullfilled[i] = true;
	//init the boards of available numbers
	int ***available_nbs = init_availability();
	//init the solution array of ints
	int **solution = calloc(sizeof(int *), N);
	for (int i = 0; i < N; i++)
		solution[i] = calloc(sizeof(int), N);
	//find guessable numbers before recursive search
	set_guessable_nbs(available_nbs, solution, clues);
	/* print_all_nb_arrays(available_nbs, clues);
	printf("\n\n"); */
	return solution;
	//recursive search
	solution = backtracking_solve(available_nbs, solution, clues);
	//print the solution found
	print_all_available_each_box(available_nbs, clues, solution);
	//return the solution
	return (solution);
}
