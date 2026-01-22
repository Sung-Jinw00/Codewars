#include <unistd.h>

/**
 * @brief Calculate the length of a null-terminated string.
 *
 * @param str Pointer to the string.
 * 
 * @return Length of the string (number of characters before '\0').
 */
int ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief Write a substring of str from start to end (inclusive) to stdout.
 *
 * @param str Pointer to the string.
 * @param start Starting index of the substring (inclusive).
 * @param end Ending index of the substring (inclusive).
 */
void	ft_putnstr(char *str, int start, int end)
{
	while (start <= end)
		write(1, &str[start++], 1);
}

/**
 * @brief Main function: reverse the words of the input string.
 *
 * If exactly one argument is provided, it prints its words in reverse order.
 * Words are separated by spaces or tabs. Multiple spaces/tabs are ignored.
 * The output is followed by a newline.
 *
 * @param ac Argument count.
 * @param av Argument vector (array of strings).
 * 
 * @return 0
 */
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
