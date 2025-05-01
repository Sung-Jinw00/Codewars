/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/01 19:05:55 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  TAB_SIZE  7

int one[TAB_SIZE][TAB_SIZE] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1}};

int answer[TAB_SIZE][TAB_SIZE] = {
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0}};

void	filter_available_nbs(int ***available_nbs, int *clues)
{
	for (int i = 0; i < TAB_SIZE * 4; i++)//while i didn't check all clues
	{
		if (clues[i] != 0)//if a clue is different than zero
		{
			if (clues[i] == TAB_SIZE)//if clue = max nb
			{
				if (i < TAB_SIZE)//if i'm in the first row of clues
				{
					for (int nb = 0; nb < TAB_SIZE; nb++)//while i didn't actualise all numbers
					{
						for (int line = 0; line < TAB_SIZE; line++)//while i didn't actualise because of each line
						{
							for (int column = 0; column < TAB_SIZE; column++)//while i didn't actualise every box of the line
							{
								if (column != i)//if the index is different than the box where i want to keep my number
									available_nbs[nb][line][column] = 0;//i set to zero
							}
						}
					}
				}
			}
		}
	}
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

int **SolvePuzzle(int *clues)
{
	if (!clues)
		return (NULL);
	int ***available_nbs = init_availability();

	filter_available_nbs(available_nbs, clues);
	return (NULL);
}

//─────────────────────────────
// Main Utils
//─────────────────────────────

#include <stdio.h>

# ifndef RESET
#  define RESET				"\033[0m"
# endif

/* Bold text */
# ifndef BOLD
#  define BOLD				"\033[1m"
# endif

/* Underlined text */
# ifndef UNDERLINE
#  define UNDERLINE			"\033[4m"
# endif

/* Red text */
# ifndef RED
#  define RED				"\033[31m"
# endif

/* Green text */
# ifndef GREEN
#  define GREEN				"\033[32m"
# endif

/* Cyan text */
# ifndef CYAN
#  define CYAN				"\033[36m"
# endif

void	print_array(int **array, int clues[TAB_SIZE * 4])
{
	if (!array || !array[0])
	{
		printf("(null)\n");
		return ;
	}
	printf("\n   ");
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
			printf(" %d |", array[TAB_SIZE - i - 1][j]);
		if (clues[TAB_SIZE + (TAB_SIZE - i - 1)])
		printf(" %d", clues[TAB_SIZE + (TAB_SIZE - i - 1)]);
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
void	print_static_array(int static_array[TAB_SIZE][TAB_SIZE], int clues[TAB_SIZE * 4])
{
	int *rows[TAB_SIZE];
	for (int i = 0; i < TAB_SIZE; i++)
		rows[i] = static_array[i];
	print_array(rows, clues);
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
		if (clues[TAB_SIZE + (TAB_SIZE - i - 1)])
		printf(" %d", clues[TAB_SIZE + (TAB_SIZE - i - 1)]);
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
//─────────────────────────────
// Main
//─────────────────────────────

int main(void)
{
	static int clues[][TAB_SIZE * 4] = {
	  { 7, 0, 0, 0, 2, 2, 3,
		0, 0, 3, 0, 0, 0, 0,
		3, 0, 3, 0, 0, 5, 0,
		0, 0, 0, 0, 5, 0, 4 },
	  { 0, 2, 3, 0, 2, 0, 0,
		5, 0, 4, 5, 0, 4, 0,
		0, 4, 2, 0, 0, 0, 6,
		5, 2, 2, 2, 2, 4, 1 }
	};
	
	static int expected[][TAB_SIZE][TAB_SIZE] = {
		{{ 1, 5, 6, 7, 4, 3, 2 },
		 { 2, 7, 4, 5, 3, 1, 6 },
		 { 3, 4, 5, 6, 7, 2, 1 },
		 { 4, 6, 3, 1, 2, 7, 5 },
		 { 5, 3, 1, 2, 6, 4, 7 },
		 { 6, 2, 7, 3, 1, 5, 4 },
		 { 7, 1, 2, 4, 5, 6, 3 }},
		{{ 7, 6, 2, 1, 5, 4, 3 },
		 { 1, 3, 5, 4, 2, 7, 6 },
		 { 6, 5, 4, 7, 3, 2, 1 },
		 { 5, 1, 7, 6, 4, 3, 2 },
		 { 4, 2, 1, 3, 7, 6, 5 },
		 { 3, 7, 6, 2, 1, 5, 4 },
		 { 2, 4, 3, 5, 6, 1, 7 }}
	};
	int diff = 0;

	for (int i = 0; i < 2; i++)
	{
		int **result = SolvePuzzle(clues[i]);
		printf(CYAN UNDERLINE BOLD"Test %d :\n"RESET, i);
		for (int j = 0; j < TAB_SIZE; j++)
		{
			if (!result || memcmp(result, expected[i], TAB_SIZE * sizeof(int)))
			{
				diff = 1;
				printf(RED "diff !\n"CYAN UNDERLINE"result of :"RESET);
				print_indices(clues[i]);
				printf(CYAN UNDERLINE"should be :\n"RESET);
				print_static_array(expected[i], clues[i]);
				printf(CYAN UNDERLINE"\ngot :\n"RESET);
				print_array(result, clues[i]);
				printf(RESET);
				break ;
			}
		}
		if (!diff)
			printf(GREEN"no diff !"CYAN" congrats !\n"RESET);
		printf("\n\n");
		diff = 0;
	}
	return (0);
}
