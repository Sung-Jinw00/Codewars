#include "main.h"

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

//wrapper
int	**wrapped_array(int static_array[N][N])
{
	static int *rows[N];
	for (int i = 0; i < N; i++)
		rows[i] = static_array[i];
	return (rows);
}

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

void	free_array(int **result)
{
	for (int i = 0; i < N; i++)
		free(result[i]);
	free(result);
}
