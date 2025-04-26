/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roman_numerals_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:53:42 by marvin            #+#    #+#             */
/*   Updated: 2025/04/26 15:10:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

const char			symbols[][3] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
const unsigned int	values[]     = {1000, 900,  500, 400,  100,  90,  50,   40,  10,   9,    5,   4,    1 };

unsigned  from_roman(const char *roman)
{
	unsigned int answer = 0; int i = 0;

	while (*roman)
	{
		if (strstr(roman, symbols[i]) == roman)
		{
			answer += values[i];
			roman += strlen(symbols[i]);		
		}
		else
			i++;
	}
	return (answer);
}
void to_roman(unsigned number, char *roman)
{
	int i = 0; *roman = 0;

	while (number)
	{
		while (number >= values[i])
		{
			roman += sprintf(roman, "%s", symbols[i]);
			number -= values[i];
		}
		i++;
	}
}

#include <stdio.h>

int main(void)
{
	char *test_symbols[8] = {"MMMCMXCIX", "MM", "MDCLXVI", "M", "CD", "XC", "XL", "I"};
	unsigned int test_values[8] = {3999, 2000, 1666, 1000, 400, 90, 40, 1};
	char s_answer[50];
	unsigned int v_answer;

	for (int i = 0; i < 8; i++)
	{
		to_roman(test_values[i], s_answer);
		v_answer = from_roman(test_symbols[i]);

		printf("Test %d :\n", i);
		if (!strcmp(test_symbols[i], s_answer))
			printf("no diff, %s (test_symbols[%d]) == %s (s_answer), congrats !\n", test_symbols[i], i, s_answer);
		else
			printf("diff !\n%s (test_symbols[%d]) != %s (s_answer)\n", test_symbols[i], i, s_answer);
		printf("\n");
		if (v_answer == test_values[i])
			printf("no diff, %u (test_values[%d]) == %u (v_answer), congrats !\n", test_values[i], i, v_answer);
		else
			printf("diff !\n%u (test_values[%d]) != %u (v_answer)\n", test_values[i], i, v_answer);
		if (i != 12)
			printf("\n\n\n");
	}
}
