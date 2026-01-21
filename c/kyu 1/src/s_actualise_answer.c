/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_actualise_answer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2026/01/19 13:54:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

/**
 * @brief
 * Set the number to the current box and remove the number from possibilities in the corresponding columns and lines
 * 
 * @param nb			the number
 * @param line			the current line
 * @param col			the curent column
 * @param available_nbs	the array of possible numbers
 * @param solution		the solution board
 */
void	set_valid_pos(int nb, int line, int col, int ***available_nbs, int **solution)
{
	//put the number in the solution board
	solution[line][col] = nb + 1;
	//set every other box on the same column to zero
	for (int col_inc = 0; col_inc < N; col_inc++)
		if (col_inc != col)
			available_nbs[nb][line][col_inc] = 0;
	//set every other boxs on the same line to zero
	for (int line_inc = 0; line_inc < N; line_inc++)
		if (line_inc != line)
			available_nbs[nb][line_inc][col] = 0;
	//remove every other numbers in the possibilities at this position
	for (int nb_inc = 0; nb_inc < N; nb_inc++)
		if (nb_inc != nb)
			available_nbs[nb_inc][line][col] = 0;
	//add one to the found numbers in the current line and column
	nbs_found[0][line]++;
	nbs_found[1][col]++;
}

/**
 * @brief
 * Set the solution from up to bottom on the current column
 * 
 * @param nb			the starting number
 * @param cur_col		the column to modify
 * @param available_nbs	the array of possible numbers
 * @param solution		the solution board
 * */
void	actualise_all_column(int nb, int cur_col, int ***available_nbs, int **solution)
{
	//nb is increase if it starts from 0, else it's decreased
	const int i = (nb == 0) ? 1 : -1;
	for (int line = 0; line < N; line++)
	{
		set_valid_pos(nb, line, cur_col, available_nbs, solution);
		nb += i;
	}
}

/**
 * @brief
 * Set the solution from left to right on the current line
 * 
 * @param nb			the starting number
 * @param cur_line		the line to modify
 * @param available_nbs	the array of possible numbers
 * @param solution		the solution board
 * */
void	actualise_all_line(int nb, int cur_line, int ***available_nbs, int **solution)
{
	//nb is increase if it starts from 0, else it's decreased
	const int i = (nb == 0) ? 1 : -1;
	for (int col = 0; col < N; col++)
	{
		set_valid_pos(nb, cur_line, col, available_nbs, solution);
		nb += i;
	}
}
