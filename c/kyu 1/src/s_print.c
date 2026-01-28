#include "skyscraper.h"

/**
 * @brief
 * Print a 2D array representing a grid, including its surrounding clues.
 *
 * This function displays:
 * 
 * - the grid values
 * 
 * - the top, bottom, left and right clues
 * 
 * - handles NULL arrays safely
 *
 * @param array   The 2D array to print
 * @param nb      The index of the number array (used for labeling)
 * @param clues   The array of clues
 */
void	print_array(int **array, int nb, int clues[N * 4])
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
	for(int j = 0; j < N; j++)
	{
		if (clues[j])
			printf(" %d  ", clues[j]);
		else
			printf("    ");
		
	}
	printf("\n");
	printf("  ─────────────────────────────\n");
	for (int i = N - 1; i >= 0; i--)
	{
		if (clues[N * 3 + i])
			printf("%d ", clues[N * 3 + i]);
		else
			printf("  ");
		printf("|");
		for(int j = 0; j < N; j++)
		{
			if (array[(rev_nb(i))][j])
				printf(" %d |", array[(rev_nb(i))][j]);
			else
				printf("   |");
		}
		if (clues[N + (rev_nb(i))])
			printf(" %d", clues[N + (rev_nb(i))]);
		else
			printf("  ");
		printf("\n  ─────────────────────────────\n");
	}
	printf("   ");
	for(int j = N - 1; j >= 0; j--)
	{
		if (clues[N * 2 + j])
			printf(" %d  ", clues[N * 2 + j]);
		else
			printf("    ");
		
	}
	printf("\n");
}

/**
 * @brief
 * Print all available numbers for each box of the grid.
 *
 * Displays, for every cell:
 * 
 * - possible values if the cell is empty
 * 
 * - the fixed value if the solution already contains one
 * 
 * - surrounding clues for better visualization
 *
 * Useful for debugging the solving process.
 *
 * @param available_nbs   the array of possible numbers
 * @param clues           The array of clues
 * @param solution        The current solution grid
 */
void	print_all_available_each_box(int ***available_nbs, int clues[N * 4], int **solution)
{
	int i = 0, j = 0, k = -1, l_clue;
	if (!available_nbs || !available_nbs[0])
	{
		printf("(null)\n");
		return ;
	}
	printf("all nbs available :\n\n    ");
	while (i < N)
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
	for (i = 0; i < N; i++)
	{
		printf("  |");
		for (k = 0; k < N; k++)
		{
			for (j = 0; j < 3; j++)
			{
				if (!solution[i][k] && j < N && available_nbs[j][i][k])
					printf(" %d", available_nbs[j][i][k]);
				else
					printf("  ");
			}
			printf(" |");
		}
		printf("\n");
		if ((l_clue = clues[left_cond_nb(i)]))
			printf("%d |", l_clue);
		else
			printf("  |");
		for (k = 0; k < N; k++)
		{
			for (j = 3; j < 6; j++)
			{
				if (solution[i][k])
				{
					printf(GREEN"   %d  "RESET, solution[i][k]);
					break ;
				}	
				if (j < N && available_nbs[j][i][k])
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
		for (k = 0; k < N; k++)
		{
			for (j = 6; j < 9; j++)
			{
				if (!solution[i][k] && j < N && available_nbs[j][i][k])
					printf(" %d", available_nbs[j][i][k]);
				else
					printf("  ");
			}
			printf(" |");
		}
		printf("\n  ─────────────────────────────────────────────────────────\n");
	}
	printf("    ");
	for(j = 0; j < N; j++)
	{
		if (clues[bottom_cond_nb(j)])
			printf("  %d  ", clues[bottom_cond_nb(j)]);
		else
			printf("     ");
		printf("   ");
		
	}
	printf("\n");
}

/**
 * @brief
 * Print all available-number arrays.
 *
 * Iterates over each number possibility array and prints it
 * using print_array().
 *
 * This allows visualization of constraints per number.
 *
 * @param available_nbs   the array of possible numbers
 * @param clues           The array of clues
 */
void	print_all_nb_arrays(int ***available_nbs, int clues[N * 4])
{
	for (int nb = 0; nb < N; nb++)
		print_array(available_nbs[nb], nb, clues);
}

/**
 * @brief
 * Print a column
 * 
 * @param solution The answer sheet
 * @param col The column to print
 */
void print_col(int **solution, int col)
{
	printf("col %d:\n", col + 1);
	for (int line = 0; line < N; line++)
		printf("|%d|\n", solution[line][col]);
}

/**
 * @brief
 * Print a line
 * 
 * @param solution The answer sheet
 * @param line The line to print
 */
void print_line(int **solution, int line)
{
	printf("line %d:\n", line + 1);
	printf("--------------\n");
	for (int col = 0; col < N; col++)
		printf("%d \n", solution[line][col]);
	printf("--------------\n");
}
