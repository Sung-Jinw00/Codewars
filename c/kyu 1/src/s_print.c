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
		fprintf(stderr, "array of %d's :\n", nb + 1);
		fprintf(stderr, "(null)\n");
		return ;
	}
	//print wrapper_array
	fprintf(stderr, "array of %d's :\n", nb + 1);
	fprintf(stderr, "\n   ");
	for(int j = 0; j < N; j++)
	{
		if (clues[j])
			fprintf(stderr, " %d  ", clues[j]);
		else
			fprintf(stderr, "    ");
		
	}
	fprintf(stderr, "\n");
	fprintf(stderr, "  ─────────────────────────────\n");
	for (int i = N - 1; i >= 0; i--)
	{
		if (clues[N * 3 + i])
			fprintf(stderr, "%d ", clues[N * 3 + i]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "|");
		for(int j = 0; j < N; j++)
		{
			if (array[(rev_nb(i))][j])
				fprintf(stderr, " %d |", array[(rev_nb(i))][j]);
			else
				fprintf(stderr, "   |");
		}
		if (clues[N + (rev_nb(i))])
			fprintf(stderr, " %d", clues[N + (rev_nb(i))]);
		else
			fprintf(stderr, "  ");
		fprintf(stderr, "\n  ─────────────────────────────\n");
	}
	fprintf(stderr, "   ");
	for(int j = N - 1; j >= 0; j--)
	{
		if (clues[N * 2 + j])
			fprintf(stderr, " %d  ", clues[N * 2 + j]);
		else
			fprintf(stderr, "    ");
		
	}
	fprintf(stderr, "\n");
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
	if (!solution)
		return ;
	int i = 0, j = 0, k = -1, l_clue;
	if (!available_nbs || !available_nbs[0])
	{
		fprintf(stderr, "(null)\n");
		return ;
	}
	fprintf(stderr, "all nbs available :\n\n    ");
	while (i < N)
	{
		if (clues[i])
			fprintf(stderr, "  %d  ", clues[i]);
		else
			fprintf(stderr, "     ");
		fprintf(stderr, "   ");
		i++;
	}
	fprintf(stderr, "\n");
	fprintf(stderr, "  ─────────────────────────────────────────────────────────\n");
	for (i = 0; i < N; i++)
	{
		fprintf(stderr, "  |");
		for (k = 0; k < N; k++)
		{
			for (j = 0; j < 3; j++)
			{
				if (!solution[i][k] && j < N && available_nbs[j][i][k])
					fprintf(stderr, " %d", available_nbs[j][i][k]);
				else
					fprintf(stderr, "  ");
			}
			fprintf(stderr, " |");
		}
		fprintf(stderr, "\n");
		if ((l_clue = clues[left_cond_nb(i)]))
			fprintf(stderr, "%d |", l_clue);
		else
			fprintf(stderr, "  |");
		for (k = 0; k < N; k++)
		{
			for (j = 3; j < 6; j++)
			{
				if (solution[i][k])
				{
					fprintf(stderr, GREEN"   %d  "RESET, solution[i][k]);
					break ;
				}	
				if (j < N && available_nbs[j][i][k])
					fprintf(stderr, " %d", available_nbs[j][i][k]);
				else
					fprintf(stderr, "  ");
			}
			fprintf(stderr, " |");
		}
		if (clues[right_cond_nb(i)])
			fprintf(stderr, " %d\n", clues[right_cond_nb(i)]);
		else
			fprintf(stderr, "\n");
		fprintf(stderr, "  |");
		for (k = 0; k < N; k++)
		{
			for (j = 6; j < 9; j++)
			{
				if (!solution[i][k] && j < N && available_nbs[j][i][k])
					fprintf(stderr, " %d", available_nbs[j][i][k]);
				else
					fprintf(stderr, "  ");
			}
			fprintf(stderr, " |");
		}
		fprintf(stderr, "\n  ─────────────────────────────────────────────────────────\n");
	}
	fprintf(stderr, "    ");
	for(j = 0; j < N; j++)
	{
		if (clues[bottom_cond_nb(j)])
			fprintf(stderr, "  %d  ", clues[bottom_cond_nb(j)]);
		else
			fprintf(stderr, "     ");
		fprintf(stderr, "   ");
		
	}
	fprintf(stderr, "\n");
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
	fprintf(stderr, "col %d:\n", col + 1);
	for (int line = 0; line < N; line++)
		fprintf(stderr, "|%d|\n", solution[line][col]);
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
	fprintf(stderr, "line %d:\n", line + 1);
	fprintf(stderr, "--------------\n");
	for (int col = 0; col < N; col++)
		fprintf(stderr, "%d \n", solution[line][col]);
	fprintf(stderr, "--------------\n");
}
