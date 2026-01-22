#include <stdio.h>

/**
 * @brief Convert a duration in seconds into a human-readable time string.
 *
 * This function formats a duration given in seconds into the form
 * "HH:MM:SS" and stores the result in the provided buffer.
 *
 * @param seconds Duration in seconds.
 * @param time_string Buffer that will receive the formatted time string.
 * 
 * It must be large enough to hold at least 9 characters (null terminator included).
 *
 * @note The supported time range is limited to 99 hours, 99 minutes, and 99 seconds.
 *
 * @return A pointer to `time_string`.
 */
char *human_readable_time(unsigned seconds, char *time_string)
{
	sprintf(time_string, "%02d:%02d:%02d", seconds / 3600, seconds / 60 % 60, seconds % 60);
	return time_string;
}

int main(void)
{
	char time[9] = {0};
	
	human_readable_time(1, time);
	return (printf("%s\n", time));
}