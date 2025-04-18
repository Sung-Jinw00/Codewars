/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:33:59 by marvin            #+#    #+#             */
/*   Updated: 2025/04/15 23:33:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	sort_array(char **array, int len_array)
{
	char	*tmp;
	int i = 0, j = 0;

	for (i = 0; i < len_array && array[i]; i++)
	{
		for (j = i + 1; j < len_array && array[j]; j++)
		{
			if (strlen(array[i]) < strlen(array[j])
				|| (strlen(array[i]) == strlen(array[j]) && strcmp(array[i], array[j]) > 0))
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

char	*strjoin_n_free(char *s1, char *s2, int tab_to_free)
{
	char	*new_string;
	size_t	i;
	size_t	j;

	new_string = malloc(strlen(s1) + strlen(s2) + 1);
	if (!new_string)
		return (NULL);
	i = -1;
	while (s1 && s1[++i] != '\0')
		new_string[i] = s1[i];
	j = 0;
	while (s2 && s2[j] != '\0')
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	if (tab_to_free == 1)
		return (free(s1), new_string);
	return (new_string);
}

char	*write_alpha(char const *s1, char c, int rep_c)
{
	char	*new_string;
	size_t	i;

	new_string = malloc(strlen(s1) + rep_c + 1);
	if (!new_string)
		return (NULL);
	for(i = 0; s1[i]; i++)
		new_string[i] = s1[i];
	while (rep_c-- > 0)
		new_string[i++] = c;
	new_string[i] = '\0';
	return (new_string);
}

void	free_array(char **array)
{
	int i = 0;

	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

char *mix(const char *s1, const char *s2)
{
	char lowalpha[27] = {0}, *answer = NULL;
	char c = 'a';
	int *alpha_s1 = calloc(sizeof(int), 27);
	int *alpha_s2 = calloc(sizeof(int), 27);
	char **alpha_array = NULL;
	int i, j = 0, nb_alpha = 0;
	size_t k, len_s1 = strlen(s1), len_s2 = strlen(s2);

	for (k = 0; k < len_s1 ; k++)
		if (s1[k] >= 'a' && s1[k] <= 'z')
			alpha_s1[s1[k] - 'a']++;
	for (k = 0; k < len_s2 ; k++)
		if (s2[k] >= 'a' && s2[k] <= 'z')
			alpha_s2[s2[k] - 'a']++;
	for (k = 0; (k < 26) ; k++)
	{
		lowalpha[k] = c++;
		if (alpha_s1[k] >= 2 || alpha_s2[k] >= 2)
			nb_alpha++;
	}
	alpha_array = calloc(sizeof(char *), (nb_alpha + 1));
	for (i = 0; i < 26; i++)
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
	alpha_array[j] = NULL;
	free(alpha_s1);
	free(alpha_s2);
	sort_array(alpha_array, nb_alpha + 1);
	if (!alpha_array[0])
		return (free_array(alpha_array), strjoin_n_free("", "", 0));
	answer = strjoin_n_free(alpha_array[0], "", 0);
	for (i = 0; alpha_array[i + 1]; i++)
	{
		char *tmp = strjoin_n_free(answer, "/", 1);
		answer = strjoin_n_free(tmp, alpha_array[i + 1], 1);
	}
	free_array(alpha_array);
	return (answer);
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
