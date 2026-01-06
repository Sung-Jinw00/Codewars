/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatDuration.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:31:47 by marvin            #+#    #+#             */
/*   Updated: 2025/04/16 15:31:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	write_str(int calc, char *str, char *time)
{
	if (calc == 0)
		return ;
	else if (calc == 1)
		snprintf(str, 500, "1 %s", time);
	else
		snprintf(str, 500, "%d %ss", calc, time);
}

char *formatDuration(int n)
{
	if (n == 0) return (strdup("now"));
	char str[5][100] = {0};
	char answer[500] = {0}, *coma = ", ", *and = " and ";
	int k = 0, count = 0;

	write_str(n % 60, str[4], "second");
	write_str((n / 60) % 60, str[3], "minute");
	write_str((n / 60 / 60) % 24, str[2], "hour");
	write_str((n / 60 / 60 / 24) % 365, str[1], "day");
	write_str(n / 60 / 60 / 24 / 365, str[0], "year");
	for(int i = 0; i < 5 ; i++)
		if (str[i][0]) count++;
	for(int i = 0; i < 5 ; i++)
	{
		if (str[i][0])
		{
			if (k && --count != 1)
				for (int j = 0; coma[j]; j++)
					answer[k++] = coma[j];
			else if (k)
				for (int j = 0; and[j]; j++)
					answer[k++] = and[j];
			for (int j = 0; str[i][j]; j++)
				answer[k++] = str[i][j];
		}
	}
  return (strdup(answer));
}

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

int main(void)
{
	char *expected[] = {
		"now",                     // 0 seconds
		"1 second",                // 1 second
		"1 minute",                // 60 seconds
		"1 minute and 1 second",   // 61 seconds
		"1 hour",                  // 3600 seconds
		"1 hour and 30 minutes",   // 5400 seconds
		"2 days",                  // 172800 seconds
		"1 year",                  // 31536000 seconds (1 year)
		"1 year and 12 hours",     // 31579200 seconds (1 year and 12 hours)
		"2 years, 3 days and 4 hours", // 63172800 seconds (2 years, 3 days and 4 hours)
		"3 years and 1 day",          // 94694400 seconds (3 years, 1 day)
		"1 year, 1 day and 2 hours", // 31579200 seconds (1 year, 1 day and 2 hours)
		"1 year and 5 hours",         // 31560000 seconds (1 year, 5 hours)
		"1 year and 10 hours",        // 31596000 seconds (1 year, 10 hours)
		"2 years",                 // 63172800 seconds (2 years)
		"3 years",                 // 94694400 seconds (3 years)
		0x0
	}, *answer;
	
	int s = 1, m = 60, h = 3600, d = 172800 / 2, y = d * 365;
	int time[] = {
		0,	// now
		s,	// 1 second
		m,	// 1 minute
		m + s,	// 1 minute and 1 second
		h,	// 1 hour
		h + (m *30),	// 1 hour and 30 minutes
		d * 2,	// 2 days
		y,	// 1 year
		y + (h * 12),	// 1 year and 12 hours
		(y * 2) + (d * 3) + (4 * h),	// 2 years, 3 days and 4 hours
		(y * 3) + d,	// 3 years, 1 day
		y + d + (h * 2),	// 1 year, 1 day and 2 hours
		y + (5 * h),	// 1 year, 5 hours
		y + (h * 10),	// 1 year, 10 hours
		2 * y,	// 2 years
		3 * y,	// 3 years
	}; 		

	for (int i = 0; expected[i]; i++)
	{
		answer = formatDuration(time[i]);
		printf(UNDERLINE BOLD"\n\nTest %d :\n"RESET"answer = %s\n", i + 1, answer);
		if (strcmp(answer, expected[i]))
			printf("\ndifference !\nexpected = %s\n", expected[i]);
		else
			printf("\nno diff, congrats !\n");
	}
	return (0);
}
