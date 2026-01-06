/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 01:10:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

void	print_array(int **array, int nb, int clues[TAB_SIZE * 4])
{
	if (!array || !array[0])
	{
		printf("array of %d's :\n", nb + 1);
		printf("(null)\n");
		return ;
	}
	//print wrapper_array
	printf("array of %d's :\n", nb + 1);
	printf("\n   ");
	for(int j = 0; j < TAB_SIZE; j++)
	{
		if (clues[j])
			printf(" %d  ", clues[j]);
		else
			printf("    ");
		
	}
	printf("\n");
	printf("  ─────────────────────────────\n");
	for (int i = TAB_SIZE - 1; i >= 0; i--)
	{
		if (clues[TAB_SIZE * 3 + i])
			printf("%d ", clues[TAB_SIZE * 3 + i]);
		else
			printf("  ");
		printf("|");
		for(int j = 0; j < TAB_SIZE; j++)
		{
			if (array[(rev_pos(i))][j])
				printf(" %d |", array[(rev_pos(i))][j]);
			else
				printf("   |");
		}
		if (clues[TAB_SIZE + (rev_pos(i))])
			printf(" %d", clues[TAB_SIZE + (rev_pos(i))]);
		else
			printf("  ");
		printf("\n  ─────────────────────────────\n");
	}
	printf("   ");
	for(int j = TAB_SIZE - 1; j >= 0; j--)
	{
		if (clues[TAB_SIZE * 2 + j])
			printf(" %d  ", clues[TAB_SIZE * 2 + j]);
		else
			printf("    ");
		
	}
	printf("\n");
}

void	print_all_available_each_box(int ***available_nbs, int clues[TAB_SIZE * 4], int **solution)
{
	int i = 0, j = 0, k = -1;
	if (!available_nbs || !available_nbs[0])
	{
		printf("(null)\n");
		return ;
	}
	printf("all nbs available :\n\n    ");
	while (i < TAB_SIZE)
	{
		if (clues[i])
			printf("  %d  ", clues[i]);
		else
			printf("     ");
		printf("   ");
		i++;
	}
	printf("\n");
	printf("  ─────────────────────────────────────────────────────────\n");
	for (i = 0; i < TAB_SIZE; i++)
	{
		printf("  |");
		for (k = 0; k < TAB_SIZE; k++)
		{
			for (j = 0; j < 3; j++)
			{
				if (!solution[i][k] && j < TAB_SIZE && available_nbs[j][i][k])
					printf(" %d", available_nbs[j][i][k]);
				else
					printf("  ");
			}
			printf(" |");
		}
		printf("\n");
		printf("%d |", clues[left_cond_nb(i)]);
		for (k = 0; k < TAB_SIZE; k++)
		{
			for (j = 3; j < 6; j++)
			{
				if (solution[i][k])
				{
					printf(GREEN"   %d  "RESET, solution[i][k]);
					break ;
				}	
				if (j < TAB_SIZE && available_nbs[j][i][k])
					printf(" %d", available_nbs[j][i][k]);
				else
					printf("  ");
			}
			printf(" |");
		}
		if (clues[right_cond_nb(i)])
			printf(" %d\n", clues[right_cond_nb(i)]);
		else
			printf("\n");
		printf("  |");
		for (k = 0; k < TAB_SIZE; k++)
		{
			for (j = 6; j < 9; j++)
			{
				if (!solution[i][k] && j < TAB_SIZE && available_nbs[j][i][k])
					printf(" %d", available_nbs[j][i][k]);
				else
					printf("  ");
			}
			printf(" |");
		}
		printf("\n  ─────────────────────────────────────────────────────────\n");
	}
	printf("    ");
	for(j = 0; j < TAB_SIZE; j++)
	{
		if (clues[bottom_cond_nb(j)])
			printf("  %d  ", clues[bottom_cond_nb(j)]);
		else
			printf("     ");
		printf("   ");
		
	}
	printf("\n");
}

void	print_all_nb_arrays(int ***available_nbs, int clues[TAB_SIZE * 4])
{
	for (int nb = 0; nb < TAB_SIZE; nb++)
		print_array(available_nbs[nb], nb, clues);
}
