#include <stdbool.h>
#include <ctype.h>

/**
 * @brief
 * Check if a string is alphanumeric
 * 
 * @param str_in a string
 * 
 * @return `true` if str_in exist and is alphanumeric, else `false`
 */
bool alphanumeric(const char *str_in)
{
	if (!*str_in) return(false);
	while (*str_in++) if (!isalnum(*str_in)) return (false);
	return (true);
}

#include <stdio.h>

# ifndef RESET
#  define RESET				"\033[0m"
# endif

/* Bold text */
# ifndef BOLD
#  define BOLD				"\033[1m"
# endif

/* Underlined text */
# ifndef UNDERLINE
#  define UNDERLINE			"\033[4m"
# endif

int main(void)
{
	char *strings[] = {"hello_world",  "PassW0rd", "     ", "a", "", (char *)0x0 };
	bool *expected = {false, true, false, true, false};
	bool answer;

	for (int i = 0; strings[i]; i++)
	{
		answer = alphanumeric(strings[i]);
		printf(UNDERLINE BOLD"\n\nTest %d :\n"RESET"answer = %d\n", i + 1, answer);
		if (answer != expected[i])
			printf("\ndifference !\nexpected = %d\n", expected[i]);
		else
			printf("\nno diff, congrats !\n");
	}
	return (0);
}
