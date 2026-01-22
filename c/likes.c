#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Compute the number of digits required to represent an integer as a string.
 *
 * @param nb The integer to analyze.
 * @param sign Pointer to an int that will be set to 1 if the number is negative.
 * 
 * @return Total number of characters needed (including '-' if negative).
 */
static int	init_vals(long nb, int *sign)
{
	int	i = 0, digits = 1;

	if (nb < 0)
	{ nb = -nb; *sign = 1; }
	while (nb >= 10)
	{ nb /= 10; digits++; }
	i = digits + *sign;
	return (i);
}

/**
 * @brief Convert an integer to a dynamically allocated string.
 *
 * @param n The integer to convert.
 * 
 * @return Pointer to a null-terminated string representing the integer.
 */
char	*itoa(int n)
{
	long	nb = n;
	int		sign = 0, i = init_vals(nb, &sign);
	char	*cpy = malloc(sizeof(char) * i + 1);
	
	if (!cpy)
		return (NULL);
	if (sign)
	{ nb = -nb; cpy[0] = '-'; }
	cpy[i--] = '\0';
	while (i >= sign)
	{
		cpy[i--] = nb % 10 + '0';
		nb /= 10;
	}
	return (cpy);
}

/**
 * @brief Concatenate two strings into a new dynamically allocated string.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * 
 * @return New string containing s1 followed by s2.
 * 
 * User is responsible for freeing the memory.
 */
char	*strjoin(char const *s1, char const *s2)
{
	size_t	i, j, len = strlen(s1) + strlen(s2) + 1;
	char	*new_string = malloc(len);

	if (!new_string)
		return (NULL);
	for (i = 0; s1[i] != '\0'; i++)
		new_string[i] = s1[i];
	for (j = 0; s2[j] != '\0'; i++, j++)
		new_string[i] = s2[j];
	new_string[i] = '\0';
	return (new_string);
}

/**
 * @brief Concatenate two strings into a new string and free the first string.
 *
 * @param s1 First string to append from. Will be freed.
 * @param s2 Second string to append.
 * 
 * @return New dynamically allocated string containing s1 + s2.
 */
char	*join_free(char *s1, const char *s2)
{
	char *newstring = strjoin(s1, s2);
	free(s1);
	return (newstring);
}

/**
 * @brief Generate a string describing who likes an item (Facebook style).
 *
 * Examples:
 * 
 * - 0 names: "no one likes this"
 * 
 * - 1 name: "Alice likes this"
 * 
 * - 2 names: "Alice and Bob like this"
 * 
 * - 3 names: "Alice, Bob and Charlie like this"
 * 
 * - >3 names: "Alice, Bob and 2 others like this"
 *
 * @param n Number of names.
 * @param names Array of strings containing names.
 * 
 * @return Dynamically allocated string describing the likes.
 * 
 * User is responsible for freeing the returned string.
 */
char	*likes(size_t n, const char *const names[n])
{
	char	*str = NULL, *nb = NULL;

	if (n == 0)
		return (strdup("no one likes this"));
	else if (n == 1)
		return (strjoin(names[0], " likes this"));
	else if (n == 2)
		return (join_free(join_free(strjoin(names[0], " and "), names[1]), " like this"));
	str = join_free(join_free(strjoin(names[0], ", "), names[1]), " and ");
	if (n == 3)
		return (join_free(join_free(str, names[2]), " like this"));
	else
	{
		nb = itoa(n - 2);
		str = join_free(join_free(str, nb), " others like this");
		return (free(nb), str);
	}
}

int	main(int ac, char **av)
{
	char	*str = likes(ac - 1, (const char *const *)av + 1);

	printf("%s\n", str);
	free(str);
	return (0);
}
