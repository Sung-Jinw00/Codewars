#include <string.h>

typedef struct s_dico
{
	char	*word;
	int		number;
}	t_dico;

t_dico dictionnary[] = {
	{"eight",		8},
	{"eighteen",	18},
	{"eighty",		80},
	{"eleven",		11},
	{"fifteen",		15},
	{"fifty",		50},
	{"five",		5},
	{"forty",		40},
	{"four",		4},
	{"fourteen",	14},
	{"hundred",		100},//multiply
	{"million",		1000000},//multiply and get out
	{"nine",		9},
	{"nineteen",	19},
	{"ninety",		90},
	{"one",			1},
	{"seven",		7},
	{"seventeen",	17},
	{"seventy",		70},
	{"six",			6},
	{"sixteen",		16},
	{"sixty",		60},
	{"thirteen",	13},
	{"thirty",		30},
	{"thousand",	1000},//multiply and get out
	{"three",		3},
	{"ten",			10},
	{"twelve",		12},
	{"twenty",		20},
	{"two",			2},
};

/**
 * @brief Convert a number written in English words into its integer value.
 *
 * This function parses a string containing a number in English words (like
 * "one thousand three hundred and thirty-seven") and returns its numeric
 * representation as a `long`.
 *
 * The function supports numbers up to "million" and handles "hundred",
 * "thousand", "million", and the word "and" as used in English numbering.
 *
 * @param number A null-terminated string representing a number in English words.
 * 
 *               For example: "one thousand two hundred and thirty-four".
 * 
 *               The string "zero" can also be represented by starting with 'z'.
 *
 * @return
 * The numeric value of the string as a `long`. Returns 0 if the input string
 * represents "zero" or is empty.
 *
 * @note
 * 
 * - Supports only lowercase words separated by spaces or hyphens.
 * 
 * - The dictionary used is limited to numbers from one to ninety, multiples
 *   of ten, hundred, thousand, and million.
 * 
 * - The user is responsible for providing a properly formatted string.
 *
 * @example
 * long n = parse_int("one thousand three hundred and thirty-seven");
 * printf("%ld\n", n); // prints 1337
 */
long	parse_int(const char* number)
{
	long answer = 0, tmp, i = 0;

	if (*number == 'z')
		return (0);
	while (*number)
	{
		tmp = 0;
		while (1)
		{
			for (i = 0; i < 30 ; i++)
				if (*number == dictionnary[i].word[0])
					break;
			for (long j = 0; *number && *number != ' ' && *number != '-' && dictionnary[i].word; j++)
			{
				while (dictionnary[i].word && (*number != dictionnary[i].word[j] || !dictionnary[i].word[j]))
					i++;
				number++;
			}
			if (!strncmp(number, " and ", 5))
				number += 5;
			else if (*number == ' ' || *number == '-')
				number++;
			if (i == 11 || i == 24)//thousand or million
			{
				tmp *= dictionnary[i].number;
				break ;
			}
			else if (i == 10)//hundred
				tmp *= dictionnary[i].number;
			else
				tmp += dictionnary[i].number;
			if (!*number)
				break ;
		}
		answer += tmp;
	}
	return (answer);
}

#include <stdio.h>

int main(void)
{
	const char *tests[3] = {"one thousand three hundred and thirty-seven", "six hundred sixty-six thousand six hundred sixty-six", "two hundred and forty-six"};
	long	expected[3] = {1337, 666666, 246};
	long	answer;

	for (int i = 0; i < 3; i++)
	{
		answer = parse_int(tests[i]);
		if (answer == expected[i])
			printf("no diff, %lu (expected[%d]) == %lu (answer), congrats !\n", expected[i], i, answer);
		else
			printf("diff !\n%lu (expected[%d]) != %lu (answer)\n", expected[i], i, answer);
		if (i != 2)
			printf("\n\n\n");
	}
}
