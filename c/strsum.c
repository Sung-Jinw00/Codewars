/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:23:34 by marvin            #+#    #+#             */
/*   Updated: 2025/04/24 00:23:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char *strsum(const char *a, const char *b)
{
	char result[5000] = {0};

	result[0] = '0';
	if (strlen(a) < strlen(b))
		strcpy(result + 1, b);
	else
		strcpy(result + 1, a);
	int mv_a = (int)strlen(a) - 1, mv_b = (int)strlen(b) - 1;

	if (strlen(a) < strlen(b))
	{
		mv_b++;
		while (mv_a >= 0)
		{
			result[mv_b] += a[mv_a--] - '0';
			if (result[mv_b] > '9')
			{
				result[mv_b - 1]++;
				result[mv_b] = '0' + (result[mv_b] - '9') - 1;
			}
			mv_b--;
		}
		while (result[mv_b] > '9')
		{
			result[mv_b - 1]++;
			result[mv_b] = '0' + (result[mv_b] - '9') - 1;
			mv_b--;
		}
	}
	else
	{
		mv_a++;
		while (mv_b >= 0)
		{
			result[mv_a] += b[mv_b--] - '0';
			if (result[mv_a] > '9')
			{
				result[mv_a - 1]++;
				result[mv_a] = '0' + (result[mv_a] - '9') - 1;
			}
			mv_a--;
		}
		while (result[mv_a] > '9')
		{
			result[mv_a - 1]++;
			result[mv_a] = '0' + (result[mv_a] - '9') - 1;
			mv_a--;
		}
	}
	int i = 0;
	while (result[i] == '0' && result[i + 1])
		i++;
    return (strdup(result + i));
}

/* 
display result
display result[mv_a]
display b[mv_b]

display result[mv_b]
display a[mv_a]
*/

#include <stdio.h>

# ifndef RESET
#  define RESET				"\033[0m"
# endif

/* Bold text */
# ifndef BOLD
#  define BOLD				"\033[1m"
# endif

/* Underlined text */
# ifndef UNDERLINE
#  define UNDERLINE			"\033[4m"
# endif

int	main(void)
{
	const char	*n1[] = {"8797" , "45"},
				*n2[] = {"888189237043806503776892181697274027222461671780811697504605487123392661858934101352711528950816076349591444652925104" , "305780284821673411716163398653520095034330612305352489820822905565270559229293949613554992962714888712921245840600292"};
	const char **numbers[] = {n1, n2};
	char *expected[] = {"8842", "1193969521865479915493055580350794122256792284086164187325428392688663221088228050966266521913530965062512690493525396"};
	for (int i = 0; i < 2; i++)
	{
		char *answer = strsum(numbers[i][0], numbers[i][1]);
		printf(UNDERLINE BOLD"\n\nTest %d :\n"RESET"answer = %s\n", i + 1, answer);
		if (strcmp(answer, expected[i]))
			printf("\ndifference !\nexpected = %s\n", expected[i]);
		else
			printf("\nno diff, congrats !\n");
		free(answer);
	}
}
