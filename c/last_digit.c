#include <math.h>
#include <string.h>

/**
 * @brief Computes the last decimal digit of a^b for large numbers.
 *
 * This function calculates only the last digit of `a` raised to the power `b`.
 * Both `a` and `b` are provided as strings to support very large numbers
 * beyond standard integer types.
 *
 * @param a Base as a null-terminated string of digits.
 * @param b Exponent as a null-terminated string of digits.
 *
 * @return
 * 
 * - The last digit of a^b (0-9).
 * 
 * - 1 if b is "0".
 * 
 * - 0 if a is "0".
 *
 * @note Only the last two digits of the exponent are used to determine the pattern
 * of last digits, which is sufficient due to cyclicity of last digits in powers.
 */
int last_digit(const char *a, const char *b)
{
    if (*b == '0')
		return (1);
    if (*a == '0')
		return (0);
    
	size_t	len_b = strlen(b);
    int x = a[strlen(a) - 1] - '0';
    int y = (b[len_b - 1] - '0');
    if (len_b > 1)
		y += (b[len_b - 2] - '0') * 10;
    y = y % 4 + 4;  
    return ((int)pow(x, y) % 10);
}

#include <stdio.h>

int main(void)
{
	char *d1 = "0";
	char *d2 = "1";
	int expected = 1;
	int answer = last_digit(d1, d2);

	printf("answer = %d\n", answer);
	if (answer != expected)
		printf("\ndifference !\nexpected = %d\n", expected);
	else
		printf("\nno diff, congrats !\n");
	return (0);
}