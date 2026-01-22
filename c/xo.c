#include <stdbool.h>

/**
 * @brief Checks if a string contains the same number of 'x' and 'o' characters.
 *
 * - Case-insensitive: 'x' and 'X' are counted as the same, likewise 'o' and 'O'.
 *
 * @param s The input string to check.
 * 
 * @return true if the number of 'x' and 'o' is equal, false otherwise.
 */
bool	xo(const char *s)
{
	int x = 0, o = 0;

	for(;*s; s++)
	{
		if (*s == 'o' || *s == 'O') 
			o++;
		else if (*s == 'x' || *s == 'X')
			x++;
	}
	return (o == x);
}
