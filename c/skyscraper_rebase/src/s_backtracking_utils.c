#include "skyscraper.h"

void	empty_box_coords(int **solution, int *line, int *col)
{
	for (*line = 0; *line < N; (*line)++)
	{
		for (*col = 0; *col < N; (*col)++)
			if (!solution[*line][*col])
				return ;
	}
	*col = *line = -1;
}

int lowest_available(int available_nbs[N][N][N], int line, int col)
{
	for (int nb = N; nb > 0; nb--)
		if (available_nbs[N - 1][line][col])
			return available_nbs[N - 1][line][col];
	return 0;
}

void sol_dup(int **solution_dup, int **solution)
{
	for (int line = 0; line < N; line++)
		for (int col = 0; col < N; col++)
			solution_dup[line][col] = solution[line][col];
}

void available_dup(int available_nbs_dup[N][N][N], int available_nbs[N][N][N])
{
	for (int nb = 0; nb < N; nb++)
	{
		for (int line = 0; line < N; line++)
			for (int col = 0; col < N; col++)
				available_nbs_dup[nb][line][col] = available_nbs[nb][line][col];
	}
}