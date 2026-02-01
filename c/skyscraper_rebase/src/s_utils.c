#include "skyscraper.h"

/**
 * @param available_nbs The array of available numbers
 * @param line The line
 * @param col The column
 * 
 * @return the smallest possible number in a box
 */
int	min_possibility(int ***available_nbs, int line, int col)
{
	for (int nb = 0; nb < N; nb++)
		if (available_nbs[nb][line][col])
			return available_nbs[nb][line][col];
	return -1;
}

/**
 * @return the reverse position on a column or line
 */
int	rev_nb(int nb)
{
	return (N - nb - 1);
}

//the 3 functions below return the matching position in the clue array

/**
 * @return the position on the right side of a condition
 */
int	right_cond_nb(int line)
{
	return (N + line);
}

/**
 * @return the position on the bottom side of a condition
 */
int	bottom_cond_nb(int col)
{
	return (N * 2 + rev_nb(col));
}

/**
 * @return the position on the left side of a condition
 */
int	left_cond_nb(int line)
{
	return (N * 3 + rev_nb(line));
}

/**
 * @return The column in line if nb has been found, else return -1
 */
int	is_nb_on_line(int nb, int line, int **solution)
{
	for (int col = 0; col < N; col++)
		if (solution[line][col] == nb)
			return (col);
	return (-1);
}

/**
 * @return The line in column if nb has been found, else return -1
 */
int	is_nb_on_col(int nb, int col, int **solution)
{
	for (int line = 0; line < N; line++)
		if (solution[line][col] == nb)
			return (line);
	return (-1);
}

/**
 * @brief
 * Check if between the start of a side and N, there's lacking towers
 * 
 * @param way		The reading way, of type @ref Direction
 * @param solution	The array of solution
 * @param line		The line in the `solution`
 * @param col		The column in the `solution`
 * 
 * @return `true` if there's one missing nb, else return `false`
 */
bool	lacking_towers(Direction way, int line, int col, int **solution)
{
	if (way == LTR)
	{
		for (col = 0; col < N && solution[line][col] != N; col++)
			if (!solution[line][col])
				return (true);
	}
	else if (way == RTL)
	{
		for (col = N - 1; col >= 0 && solution[line][col] != N; col--)
			if (!solution[line][col])
				return (true);
	}
	else if (way == TTB)
	{
		for (line = 0; line < N && solution[line][col] != N; line++)
			if (!solution[line][col])
				return (true);
	}
	else
	{
		for (line = N - 1; line >= 0 && solution[line][col] != N; line--)
			if (!solution[line][col])
				return (true);
	}
	return (false);
}

/**
 * @brief
 * Check how much empty boxes there is until N is found
 * 
 * @param way		The reading way, of type @ref Direction
 * @param solution	The array of solution
 * @param line		The line in the `solution`
 * @param col		The column in the `solution`
 * 
 * @return the amount of empty boxes before N
 */
int	empty_boxes_until_N(Direction way, int line, int col, int **solution)
{
	if (((way == BTT || way == TTB) && is_nb_on_col(N, col, solution) == -1)
		|| ((way == RTL || way == LTR) && is_nb_on_line(N, line, solution) == -1))
		return 0;
	int empty_boxes = 0;

	if (way == LTR)
	{
		for (col = 0; col < N && solution[line][col] != N; col++)
			if (!solution[line][col])
				empty_boxes++;
	}
	else if (way == RTL)
	{
		for (col = N - 1; col >= 0 && solution[line][col] != N; col--)
			if (!solution[line][col])
				empty_boxes++;
	}
	else if (way == TTB)
	{
		for (line = 0; line < N && solution[line][col] != N; line++)
			if (!solution[line][col])
				empty_boxes++;
	}
	else
	{
		for (line = N - 1; line >= 0 && solution[line][col] != N; line--)
			if (!solution[line][col])
				empty_boxes++;
	}
	return (empty_boxes);
}

/**
 * @brief
 * Check how much towers are visible until N, empty boxes are not considered visible
 * 
 * @param way		The reading way, of type @ref Direction
 * @param solution	The array of solution
 * @param line		The line in the `solution`
 * @param col		The column in the `solution`
 * 
 * @return the amount of visible towers
 */
int	visible_towers(Direction way, int line, int col, int **solution)
{
	if (((way == BTT || way == TTB) && is_nb_on_col(N, col, solution) == -1)
		|| ((way == RTL || way == LTR) && is_nb_on_line(N, line, solution) == -1))
		return 0;
	int visible_towers = 1;
	int prev_tower = 0;
	if (way == LTR)
	{
		for (col = 0; col < N && solution[line][col] != N; col++)
			if (solution[line][col] && prev_tower < solution[line][col])
			{
				visible_towers++;
				prev_tower = solution[line][col];
			}
	}
	else if (way == RTL)
	{
		for (col = N - 1; col >= 0 && solution[line][col] != N; col--)
			if (solution[line][col] && prev_tower < solution[line][col])
			{
				visible_towers++;
				prev_tower = solution[line][col];
			}
	}
	else if (way == TTB)
	{
		for (line = 0; line < N && solution[line][col] != N; line++)
			if (solution[line][col] && prev_tower < solution[line][col])
			{
				visible_towers++;
				prev_tower = solution[line][col];
			}
	}
	else
	{
		for (line = N - 1; line >= 0 && solution[line][col] != N; line--)
			if (solution[line][col] && prev_tower < solution[line][col])
			{
				visible_towers++;
				prev_tower = solution[line][col];
			}
	}
	return (visible_towers);
}

/**
 * @brief
 * Check if there's lacking towers between where line or col is and N
 * 
 * @param way		The reading way, of type @ref Direction
 * @param solution	The array of solution
 * @param line		The line in the `solution`
 * @param col		The column in the `solution`
 * 
 * @return `true` if there's one missing nb, else return `false`
 */
bool	last_boxs_are_filled(Direction way, int **solution, int line, int col)
{
	if (way == LTR)
	{
		while (col < N)
			if (!solution[line][col++])
				return (false);
	}
	else if (way == RTL)
	{
		while (col >= 0)
			if (!solution[line][col--])
				return (false);
	}
	else if (way == BTT)
	{
		while (line >= 0)
			if (!solution[line--][col])
				return (false);
	}
	else
	{
		while (line < N)
			if (!solution[line++][col])
				return (false);
	}
	return (true);
}

/**
 * @brief
 * Check if there's lacking towers between where line or col is and N
 * 
 * @param way		The reading way, of type @ref Direction
 * @param solution	The array of solution
 * @param line		The line in the `solution`
 * @param col		The column in the `solution`
 * 
 * @return `true` if there's one missing nb, else return `false`
 */
bool	last_boxs_arent_filled(Direction way, int **solution, int line, int col)
{
	if (way == LTR)
	{
		while (--col >= 0)
			if (solution[line][col])
				return (false);
	}
	else if (way == RTL)
	{
		while (++col < N)
			if (solution[line][col])
				return (false);
	}
	else if (way == BTT)
	{
		while (++line < N)
			if (solution[line][col])
				return (false);
	}
	else
	{
		while (--line >= 0)
			if (solution[line][col])
				return (false);
	}
	return (true);
}

/**
 * @brief
 * Find the tiniest available number and return it
 * 
 * @param available_nbs	The array of available numbers
 * @param start_nb		The number that start the reasearch
 * @param line			The line in `available_nbs`
 * @param col			The column in `available_nbs`
 * 
 * @return the number if he exist, else 0
 */
int	tiniest_nb_in_box(int ***available_nbs, int start_nb, int line, int col)
{
	for (int nb = start_nb; nb < N; nb++)
		if (available_nbs[nb][line][col])
			return (nb + 1);//cf init vailability below
	return (0);
}
/**
 * @brief
 * Intialise an array of arrays of arrays of ints.
 * 
 * For example, if N = 4 :
 * 
 *.....[0]................[1]................[2]................[3]
 *
 * 	1, 1, 1, 1......2, 2, 2, 2......3, 3, 3, 3......4, 4, 4, 4
 * 
 * 	1, 1, 1, 1......2, 2, 2, 2......3, 3, 3, 3......4, 4, 4, 4
 * 
 * 	1, 1, 1, 1......2, 2, 2, 2......3, 3, 3, 3......4, 4, 4, 4
 * 
 * 	1, 1, 1, 1......2, 2, 2, 2......3, 3, 3, 3......4, 4, 4, 4
 * 
 * @return
 * The array of arrays of arrays of ints.
 */
void	init_availability(int available_nbs[N][N][N])
{
	//first int in the numbers placable
	for (int nb = 0; nb < N; nb++)
	{
		//second int is lines
		for (int line = 0; line < N; line++)
		{
			//third line is columns
			for (int column = 0; column < N; column++)
				available_nbs[nb][line][column] = nb + 1;//nb starts at zero
		}
	}
}

int	**init_solution(void)
{
	int **solution = calloc(sizeof(int *), N);
	for (int i = 0; i < N; i++)
		solution[i] = calloc(sizeof(int), N);
		return solution;
}
