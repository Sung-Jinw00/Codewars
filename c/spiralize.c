/**
 * @brief Fills a square matrix with a clockwise spiral of 1s.
 *
 * - Initializes all elements to 0.
 * 
 * - Starts from the top-left corner and moves in a clockwise spiral.
 * 
 * - Changes direction whenever the next step would go out of bounds
 *   or encounter a previously filled cell.
 *
 * @param n Size of the square matrix.
 * @param spiral The n x n matrix to fill with the spiral pattern.
 */
void spiralize(int n, int spiral[n][n])
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			spiral[i][j] = 0;
	int dl[] = {1, 0, -1, 0};
	int dc[] = {0, 1, 0, -1};
	int x = 0, y = 0, dir = 0;
	for (int steps = 0; steps < (n * n);)
	{
		steps++;
		int c = x + dc[dir];
		int l = y + dl[dir];
		if (c < 0 || c >= n || l < 0 || l >= n
			|| ((!dir && l + 1 < n && spiral[c][l + 1] == 1)
				|| (dir == 1 && c + 1 < n && spiral[c + 1][l] == 1)
				|| (dir == 2 && l - 1 >= 0 && spiral[c][l - 1] == 1)
				|| (dir == 3 && c - 1 >= 0 && spiral[c - 1][l] == 1)))
		{
			dir = (dir + 1) % 4;
			c = x + dc[dir];
			l = y + dl[dir];
		}
		if (spiral[c][l] == 1 || c < 0 || c >= n || l < 0 || l >= n)
			break;
		spiral[x][y] = 1;
		x = c;
		y = l;
	}
}

#include <stdio.h>

int main(void)
{
	int size = 5;
	int arr[5][5] = {0};
	spiralize(size, arr);
	for (int c = 0; c < size; c++) {
		for (int l = 0; l < size; l++) {
			if (arr[c][l] == 1)
				printf("\033[0;32m%d\033[0m, ", arr[c][l]); // vert
			else
				printf("\033[0;31m%d\033[0m, ", arr[c][l]); // rouge
		}
		printf("\n\n");
	}
}