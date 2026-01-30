#include "main.h"

/**
 * @brief
 * Display the expected solution and the computed solution side by side.
 *
 * This function prints two boards:
 * 
 * - the expected solution (`wrapper_array`)
 * 
 * - the solver result (`array`)
 *
 * Each cell is colorized:
 * 
 * - green if the value matches the expected one
 * 
 * - red if the value differs
 *
 * The board is displayed with the surrounding `clues` to ease debugging.
 *
 * @param array           the solution returned by the solver
 * @param wrapper_array   a wrapped 2D array containing the expected solution
 * @param clues           the array of clues surrounding the board
 */
void	print_answer(int **array, int **wrapper_array, int clues[N * 4])
{
	if (!array || !array[0])
	{
		printf("(null)\n");
		return ;
	}
	//print wrapper_array
	printf(CYAN UNDERLINE"should be :\n"RESET);
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
			printf(" %d |", wrapper_array[rev_nb(i)][j]);
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
	//print array
	printf(CYAN UNDERLINE"\ngot :\n"RESET);
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
			if (array[rev_nb(i)][j] == wrapper_array[rev_nb(i)][j])
				printf(" "GREEN"%d"RESET" |", array[rev_nb(i)][j]);
			else
				printf(" "RED"%d"RESET" |", array[rev_nb(i)][j]);
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
 * Wrap a static 2D array into a double pointer.
 *
 * This function converts a static array `int[N][N]` into an `int **`
 * by creating an array of row pointers.
 *
 * The returned pointer must NOT be freed.
 *
 * @param static_array    the static 2D array to wrap
 *
 * @return a pointer-to-pointer view of `static_array`
 */
int	**wrapped_array(int static_array[N][N])
{
	static int *rows[N];
	for (int i = 0; i < N; i++)
		rows[i] = static_array[i];
	return (rows);
}

/**
 * @brief
 * Print an empty board showing only the clue indices.
 *
 * This function displays the board layout with all `clues`
 * but without any numbers inside the grid.
 *
 * It is useful to visualize clue placement independently
 * from the solution.
 *
 * @param clues   the array of clues
 */
void	print_indices(int clues[N * 4])
{
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
			printf("   |");
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
 * Free a dynamically allocated 2D array.
 *
 * @param arr2  the 2D array to free
 */
void	free_array2(int **arr2)
{
	for (int i = 0; i < N; i++)
		free(arr2[i]);
	free(arr2);
}

/**
 * @brief
 * Free a dynamically allocated 3D array.
 *
 * @param arr2  the 3D array to free
 */
void free_array3(int ***arr3)
{
	for (int nb = NB(1); nb < N; nb++)
		free_array2(arr3[nb]);
	free(arr3);
}
