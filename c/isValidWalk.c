#include <stdbool.h>
#include <string.h>

/**
 * @brief
 * Check whether a walk is valid.
 *
 * A walk is considered valid if:
 * - It contains exactly 10 steps.
 * - Each step is one of the following characters:
 *   'n' (north), 's' (south), 'e' (east), 'w' (west).
 * - The walk returns to the starting point (net displacement is zero).
 *
 * The function simulates the walk on a 2D grid and checks whether the final
 * coordinates match the starting position.
 *
 * @param walk
 * A null-terminated string representing the walk directions.
 *
 * @return
 * - true if the walk is valid.
 * - false otherwise.
 */
bool isValidWalk(const char *walk)
{
	int x = 0, y = 0;
	
	if (strlen(walk) != 10)
		return false;
	for(int i = 0; walk[i]; i++)
	{
		if (walk[i] == 'n')
			x++;
		else if (walk[i] == 's')
			x--;
		else if (walk[i] == 'e')
			y++;
		else if (walk[i] == 'w')
			y--;
	}
   	return (!x && !y);
}