#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_strclen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	*get_str(const char *str, int *j)
{
	char	*word;
	int		i = 0, len = ft_strclen(str + *j);
	word = malloc(sizeof(char) * len + 1);
	while (i < len)
	{
		word[i] = str[(*j)++];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	*longest_word(const char *words)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (words[i])
	{
		if ((words[i] && words[i] != ' ')
			&& ((str && ft_strclen(str) <= ft_strclen(words + i)) || !str))
		{
			free(str);
			str = get_str(words, &i);
		}
		else if (words[i])
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
