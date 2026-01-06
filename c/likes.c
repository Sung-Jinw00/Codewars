/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   likes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:51:56 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/27 20:01:39 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	init_vals(long nb, int *sign)
{
	int	i;
	int	digits;

	i = 0;
	digits = 1;
	if (nb < 0)
	{
		nb = -nb;
		*sign = 1;
	}
	while (nb >= 10)
	{
		nb /= 10;
		digits++;
	}
	i = digits + *sign;
	return (i);
}

char	*itoa(int n)
{
	char	*cpy;
	long	nb;
	int		i;
	int		sign;

	nb = n;
	sign = 0;
	i = init_vals(nb, &sign);
	if (nb < 0)
		nb = -nb;
	cpy = malloc(sizeof(char) * i + 1);
	if (!cpy)
		return (NULL);
	if (sign == 1)
		cpy[0] = '-';
	cpy[i--] = '\0';
	while (i >= sign)
	{
		cpy[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (cpy);
}

char	*strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	len;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	len = strlen(s1) + strlen(s2) + 1;
	new_string = malloc(len);
	if (!new_string)
		return (NULL);
	while (s1[++i] != '\0')
		new_string[i] = s1[i];
	while (s2[j] != '\0')
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	return (new_string);
}

char	*strjoin_n_free(char *s1, const char *s2)
{
	char	*newstring;

	newstring = strjoin(s1, s2);
	free(s1);
	return (newstring);
}

char	*likes(size_t n, const char *const names[n])
{
	char	*str;

	str = NULL;
	if (n == 0)
		return (strdup("no one likes this"));
	else if (n == 1)
		return (strjoin(names[0], " likes this"));
	else if (n == 2)
	{
		str = strjoin(names[0], " and ");
		str = strjoin_n_free(str, names[1]);
		return (strjoin_n_free(str, " like this"));
	}
	else if (n == 3)
	{
		str = strjoin(names[0], ", ");
		str = strjoin_n_free(str, names[1]);
		str = strjoin_n_free(str, " and ");
		str = strjoin_n_free(str, names[2]);
		return (strjoin_n_free(str, " like this"));
	}
	else
	{
		str = strjoin(names[0], ", ");
		str = strjoin_n_free(str, names[1]);
		str = strjoin_n_free(str, " and ");
		str = strjoin_n_free(str, itoa(n - 2));
		return (strjoin_n_free(str, " others like this"));
	}
}

int	main(int ac, char **av)
{
	char	*str;

	str = likes(ac - 1, (const char *const *)av + 1);
	printf("%s\n", str);
	free(str);
	return (0);
}
