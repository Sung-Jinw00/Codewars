/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   The_observed_pin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:42:31 by marvin            #+#    #+#             */
/*   Updated: 2025/04/26 21:28:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <math.h>
#include <string.h>

char *possibilities[] = {
	(char []){"08"},	//0
	(char []){"124"},	//1
	(char []){"1235"},	//2
	(char []){"236"},	//3
	(char []){"1457"},	//4
	(char []){"24568"},	//5
	(char []){"3569"},	//6
	(char []){"478"},	//7
	(char []){"57890"},	//8
	(char []){"689"},	//9
};

void	get_all_last_digits(char **array, int *i, int j, const char* observed)
{
	int nb = observed[j] - '0', a = 0, trigger = 0;

	while (possibilities[nb][a])
	{
		array[*i][j] = possibilities[nb][a++];
		if (j > 0 && trigger)
			for (int k = j - 1; k >= 0; k--)
				array[*i][k] = array[*i - 1][k];
		else if (j > 0)
			trigger = 1;
		if (array[0][j + 1])
			get_all_last_digits(array, i, j + 1, observed);
		(*i)++;
	}
	if (j > 0)
		(*i)--;
}

const char** get_pins(const char* observed, size_t* count)
{
	int len_tabs = (int)pow(5, strlen(observed)) + 1;

	char **array = malloc(sizeof(char *) * (len_tabs));
	for (int i = 0; i < len_tabs - 1; i++)
		array[i] = strdup(observed);
	array[len_tabs - 1] = NULL;

	int i = 0;
	get_all_last_digits(array, &i, 0, observed);
	*count = i;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
    return ((const char **)array);
}

void free_pins(const char ** pins)
{
	if (!pins)
		return;

	for(int i = 0; pins[i] ; i++)
		free((void *)pins[i]);
	free((void *)pins);
}

#include <stdio.h>

void	print_array(const char **array)
{
	if (!array)
	{
		printf("array == (null)\n");
		return ;
	}
	size_t i = 0;
	while (array[i])
		printf("array[%zu] == %s\n", i, array[i]), i++;
	printf("array[%zu] == (null)\n", i);
}

int main(void)
{
	size_t count;
	const char* observed = "33";

	const char **possibilities = get_pins(observed, &count);
	print_array(possibilities);
	printf("len = %zu\n", count);
	free_pins(possibilities);
	return (0);
}
