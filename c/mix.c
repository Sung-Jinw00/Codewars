#include <stdlib.h>
#include <string.h>

/**
 * @brief Sort an array of strings by length (descending), then alphabetically.
 *
 * @param array Array of strings to sort. Must be NULL-terminated.
 * @param len_array Number of elements in the array.
 */
void	sort_array(char **array, int len_array)
{
	char	*tmp;
	int i = 0, j = 0;

	for (i = 0; i < len_array && array[i]; i++)
	{
		for (j = i + 1; j < len_array && array[j]; j++)
		{
			size_t len_i = strlen(array[i]), len_j = strlen(array[j]);
			if (len_i < len_j || (len_i == len_j && strcmp(array[i], array[j]) > 0))
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

/**
 * @brief Join two strings into a new dynamically allocated string, optionally freeing the first string.
 *
 * @param s1 First string (may be freed if tab_to_free is 1).
 * @param s2 Second string (not freed).
 * @param tab_to_free 1 to free s1 after joining, 0 to keep it.
 *
 * @return
 * Newly allocated string containing s1 followed by s2. User is responsible for freeing it.
 */
char	*strjoin_n_free(char *s1, char *s2, int tab_to_free)
{
	char	*new_string = malloc(strlen(s1) + strlen(s2) + 1);
	size_t	i, j;

	if (!new_string)
		return (NULL);
	for (i = 0; s1 && s1[i] != '\0'; i++)
		new_string[i] = s1[i];
	for (j = 0; s2 && s2[j] != '\0'; i++, j++)
		new_string[i] = s2[j];
	new_string[i] = '\0';
	if (tab_to_free == 1)
		free(s1);
	return (new_string);
}

/**
 * @brief Write a character multiple times after a prefix string.
 *
 * @param s1 Prefix string.
 * @param c Character to repeat.
 * @param rep_c Number of repetitions.
 *
 * @return
 * Newly allocated string with s1 followed by c repeated rep_c times. User is responsible for freeing it.
 */
char	*write_alpha(char const *s1, char c, int rep_c)
{
	char	*new_string = malloc(strlen(s1) + rep_c + 1);
	size_t	i;

	if (!new_string)
		return (NULL);
	for(i = 0; s1[i]; i++)
		new_string[i] = s1[i];
	while (rep_c-- > 0)
		new_string[i++] = c;
	new_string[i] = '\0';
	return (new_string);
}

/**
 * @brief Free all strings in a NULL-terminated array and then the array itself.
 *
 * @param array Array of strings to free.
 */
void	free_array(char **array)
{
	for (int i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

/**
 * @brief Mix two strings by comparing lowercase letter frequencies.
 *
 * Letters occurring more than once in either string are included with a prefix indicating
 * the string with the highest count ('1:', '2:' or '=:'). Letters are then sorted by length
 * and alphabetically, and joined with '/'.
 *
 * @param s1 First input string.
 * @param s2 Second input string.
 *
 * @return
 * Dynamically allocated string with the mixed result. User is responsible for freeing it.
 */
char *mix(const char *s1, const char *s2)
{
	char lowalpha[27] = {0}, *answer = NULL, c = 'a';
	int *alpha_s1 = calloc(sizeof(int), 27), *alpha_s2 = calloc(sizeof(int), 27), nb_alpha = 0;
	size_t len_s1 = strlen(s1), len_s2 = strlen(s2);

	if (!alpha_s1 || !alpha_s2)
		return (free(alpha_s1), free(alpha_s2), calloc(1, 1));
	for (size_t i = 0; i < len_s1 && i < len_s2 ; i++)
	{
		if (i < len_s1 && s1[i] >= 'a' && s1[i] <= 'z')
			alpha_s1[s1[i] - 'a']++;
		if (i < len_s2 && s2[i] >= 'a' && s2[i] <= 'z')
			alpha_s2[s2[i] - 'a']++;
	}
	for (size_t i = 0; (i < 26) ; i++)
	{
		lowalpha[i] = c++;
		if (alpha_s1[i] >= 2 || alpha_s2[i] >= 2)
			nb_alpha++;
	}
	char **alpha_array = calloc(sizeof(char *), (nb_alpha + 1));
	if (!alpha_array)
		return (free(alpha_s1), free(alpha_s2), calloc(1, 1));
	for (size_t i = 0, j = 0; i < 26; i++)
	{
		if (alpha_s1[i] > 1 || alpha_s2[i] > 1)
		{
			if (alpha_s1[i] > alpha_s2[i])
				alpha_array[j++] = write_alpha("1:", lowalpha[i], alpha_s1[i]);
			else if (alpha_s1[i] == alpha_s2[i])
				alpha_array[j++] = write_alpha("=:", lowalpha[i], alpha_s1[i]);
			else if (alpha_s1[i] < alpha_s2[i])
				alpha_array[j++] = write_alpha("2:", lowalpha[i], alpha_s2[i]);
		}
	}
	alpha_array[nb_alpha] = NULL;
	free(alpha_s1);
	free(alpha_s2);
	sort_array(alpha_array, nb_alpha + 1);
	if (!alpha_array[0])
		return (free_array(alpha_array), calloc(1, 1));
	answer = strjoin_n_free(alpha_array[0], "", 0);
	for (size_t i = 0; alpha_array[i + 1]; i++)
		answer = strjoin_n_free(strjoin_n_free(answer, "/", 1), alpha_array[i + 1], 1);
	return (free_array(alpha_array), answer);
}

#include <stdio.h>

int main(void)
{
	char *s1 = "looping is fun but dangerous";
	char *s2 = "less dangerous than coding";
	char *correct = "1:ooo/1:uuu/2:sss/=:nnn/1:ii/2:aa/2:dd/2:ee/=:gg";
	char *answer = mix(s1, s2);
	printf ("answer = %s\n\n", answer);
	if (strcmp(answer, correct))
		printf ("difference !\nexpect = %s\n", correct);
	else
		printf ("same, congrats !\n");
	free(answer);
	return (0);
}
