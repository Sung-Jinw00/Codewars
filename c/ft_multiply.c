/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:27:09 by marvin            #+#    #+#             */
/*   Updated: 2025/04/13 15:27:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int	verifications(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	len_s1;
	int	len_s2;

	i = 0;
	j = 0;
	if (s1[i] == '-')
		i++;
	if (s2[j] == '-')
		j++;
	len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	while (s1[i] || s2[j])
		if ((i < len_s1 && !isdigit(s1[i++]))
			|| (j < len_s2 && !isdigit(s2[j++])))
			return (0);
	return (1);
}

static int	calculation(char *result, const char *s1, const char *s2)
{
	int	i_s1;
	int	i_s2;
	int	i_result;
	int	start_result;

	i_s1 = strlen(s1) - 1;
	start_result = 500;
	while (i_s1 >= 0 && s1[i_s1] != '-')
	{
		i_s2 = strlen(s2) - 1;
		i_result = start_result--;
		while (i_s2 >= 0 && s2[i_s2] != '-')
		{
			result[i_result] += (s1[i_s1] - '0') * (s2[i_s2--] - '0');
			while (result[i_result] >= 10)
			{
				result[i_result] -= 10;
				result[i_result - 1]++;
			}
			i_result--;
		}
		i_s1--;
	}
	return (i_result);
}

/**
 * @brief
 * Multiply 2 numbers in a string format, return the value of the 2 numbers in
 * a string, the values of s1 and s2 can be greater than a long long.
 * 
 * Requirements :*/
/**
 * - The only sign tolerated is one and only '-' sign if the number is
 * negative.*/
/**
 * - Besides this sign, if the string is not composed of numbers exclusively,
 * the function will return NULL.
 * 
 * @return
 * - NULL if one of the strings is NULL or empty, or if the requirements aren't
 * fulfilled.*/
/**
 * - The multiplication of the 2 numbers in a memory allocated string.
 * 
 * @note
 * The memory released of the string returned by the function is the
 * responsibility of the user.
*/
char	*ft_multiply(const char *s1, const char *s2)
{
	static char	result[501] = {0};
	int			start_result;
	int			i_result;

	if (!s1 || !s1[0] || !s2 || !s2[0] || !verifications(s1, s2))
		return (NULL);
	i_result = calculation(result, s1, s2) + 1;
	while (result[i_result - 1] != 0 || result[i_result - 2] != 0
		|| result[i_result - 3] != 0)
		i_result--;
	start_result = -1;
	if ((s1[0] == '-' && s2[0] != '-') || (s1[0] != '-' && s2[0] == '-'))
		result[++start_result] = '-';
	while (i_result < 501)
		result[++start_result] = '0' + result[i_result++];
	result[++start_result] = 0;
	return (strdup(result));
}

/* #include <unistd.h>

int main(int ac, char **av)
{
	if (ac != 3)
		return (0);

	char *str = ft_multiply(av[1], av[2]);
	write(1, str, strlen(str));
	write(1, "\n", 1);
	if (!strcmp(str, "1449557665776209901793684752"))
		return(free(str), write(1, "ok\n", 3));
	return(free(str), write(1, "naze\n", 5));
} */
