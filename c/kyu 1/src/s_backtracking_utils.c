#include "skyscraper.h"

void	sol_dup(int sol_save[N][N], int **solution, int dest)
{
	if (dest == 0)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				sol_save[i][j] = solution[i][j];
	}
	else
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				solution[i][j] = sol_save[i][j];
	}
}

/* 
display *available_amount[0]@7
display *available_amount[1]@7
display *available_amount[2]@7
display *available_amount[3]@7
display *available_amount[4]@7
display *available_amount[5]@7
display *available_amount[6]@7

*/

void set_available_amount(int available_amount[N][N], int ***available_nbs)
{
	for (int line = 0; line < N; line++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int nb = 0; nb < N; nb++)
			{
				if (available_nbs[nb][line][col])
					available_amount[line][col]++;
			}
		}
	}
}

void	get_pos_least_amount(int start_line, int start_col, int pos[2], int available_amount[N][N])
{
	int line = start_line, col = start_col;
	if (line || col)
	{
		if (col + 1 == N)
		{
			col = 0;
			line++;
		}
		else
			col++;
		if (line == N)
			return ;
	}
	while (line < N)
	{
		while (col < N)
		{
			if (available_amount[line][col] != 1)
				break ;
			col++;
		}
		if (available_amount[line][col] != 1)
				break ;
		line++;
		col = 0;
	}
	int least_amount = available_amount[line][col];
	while (line < N)
	{
		while (col < N)
		{
			int cur_amount = available_amount[line][col];
			if (cur_amount > 1 && cur_amount < least_amount)
			{
				least_amount = cur_amount;
				pos[0] = line;
				pos[1] = col;
				if (cur_amount == 2)
					return ;
			}
			col++;
		}
		line++;
		col = 0;
	}
}
