#include <string.h>
#include <limits.h>

/**
 * @brief Possible moves of a knight on a chessboard
 */
short moves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

/**
 * @brief Recursive search for the minimal number of knight moves
 *
 * This function recursively explores all possible knight moves up to a depth limit
 * to determine the minimal number of moves to reach the goal position.
 *
 * @param x Current column (0-7)
 * @param y Current row (0-7)
 * @param goal_x Target column (0-7)
 * @param goal_y Target row (0-7)
 * @param depth Current recursion depth (used to limit search)
 * 
 * @return Minimum number of moves required to reach the target. 
 *         Returns SHRT_MAX if target is unreachable within depth limit.
 */
short recursive_srch(short x, short y, short goal_x, short goal_y, short depth)
{
	//out of bounds or too deep
	if (x < 0 || x > 7 || y < 0 || y > 7 || depth > 6)
		return (SHRT_MAX);
	if (x == goal_x && y == goal_y)
		return (0);
	short min_moves = SHRT_MAX;
	for (short i = 0; i < 8; i++)
	{
		//send every possible move from the x, y position
		short res = recursive_srch(x + moves[i][0], y + moves[i][1], goal_x, goal_y, depth + 1);
		if (res != SHRT_MAX)
			min_moves = min_moves < (res + 1) ? min_moves : (res + 1);
	}
	return (min_moves);
}

/**
 * @brief Computes the minimum number of moves a knight needs to travel from one square to another on a chessboard
 *
 * Converts algebraic chess notation (e.g., "a1") into coordinates and calls a recursive search
 * to find the minimal path.
 *
 * @param p1 Starting square as a string (e.g., "a1")
 * @param p2 Target square as a string (e.g., "c1")
 *
 * @return Minimum number of knight moves from `p1` to `p2`. Returns 0 if positions are invalid
 *         or identical.
 */
short knight(const char *p1, const char *p2)
{
	short x = p1[0] - 'a', y = p1[1] - '1', final_x = p2[0] - 'a', final_y = p2[1] - '1';
	if (!strcmp(p1, p2)
		|| x < 0 || x > 7 || y < 0 || y > 7
		|| final_x < 0 || final_x > 7 || final_y < 0 || final_y > 7)
		return (0);
	short answer = recursive_srch(x, y, final_x, final_y, 0);
	return (answer != SHRT_MAX) ? answer : 0;
}

#include <stdio.h>

int	main(void)
{
	short answer = knight("a1", "c1");
	printf("%d\n", answer);
	return (0);
}