/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:22:47 by marvin            #+#    #+#             */
/*   Updated: 2025/05/01 15:29:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

#define  SIZE  7

int answer[SIZE][SIZE] = {
	{ 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0}};

int **SolvePuzzle(int *clues)
{
	(void)clues;
	return (NULL);
}

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

void	print_array(int **array, int clues[SIZE * 4])
{
	if (!array || !array[0])
	{
		printf("(null)\n");
		return ;
	}
	printf("\n   ");
	printf("\n   ");
	for(int j = 0; j < SIZE; j++)
	{
		if (clues[j])
			printf(" %d  ", clues[j]);
		else
			printf("    ");
		
	}
	printf("\n");
	printf("  ─────────────────────────────\n");
	for (int i = SIZE - 1; i >= 0; i--)
	{
		if (clues[SIZE * 3 + i])
			printf("%d ", clues[SIZE * 3 + i]);
		else
			printf("  ");
		printf("|");
		for(int j = 0; j < SIZE; j++)
			printf(" %d |", array[SIZE - i - 1][j]);
		if (clues[SIZE + (SIZE - i - 1)])
		printf(" %d", clues[SIZE + (SIZE - i - 1)]);
		else
			printf("  ");
		printf("\n  ─────────────────────────────\n");
	}
	printf("   ");
	for(int j = SIZE - 1; j >= 0; j--)
	{
		if (clues[SIZE * 2 + j])
			printf(" %d  ", clues[SIZE * 2 + j]);
		else
			printf("    ");
		
	}
	printf("\n");
}

//wrapper
void	print_static_array(int static_array[SIZE][SIZE], int clues[SIZE * 4])
{
	int *rows[SIZE];
	for (int i = 0; i < SIZE; i++)
		rows[i] = static_array[i];
	print_array(rows, clues);
}

void	print_indices(int clues[SIZE * 4])
{
	printf("\n   ");
	for(int j = 0; j < SIZE; j++)
	{
		if (clues[j])
			printf(" %d  ", clues[j]);
		else
			printf("    ");
		
	}
	printf("\n");
	printf("  ─────────────────────────────\n");
	for (int i = SIZE - 1; i >= 0; i--)
	{
		if (clues[SIZE * 3 + i])
			printf("%d ", clues[SIZE * 3 + i]);
		else
			printf("  ");
		printf("|");
		for(int j = 0; j < SIZE; j++)
			printf("   |");
		if (clues[SIZE + (SIZE - i - 1)])
		printf(" %d", clues[SIZE + (SIZE - i - 1)]);
		else
			printf("  ");
		printf("\n  ─────────────────────────────\n");
	}
	printf("   ");
	for(int j = SIZE - 1; j >= 0; j--)
	{
		if (clues[SIZE * 2 + j])
			printf(" %d  ", clues[SIZE * 2 + j]);
		else
			printf("    ");
		
	}
	printf("\n");
}

/* 

correct shittu :
static int clues[][SIZE * 4] = {
	  { 7, 0, 0, 0, 2, 2, 3,
		0, 0, 2, 0, 0, 0, 0,
		4, 0, 5, 0, 0, 2, 0,
		0, 0, 0, 0, 1, 0, 3 },
	  { 0, 2, 3, 0, 2, 0, 0,
		6, 0, 3, 3, 0, 4, 0,
		0, 4, 2, 0, 0, 0, 5,
		5, 2, 4, 5, 3, 4, 1 }
	};

*/

int main(void)
{
	static int clues[][SIZE * 4] = {
	  { 7, 0, 0, 0, 2, 2, 3,
		0, 0, 3, 0, 0, 0, 0,
		3, 0, 3, 0, 0, 5, 0,
		0, 0, 0, 0, 5, 0, 4 },
	  { 0, 2, 3, 0, 2, 0, 0,
		5, 0, 4, 5, 0, 4, 0,
		0, 4, 2, 0, 0, 0, 6,
		5, 2, 2, 2, 2, 4, 1 }
	};
	
	static int expected[][SIZE][SIZE] = {
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
		for (int j = 0; j < SIZE; j++)
		{
			if (!result || memcmp(result, expected[i], SIZE * sizeof(int)))
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
