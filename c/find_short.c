#include <sys/types.h>
#include <string.h>

/**
 * @brief Find the length of the shortest word in a string.
 * 
 * This function scans the input string and returns the length of the shortest
 * sequence of non-space characters (i.e., the shortest word). Words are
 * assumed to be separated by one or more spaces.
 * 
 * @param s The input string to analyze. Should be null-terminated.
 * 
 * @return The length of the shortest word in the string. Returns 0 if the string is empty or contains only spaces.
 */
ssize_t find_short(const char *s)
{
	ssize_t len = 0;

	for (ssize_t i = 0, j = 0; s[j] && j < (ssize_t)strlen(s);)
	{
		while (s[j] && s[j] != ' ')
			j++;
		if (len == 0 || len > j - i)
			len = j - i;
		while (s[j] && s[j] == ' ')
			j++;
		i = j;
	}
    return (len);
}

#include <stdio.h>

int main(void)
{
	ssize_t res = 0;

	res = find_short("bitcoin take over the world maybe who knows perhaps");
	if (res == 3)
		printf("1st test passed !\n");
	else
		return (printf("1st test failed !, res = %lu, expected : 3\n", res));
	res = find_short("turns out random test cases are easier than writing out basic ones");
	if (res == 3)
		printf("2nd test passed !\n");
	else
		return (printf("2nd test failed !, res = %lu, expected : 3\n", res));
	res = find_short("lets talk about C the best language");
	if (res == 1)
		printf("3rd test passed !\n");
	else
		return (printf("3rd test failed !, res = %lu, expected : 1\n", res));
	res = find_short("i want to travel the world writing code one day");
	if (res == 1)
		printf("4th test passed !\n");
	else
		return (printf("4th test failed !, res = %lu, expected : 1\n", res));
	res = find_short("Lets all go on holiday somewhere very cold");
	if (res == 2)
		printf("5th test passed !\n");
	else
		return (printf("5th test failed !, res = %lu, expected : 2\n", res));
	res = find_short("Let's travel abroad shall we");
	if (res == 2)
		return (printf("6th and last test passed !\n"));
	else
		return (printf("6th and last test failed !, res = %lu, expected : 2\n", res));
}
