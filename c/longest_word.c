#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Compute the length of a word (sequence of non-space characters).
 *
 * @param str Input string (starting at the word).
 * 
 * @return Length of the first word in the string.
 */
int	ft_strclen(const char *str)
{
	int	i = 0;

	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

/**
 * @brief Extract a word from a string starting at a given position.
 *
 * Allocates memory for the word and updates the index pointer.
 *
 * @param str Input string.
 * @param j Pointer to current index in str. Will be incremented past the word.
 * 
 * @return Dynamically allocated word. Caller must free it.
 */
char	*get_str(const char *str, int *j)
{
	int		i = 0, len = ft_strclen(str + *j);
	char	*word = malloc(sizeof(char) * len + 1);

	while (i < len)
		word[i++] = str[(*j)++];
	return (word[i] = 0, word);
}

/**
 * @brief Find the longest word in a string.
 *
 * If multiple words have the same maximum length, returns the last one.
 * Words are assumed to be separated by spaces.
 *
 * @param words Input string containing one or more words.
 * 
 * @return Dynamically allocated string containing the longest word.
 * 
 * User is responsible for freeing it.
 */
char	*longest_word(const char *words)
{
	int		i = 0;
	char	*str = NULL;

	while (words[i])
	{
		if (words[i] != ' ' && (!str || ft_strclen(str) <= ft_strclen(words + i)))
		{
			free(str);
			str = get_str(words, &i);
		}
		else
			i++;
	}
	return (str);
}

int	main(void)
{
	char	*str;

	str = longest_word("a b c d e fgh");
	if (strcmp(str, "fgh"))
		return (printf("1st test false : str = %s, result expected = fgh\n",
				str));
	else
		printf("1st test passed !\n");
	free(str);
	str = longest_word("three two one");
	if (strcmp(str, "three"))
		return (printf("1st test false : str = %s, result expected = three\n",
				str));
	else
		printf("2nd test passed !\n");
	free(str);
	str = longest_word("grey red blue");
	if (strcmp(str, "blue"))
		return (printf("1st test false : str = %s, result expected = blue\n",
				str));
	else
		printf("all tests passed !\n");
	free(str);
	return (0);
}
