#include <stdbool.h>
#include <math.h>

/**
 * @brief
 * Check whether a number is a prime number.
 *
 * A prime number is an integer greater than 1 that has no positive divisors
 * other than 1 and itself.
 *
 * This function uses an optimized trial division:
 * 
 * - Handles small edge cases (numbers < 2, 2 and 3).
 * 
 * - Eliminates multiples of 2 and 3 early.
 * 
 * - Tests only numbers of the form 6k ± 1 up to sqrt(num).
 *
 * @param num
 * The integer to test for primality.
 *
 * @return
 * 
 * - true if `num` is a prime number.
 * 
 * - false otherwise.
 */
bool is_prime(int num)
{
	if (num == 2 || num == 3)
		return true;
	if (num < 2 || num % 2 == 0 || num % 3 == 0)
		return false;
	for (int i = 5; i <= sqrt(num); i += 6)
		if (num % i == 0 || num % (i + 2) == 0)
			return false;
	return true;
}

#include <stdio.h>

int main(void)
{
	bool res = is_prime(75);
	return (printf("%d", res));
}