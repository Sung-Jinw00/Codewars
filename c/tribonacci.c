#include <stdlib.h>

/**
 * @brief Generates the first n elements of a Tribonacci sequence.
 *
 * - The sequence starts with the 3-element signature array.
 * 
 * - Each next element is the sum of the previous three elements.
 * 
 * - If n is 0, returns NULL.
 *
 * @param signature Array of 3 long long integers to start the sequence.
 * @param n Number of elements to generate.
 * 
 * @return A newly allocated array of long long containing the Tribonacci sequence.
 *         The caller is responsible for freeing the memory.
 */
long long *tribonacci(const long long signature[3], size_t n)
{
	long long *tab = calloc(sizeof(long long), n);
	size_t i = 0, lvl = 0;

	if (!n)
		return (NULL);
	if (n >= 1)
		tab[0] = signature[0];
	if (n >= 2)
		tab[1] = signature[1];
	if (n >= 3)
		tab[2] = signature[2];
	while (i + lvl + 3 < n)
	{
		tab[i + lvl + 3] = (tab[i + lvl]) + (tab[(i + 1) + lvl]) + (tab[(i + 2) + lvl]);
		lvl++;
	}
	return (tab);
}

#include <stdio.h>

int strintcmp(long long *result, long long *expected, size_t n)
{
	size_t i = 0;

	while (i < n)
	{
		if (result[i] != expected[i])
			return (1);
		i++;
	}
	return (0);
}

int main(void)
{
	const long long signature0[3] = {1, 1, 1};
	size_t n = 10;
	long long *result, expected0[10] = {1, 1, 1, 3, 5, 9, 17, 31, 57, 105};
	result = tribonacci(signature0, n);
	if (!strintcmp(result, expected0, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);

    const long long signature1[3] = {0, 0, 1};
    long long expected1[10] = {0, 0, 1, 1, 2, 4, 7, 13, 24, 44};
    result = tribonacci(signature1, n);
	if (!strintcmp(result, expected1, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);
    const long long signature2[3] = {0, 1, 1};
    long long expected2[10] = {0, 1, 1, 2, 4, 7, 13, 24, 44, 81};
    result = tribonacci(signature2, n);
	if (!strintcmp(result, expected2, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);
    const long long signature3[3] = {1, 0, 0};
    long long expected3[10] = {1, 0, 0, 1, 1, 2, 4, 7, 13, 24};
    result = tribonacci(signature3, n);
	if (!strintcmp(result, expected3, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);

    const long long signature4[3] = {0, 0, 0};
    
    long long expected4[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    result = tribonacci(signature4, n);
	if (!strintcmp(result, expected4, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);

    const long long signature5[3] = {0, 0, 0};
    
    long long expected5[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    result = tribonacci(signature5, n);
	if (!strintcmp(result, expected5, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);

    const long long signature6[3] = {1, 2, 3};
    
    long long expected6[10] = {1, 2, 3, 6, 11, 20, 37, 68, 125, 230};
    result = tribonacci(signature6, n);
	if (!strintcmp(result, expected6, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);

    const long long signature7[3] = {3, 2, 1};
    
    long long expected7[10] = {3, 2, 1, 6, 9, 16, 31, 56, 103, 190};
    result = tribonacci(signature7, n);
	if (!strintcmp(result, expected7, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);

    const long long signature8[3] = {42, 55, 70};
    n = 1;
    long long expected8[1] = {42};
    result = tribonacci(signature8, n);
	if (!strintcmp(result, expected8, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);

    const long long signature9[3] = {300, 200, 100};
    n = 0;
    long long *expected9 = NULL;
    result = tribonacci(signature9, n);
	if (!strintcmp(result, expected9, n))
		printf("1st test passed\n");
	else
		return (free(result), printf("1st test failed\n"));
	free(result);
}
