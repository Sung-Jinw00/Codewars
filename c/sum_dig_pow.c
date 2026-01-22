//  don't allocate memory for the results array
//  assign values to the provided results array
//  set length pointer as size of results array
//  after calculations return the results array

#include <stddef.h>
#include <limits.h>
#include <math.h>

/**
 * @brief Computes the sum of the digits of a number, each raised to the power of the number of digits.
 *
 * - Determines the number of digits in the input number.
 * 
 * - Raises each digit to the power of the total number of digits.
 * 
 * - Returns the sum of these powers.
 *
 * @param cur_nb The input number.
 * 
 * @return The sum of the digits each raised to the power of the number of digits.
 */
size_t	pow_sum(size_t cur_nb)
{
	size_t cpy = cur_nb, powr = 1, res = 0;

	while (cpy >= 10)
	{
		cpy /= 10;
		powr++;
	}
	cpy = cur_nb;
	while (cur_nb >= 10)
	{
		if (cpy >= 10)
			cpy %= 10;
		res += pow(cpy, powr--);
		cur_nb /= 10;
		cpy = cur_nb;
	}
	res += cur_nb;
	return (res);
}

/**
 * @brief Finds all numbers in a range whose digits raised to successive powers sum to the number itself.
 *
 * - Iterates from `a` to `b` inclusive.
 * 
 * - Checks each number using `pow_sum`.
 * 
 * - Stores matching numbers in the provided `results` array.
 * 
 * - Sets `*length` to the number of results found.
 *
 * @param a Start of the range.
 * @param b End of the range.
 * @param results Pre-allocated array to store the results.
 * @param length Pointer to a size_t variable that will hold the number of results.
 * 
 * @return Pointer to the `results` array.
 */
size_t *sum_dig_pow(size_t a, size_t b, size_t *results, size_t *length)
{
    size_t cur_nb = a, i = 1, sum = 0;
	int count = 0;

	while (cur_nb <= b)
	{
		if (cur_nb < 10)
			results[count++] = cur_nb;
		else
		{
			sum = pow_sum(cur_nb);
			if (sum == cur_nb)
				results[count++] = cur_nb;
			i = 1;
			sum = 0;
		}
		cur_nb++;
	}
	*length = count;
    return (results);
}

#include <stdio.h>

int main(void)
{
	size_t a = 0, b = 100, results[500] = {0};
	size_t length = 0, i = 0;
	sum_dig_pow(a, b, results, &length);
	printf("%zu\n", length);
	while (i < length)
	{
		printf("%llu", results[i]);
		if (i + 1 < length)
			printf(", ");
		i++;
	}
	printf("\n");
	return (0);
}