#include <stdbool.h>
#include <string.h>

/**
 * @brief Checks if a string ends with a given substring.
 *
 * Compares the end of the string with the given ending.
 *
 * @param string The input string.
 * @param ending The substring to check at the end.
 * 
 * @return true if the string ends with the given substring, false otherwise.
 */
bool solution(const char *string, const char *ending)
{
    return (!strcmp(string + (strlen(string) - strlen(ending)), ending));
}

#include <stdio.h>
int main(void)
{
	bool answer = solution("abc", "bc");
	if (answer == true)
		printf("bon\n");
	else
		printf("pas bon\n");
	return (0);
}