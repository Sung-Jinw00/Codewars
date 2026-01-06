/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/04 00:34:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_answer(int **array, int **wrapper_array, int clues[TAB_SIZE * 4])
{
	if (!array || !array[0])
	{
		printf("(null)\n");
		return ;
	}
	//print wrapper_array
	/* printf(CYAN UNDERLINE"should be :\n"RESET);
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
			printf(" %d |", wrapper_array[rev_pos(i)][j]);
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
	printf("\n"); */
	//print array
	printf(CYAN UNDERLINE"\ngot :\n"RESET);
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
			if (array[rev_pos(i)][j] == wrapper_array[rev_pos(i)][j])
				printf(" "GREEN"%d"RESET" |", array[rev_pos(i)][j]);
			else
				printf(" "RED"%d"RESET" |", array[rev_pos(i)][j]);
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

//wrapper
int	**wrapped_array(int static_array[TAB_SIZE][TAB_SIZE])
{
	static int *rows[TAB_SIZE];
	for (int i = 0; i < TAB_SIZE; i++)
		rows[i] = static_array[i];
	return (rows);
}

void	print_indices(int clues[TAB_SIZE * 4])
{
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
			printf("   |");
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

void	free_array(int **result)
{
	for (int i = 0; i < TAB_SIZE; i++)
		free(result[i]);
	free(result);
}
