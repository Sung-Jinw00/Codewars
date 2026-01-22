#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Helper to format a single unit of time (year, day, hour, minute, second).
 * 
 * This function writes a formatted string into the provided buffer according to
 * the value of `calc`. It automatically pluralizes the time unit.
 * 
 * @param calc The quantity of the time unit.
 * @param str Output buffer (must be at least 500 chars).
 * @param time Name of the time unit (e.g., "second", "minute").
 */
void	write_str(int calc, char *str, char *time)
{
	if (calc == 0) return ;
	snprintf(str, 500, (calc == 1) ? "%d %s" : "%d %ss", calc, time);
}

/**
 * @brief Convert a duration in seconds to a human-readable string.
 * 
 * This function converts an integer number of seconds into a human-readable
 * English string describing the duration in years, days, hours, minutes, and
 * seconds. It handles singular/plural forms and inserts commas and "and"
 * according to English grammar rules.
 * 
 * Examples:
 * 
 * - 0 → "now"
 * 
 * - 1 → "1 second"
 * 
 * - 62 → "1 minute and 2 seconds"
 * 
 * - 3662 → "1 hour, 1 minute and 2 seconds"
 * 
 * @param n Duration in seconds (non-negative).
 * 
 * @return A newly allocated string containing the formatted duration. 
 * The caller is responsible for freeing this memory using `free()`.
 */
char *formatDuration(int n)
{
	if (n == 0) return (strdup("now"));
	char str[5][100] = {0};
	char answer[500] = {0}, *coma = ", ", *and = " and ";
	int count = 0;

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
			if (answer[0] && --count != 1)
				strcat(answer, coma);
			else if (answer[0])
				strcat(answer, and);
			strcat(answer, str[i]);
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
