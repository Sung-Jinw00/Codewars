#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * @brief
 * Validate two numeric strings for multiplication.
 *
 * This function checks whether both input strings represent valid integers
 * that can be multiplied. A valid string:
 * - May start with a single optional '-' sign.
 * - Must otherwise contain only digit characters.
 *
 * @param s1 First string to validate.
 * @param s2 Second string to validate.
 *
 * @return
 * - 1 if both strings are valid numeric representations.
 * 
 * - 0 if one of the strings contains invalid characters.
 */
static int	verifications(const char *s1, const char *s2)
{
	int	i = 0, j = 0, len_s1 = strlen(s1), len_s2 = strlen(s2);

	if (s1[i] == '-')
		i++;
	if (s2[j] == '-')
		j++;
	while (s1[i] || s2[j])
		if ((i < len_s1 && !isdigit(s1[i++]))
			|| (j < len_s2 && !isdigit(s2[j++])))
			return (0);
	return (1);
}

/**
 * @brief
 * Perform digit-by-digit multiplication of two numeric strings.
 *
 * This function multiplies the absolute values of two numeric strings using
 * a manual multiplication algorithm (similar to pen-and-paper multiplication).
 * The result is stored as individual digits in the provided result buffer.
 *
 * The buffer is expected to be large enough to hold the intermediate results.
 * Digits are accumulated from right to left, and carries are propagated
 * during the computation.
 *
 * @param result Buffer used to store the intermediate multiplication result.
 *               Each cell contains a single digit (0–9).
 * @param s1 First numeric string operand (may contain a leading '-').
 * @param s2 Second numeric string operand (may contain a leading '-').
 *
 * @return The index of the most significant digit written in the result buffer.
 */
static int	calculation(char *result, const char *s1, const char *s2)
{
	int start_result = 500, i_result;

	for (int i_s1 = strlen(s1) - 1; i_s1 >= 0 && s1[i_s1] != '-'; i_s1--)
	{
		int i_s2 = strlen(s2) - 1;
		i_result = start_result--;
		while (i_s2 >= 0 && s2[i_s2] != '-')
		{
			result[i_result] += (s1[i_s1] - '0') * (s2[i_s2--] - '0');
			while (result[i_result] >= 10)
			{
				result[i_result] -= 10;
				result[i_result - 1]++;
			}
			i_result--;
		}
	}
	return (i_result);
}

/**
 * @brief
 * Multiply 2 numbers in a string format, return the value of the 2 numbers in
 * a string, the values of s1 and s2 can be greater than a long long.
 * 
 * Requirements :
 * 
 * - The only sign tolerated is one and only '-' sign if the number is
 * negative.
 * 
 * - Besides this sign, if the string is not composed of numbers exclusively,
 * the function will return NULL.
 * 
 * @return
 * - NULL if one of the strings is NULL or empty, or if the requirements aren't
 * fulfilled.
 * 
 * - The multiplication of the 2 numbers in a memory allocated string.
 * 
 * @note
 * The memory released of the string returned by the function is the
 * responsibility of the user.
*/
char	*ft_multiply(const char *s1, const char *s2)
{
	if (!s1 || !s1[0] || !s2 || !s2[0] || !verifications(s1, s2))
		return (NULL);
	static char	result[501] = {0};
	int start_result = -1, i = calculation(result, s1, s2) + 1;

	while (result[i - 1] != 0 || result[i - 2] != 0 || result[i - 3] != 0)
		i--;
	if (((s1[0] == '-') + (s2[0] == '-')) == 1)
		result[++start_result] = '-';
	while (i < 501)
		result[++start_result] = '0' + result[i++];
	result[++start_result] = 0;
	return (strdup(result));
}

/* #include <unistd.h>

int main(int ac, char **av)
{
	if (ac != 3)
		return (0);

	char *str = ft_multiply(av[1], av[2]);
	write(1, str, strlen(str));
	write(1, "\n", 1);
	if (!strcmp(str, "1449557665776209901793684752"))
		return(free(str), write(1, "ok\n", 3));
	return(free(str), write(1, "naze\n", 5));
} */
