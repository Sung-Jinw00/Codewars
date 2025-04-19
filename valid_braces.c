/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_braces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:12:18 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 17:56:43 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool closed_quotes(const char *braces, int i, int j)
{
	return ((braces[i] == '(' && braces[j] == ')')
		|| (braces[i] == '[' && braces[j] == ']')
		|| (braces[i] == '{' && braces[j] == '}'));
}

void	shorten_str(char *str, int i, int j)
{
	int len = (int)strlen(str);
	i++;
	while (str[j] && j < len)
		str[i++] = str[j++];
	while (i < j)
		str[i++] = 0;
}

bool valid_braces(const char *braces)
{
	int i = 0, j = 0;
	char *str = strdup(braces);

	while (str[i])
	{
		if (closed_quotes(str, i, i + 1))
		{
			j = i + 1;
			while (closed_quotes(str, i, j) && i >= 0 && j < (int)strlen(str))
			{
				i--;
				j++;
			}
			shorten_str(str, i, j);
			i = -1;
		}
		i++;
	}
	if (str[0])
		return (free(str), false);
	return (free(str), true);
}

#include <stdio.h>

int main(void)
{
	bool res = valid_braces("(((");
	if (res == false)
		printf("1st test passed !\n");
	else
		return (printf("1st test failed, expected false, got %s\n", res ? "true" : "false"));
	res = valid_braces(")))");
	if (res == false)
		printf("2nd test passed !\n");
	else
		return (printf("2nd test failed, expected false, got %s\n", res ? "true" : "false"));
	res = valid_braces("(){}[]");
	if (res == true)
		printf("3rd test passed !\n");
	else
		return (printf("3rd test failed, expected true, got %s\n", res ? "true" : "false"));
	res = valid_braces("([{}])");
	if (res == true)
		printf("4th test passed !\n");
	else
		return (printf("4th test failed, expected true, got %s\n", res ? "true" : "false"));
	res = valid_braces("(}");
	if (res == false)
		printf("5th test passed !\n");
	else
		return (printf("5th test failed, expected false, got %s\n", res ? "true" : "false"));
	res = valid_braces("[(])");
	if (res == false)
		printf("6th test passed !\n");
	else
		return (printf("6th test failed, expected false, got %s\n", res ? "true" : "false"));
	res = valid_braces("[({})](]");
	if (res == false)
		printf("7th test passed !\n");
	else
		return (printf("7th test failed, expected false, got %s\n", res ? "true" : "false"));
	res = valid_braces("[(){[]}{{()}}]");
	if (res == true)
		printf("8th test passed !\n");
	else
		return (printf("8th test failed, expected true, got %s\n", res ? "true" : "false"));
}
