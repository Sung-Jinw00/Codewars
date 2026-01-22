#include <stdlib.h>
#include <string.h>

/**
 * @brief Reajust the result string by removing leading zeros.
 *
 * @param str String containing the current result.
 * @param k Index where the meaningful digits start.
 *
 * @note
 * This function shifts all characters starting from index `k` to the beginning of the string
 * and zeroes out the remaining part.
 */
void	reajust(char *str, int k)
{
	int i = 0;

	if (str[k] < '0')
		k++;
	while (k <= 3000)
		str[i++] = str[k++];
	while (str[--k] != 0)
		str[k] = 0;
}

/**
 * @brief Add a single digit to a given position in the result string, handling carry.
 *
 * @param str Result string.
 * @param k Position in the string to add the digit.
 * @param result Single-digit value to add (0-9).
 *
 * @note
 * If adding the digit causes the character to exceed '9', the carry is propagated to the previous digit.
 */
void	add(char *str, int k, int result)
{
	if (str[k] < '0')
		str[k] += '0';
	str[k] += result % 10;
	if (str[k] > '9')
	{
		str[k] = '0' + (str[k] - '9');
		str[k - 1]++;
	}
}

/**
 * @brief Multiply two non-negative integer numbers represented as strings.
 *
 * @param a First number as a string (e.g., "52436").
 * @param b Second number as a string (e.g., "144").
 *
 * @return
 * Newly allocated string containing the product of `a` and `b`. User is responsible for freeing it.
 *
 * @note
 * The function can handle numbers larger than what fits in standard integer types.
 * The multiplication is performed manually using the grade-school algorithm.
 *
 * @example
 * const char *a = "52436";
 * const char *b = "144";
 * char *product = multiply(a, b);
 * printf("%s\n", product); // prints "7550784"
 * free(product);
 */
char *multiply(const char *a, const char *b)
{
	char str[3001] = {0};
	int len_a = strlen(a) - 1, max = 3000, k = max, result = 0;

	for (int len_b = strlen(b) - 1; len_b >= 0; len_b--)
	{
		for (int i = len_a; i >= 0; i--)
		{
			result = (a[i] - '0') * (b[len_b] - '0');//je prends la multiplication de mes nombres
			add(str, k--, result % 10);//j'ajoute le nombre et je passe a la dizaine suivante
			while (result >= 10)//si le nombre est toujours plus grand que 10, je l'ajoute avec une variable temporaire
			{
				result /= 10;
				add(str, k--, result % 10);
			}
		}
		k = --max;
	}
	reajust(str, k);
	return (strdup(str));
}

#include <stdio.h>

int	main(void)
{
	char *str = multiply("144", "52436");
	printf("%s\n", str);
	free(str);
	return (0);
}
