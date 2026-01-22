#include "utils.h"

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * @param array Array of strings to free.
 */
void	free_label_storages(char **array)
{
	for (int i = 0; array && array[i]; i++)
		free(array[i]);
}

/**
 * @brief Frees a double pointer array of strings and sets it to NULL.
 *
 * @param array Pointer to the array of strings.
 */
void	free_array(char ***array)
{
	if (!array || !*array)
		return ;
	for (int i = 0; *array && (*array)[i]; i++)
	{
		printf("tab that is freed : %s\n", (*array)[i]);
		free((*array)[i]);
	}
	free(*array);
	*array = NULL;
}

/**
 * @brief Skips leading whitespace in a string.
 *
 * @param str The string to scan.
 * @return Index of the first non-whitespace character.
 */
int	skip_wspaces(char *str)
{
	int i = 0;

	while (str && isspace(str[i]))
		i++;
	return (i);
}

/**
 * @brief Returns the length of a string up to a specific cut character.
 *
 * @param program Input string.
 * @param cut Character to stop at.
 * @return Number of characters until cut or null terminator.
 */
int	strclen(char *program, char cut)
{
	int i = 0;
	while (program && program[i] && program[i] != cut)
		i++;
	return (i);
}

/**
 * @brief Counts the number of words separated by a delimiter up to a limit.
 *
 * @param program Input string.
 * @param cut Delimiter character.
 * @param limit Maximum number of characters to scan.
 * @return Number of words found.
 */
int	count_words(char *program, char cut, int limit)
{
	if (!program)
		return (0);
	int trigger = 0, count = 0;

	for (int i = 0; i < limit && program[i]; i++)
	{
		if (program[i] && program[i] == cut && trigger)
			trigger = 0;
		while (i < limit && program[i] == cut)
			i++;
		i += skip_wspaces(program + i);
		if (i < limit && program[i] && program[i] != cut && !trigger)
			(trigger = 1, count++);
	}
	return (count);
}

/**
 * @brief Splits a string by a delimiter into an array of strings.
 *
 * @param program Input string (will be freed inside).
 * @param cut Delimiter character.
 * @param limit Maximum number of characters to scan.
 * @return Array of strings (NULL-terminated), or NULL if no words.
 */
char	**split(char *program, char cut, int limit)
{
	if (!program || !program[0])
		return (free(program), NULL);
	int len_word = 0, trigger = 0;

	int count = count_words(program, cut, limit);
	if (!count)
		return (free(program), NULL);
	char **arr = calloc(sizeof(char *), count + 1);
	if (!arr)
		return (free(program), NULL);
	int j = 0;
	for (int i = 0; i < limit && program[i]; i++)
	{
		i += skip_wspaces(program + i);
		if (strclen(program + i, ';') < strclen(program + i, cut))
			len_word = strclen(program + i, ';'), trigger = 1;
		else
			len_word = strclen(program + i, cut);
		if (program[i] && len_word)
		{
			arr[j++] = strndup(program + i, len_word);
			i += len_word;
		}
		if (i < limit && trigger)
			trigger = 0, i += strclen(program + i, cut);
	}
	arr[count] = NULL;
	return (free(program), arr);
}

/**
 * @brief Removes whitespace from all strings in an array.
 *
 * @param array Array of strings.
 * @return Array of strings without leading spaces (same pointer).
 */
char **remove_wspaces(char **array)
{
	if (!array)
		return (NULL);
	for (int i = 0; array[i]; i++)
	{
		int j = 0, k = j;
		while (isspace(array[i][k]))
			k++;
		while (array[i][k])
			array[i][j++] = array[i][k++];
		while (j < k)
			array[i][j++] = 0;
	}
	return (array);
}

/* count the strings in an array */
int	count_tabs(char **arr)
{
	int i = 0;

	while (arr && arr[i])
		i++;
	return (i);
}
