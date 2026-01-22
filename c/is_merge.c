#include <stdbool.h>

/**
 * @brief Check whether a string is a valid merge of two other strings.
 *
 * This function determines if the string `s` can be formed by interleaving
 * the characters of `part1` and `part2` while preserving the relative order
 * of characters from each string.
 *
 * The merge does not require characters from `part1` and `part2` to be
 * contiguous, but their internal order must remain unchanged.
 *
 * @param s The target string to validate.
 * @param part1 The first source string.
 * @param part2 The second source string.
 *
 * @return true if `s` is a valid merge of `part1` and `part2`,
 *         false otherwise.
 *
 * @note This implementation uses recursion and may have exponential
 *       time complexity in the worst case due to overlapping subproblems.
 */
bool is_merge(const char *s, const char *part1, const char *part2)
{
    if (!*s)
        return !*part1 && !*part2;
    return (*part1 == *s && is_merge(s + 1, part1 + 1, part2)) || (*part2 == *s && is_merge(s + 1, part1, part2 + 1));
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
	char *inputs[][3] = {
		{"aabaaaaaba", "aabaa", "aaaab"},
		{"vanxuvxceevcemjcrkku", "vnuvxcecmj", "axevecrkku"},
		{"codewars", "codew", "wars"},
		{"codewars", "code", "warss"},
		{"codewars", "code", "code"},
		{"codewars", "codewars", ""},
		{"codewars", "", "codewars"},
		{"acab", "ab", "ac"},
		{"acab", "ac", "ab"},
		{"acab", "aa", "cb"},
		{"acab", "cb", "aa"},
		{"acab", "ca", "ba"},
		{"acab", "bc", "aa"},
		{"acab", "cb", "aaa"},
		{"", "", ""},
		{0x0}
	};	
	bool answer, expected[] = {
		true,
		true,
		false,
		false,
		false,
		true,
		true,
		true,
		true,
		true,
		true,
		false,
		false,
		false,
		true
	};	

	for (int i = 0; inputs[i][0]; i++)
	{
		answer = is_merge(inputs[i][0], inputs[i][1], inputs[i][2]);
		printf(UNDERLINE BOLD"\n\nTest %d :\n"RESET"answer = %d\n", i + 1, answer);
		if (answer != expected[i])
			printf("\ndifference !\nexpected = %d\n", expected[i]);
		else
			printf("\nno diff, congrats !\n");
	}
	return (0);
}
