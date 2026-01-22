#include <stdlib.h>

/**
 * @brief Flattens a 2D matrix into a 1D array in "snail" order.
 *
 * Given a 2D matrix of integers with specified rows and columns,
 * returns a dynamically allocated 1D array containing all elements
 * in a clockwise spiral starting from the top-left corner.
 *
 * - Start from the top-left corner
 * 
 * - Move right across the top row
 * 
 * - Move down the rightmost column
 * 
 * - Move left across the bottom row
 * 
 * - Move up the leftmost column
 * 
 * - Repeat the above steps inward until all elements are traversed
 *
 * @param outsz Pointer to a size_t variable that will hold the length
 *               of the resulting array.
 * @param mx Pointer to an array of pointers to integer arrays representing
 *           the matrix.
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * 
 * @return Pointer to a newly allocated 1D array containing the elements
 *         in snail order, or NULL if rows or cols are zero. The caller
 *         is responsible for freeing the allocated memory.
 * 
 */
int	*snail(size_t *outsz, const int **mx, size_t rows, size_t cols)
{
	if (!rows || !cols)
	{
		*outsz = 0;
		return (NULL);
	}
	*outsz = rows * cols;
	int	*answer = calloc(sizeof(int), *outsz);
	int start_row = -1, start_cols = 0, i = 0, j = -1, k = 0;

	while(start_row <= (int)rows && start_cols <= (int)cols)
	{
		while (++j < (int)rows)
			answer[k++] = mx[i][j];
		j--;
		start_row++;
		if (start_row >= (int)rows && start_cols >= (int)cols)
			break ;
		while (++i < (int)cols)
			answer[k++] = mx[i][j];
		i--;
		start_cols++;
		if (start_row >= (int)rows && start_cols >= (int)cols)
			break ;
		while (--j >= start_row)
			answer[k++] = mx[i][j];
		j++;
		cols--;
		if (start_row >= (int)rows && start_cols >= (int)cols)
			break ;
		while (--i >= start_cols)
			answer[k++] = mx[i][j];
		i++;
		rows--;
	}
	return (answer);
}

#include <stdio.h>

int	int_arr_cmp(int *result, const int *answer, size_t len_tabs)
{
	if (!result && !answer)
		return (0);
	if ((!result && answer) || (result && !answer))
		return (1);
	for (size_t i = 0; i < len_tabs; i++)
		if (result[i] != answer[i])
			return (1);
	return (0);
}

int	main(void)
{
	const int *tab1[] = {
		(const int[]){1, 2, 3},
		(const int[]){4, 5, 6},
		(const int[]){7, 8, 9}
	};
	const int *tab2[] = {
		(const int[]){1, 2, 3},
		(const int[]){8, 9, 4},
		(const int[]){7, 6, 5}
	};
	const int *tab3[] = {
		(const int[]){1, 2, 3, 1},
		(const int[]){4, 5, 6, 4},
		(const int[]){7, 8, 9, 7},
		(const int[]){7, 8, 9, 7}
	};
	const int **tabs[] = {
		tab1,
		tab2,
		tab3
	};
	const int *answer[] = {
		(const int[]){1, 2, 3, 6, 9, 8, 7, 4, 5},
		(const int[]){1, 2, 3, 4, 5, 6, 7, 8, 9},
		(const int[]){1, 2, 3, 1, 4, 7, 7, 9, 8, 7, 7, 4, 5, 6, 9, 8}
	};
	size_t len_tabs[] = {3, 3, 3, 3, 4, 4};
	size_t lens[] = {9, 9, 16};

	for (int i = 0; i < 3; i++)
	{
		size_t len;
		int *result = snail(&len, tabs[i], len_tabs[i * 2], len_tabs[(i * 2) + 1]);
		if (len == lens[i] && !int_arr_cmp(result, answer[i], lens[i]))
			printf("no diff, congrats !\n");
		else
		{
			printf("difference, expected :\n-my len = %zu, expected = %zu\n\n- my tab = {", len, lens[i]);
			for (int j = 0; j < (int)len; j++)
			{
				printf("%d", result[j]);
				if (j < (int)len - 1)
					printf(", ");
			}
			printf("}\nexpected = {");
			for (int j = 0; j < (int)len; j++)
			{
				printf("%d", answer[i][j]);
				if (j < (int)len - 1)
					printf(", ");
			}
			printf("}\n\n\n");
		}
		free(result);
	}
}
