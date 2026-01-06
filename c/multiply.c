/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:24:43 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/04 21:19:14 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	reajust(char *str, int k)
{
	int i = 0;

	if (str[k] < '0')
		k++;
	while (k <= 3000)
		str[i++] = str[k++];
	while (str[--k] != 0)
		str[k] = 0;
}

void	add(char *str, int *k, int result)
{
	if (str[*k] < '0')
		str[*k] += '0';
	str[*k] += result % 10;
	while (str[*k] > '9')
	{
		str[*k] = '0' + (str[*k] - '9');
		str[*k - 1]++;
	}
	(*k)--;
}
//    52436 (b)
//  *   144 (a)
//  -------
//  7550784 (str)

char *multiply(const char *a, const char *b)
{
	char str[3001] = {0};
	int len_a = strlen(a) - 1, len_b = strlen(b) - 1, max = 3000, i = len_a, j = len_b, k = max, result = 0, expand_k = k;

	while (j >= 0)
	{
		while (i >= 0)
		{
			result = (a[i] - '0') * (b[j] - '0');//je prends la multiplication de mes nombres
			add(str, &k, result % 10);//j'ajoute le nombre et je passe a la dizaine suivante
			expand_k = k;
			while (result >= 10)//si le nombre est toujours plus grand que 10, je l'ajoute avec une variable temporaire
			{
				result /= 10;
				add(str, &expand_k, result % 10);
			}
			i--;//j'ajoute jusqu'a la fin de a
		}
		j--;
		k = --max;
		i = len_a;
	}
	reajust(str, k);
	return (strdup(str));
}

#include <stdio.h>

int	main(void)
{
	char *str = multiply("144", "52436");
	printf("%s\n", str);
	free(str);
	return (0);
}
