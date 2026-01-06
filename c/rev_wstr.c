/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:33:18 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/26 17:48:52 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnstr(char *str, int start, int end)
{
	while (start <= end)
		write(1, &str[start++], 1);
}

int main(int ac, char **av)
{
	int start;
	int end;
	
	if (ac == 2)
	{
		start = ft_strlen(av[1]) - 1;
		while (start >= 0)
		{
			while (av[1][start] == ' ' || av[1][start] == '\t')
				start--;
			end = start;
			while (start - 1 >= 0 && (av[1][start - 1] != ' ' && av[1][start - 1] != '\t'))
				start--;
			if (start >= 0)
				ft_putnstr(av[1], start, end);
			write(1, " ", 1);
			start--;
		}
	}
	write(1, "\n", 1);
	return (0);
}
