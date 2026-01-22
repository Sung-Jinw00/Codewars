#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <math.h>
#include <string.h>

char *possibilities[] = {
	(char []){"08"},	//0
	(char []){"124"},	//1
	(char []){"1235"},	//2
	(char []){"236"},	//3
	(char []){"1457"},	//4
	(char []){"24568"},	//5
	(char []){"3569"},	//6
	(char []){"478"},	//7
	(char []){"57890"},	//8
	(char []){"689"},	//9
};

/**
 * @brief Recursively fills an array with all possible PIN variations for a given observed digit.
 *
 * - Uses the `possibilities` table to determine possible adjacent digits.
 * 
 * - Fills the array by trying all possibilities for the current digit and recursively for the next digits.
 *
 * @param array Array of strings to store the generated PINs.
 * @param i Pointer to the current index in the array.
 * @param j Current position in the observed PIN.
 * @param observed The observed PIN as a string.
 */
void	get_all_last_digits(char **array, int *i, int j, const char* observed)
{
	int nb = observed[j] - '0', a = 0, trigger = 0;

	while (possibilities[nb][a])
	{
		array[*i][j] = possibilities[nb][a++];
		if (j > 0 && trigger)
			for (int k = j - 1; k >= 0; k--)
				array[*i][k] = array[*i - 1][k];
		else if (j > 0)
			trigger = 1;
		if (array[0][j + 1])
			get_all_last_digits(array, i, j + 1, observed);
		(*i)++;
	}
	if (j > 0)
		(*i)--;
}

/**
 * @brief Generates all possible PINs from an observed PIN considering adjacent digits.
 *
 * - Allocates an array of strings containing all PIN variations.
 * 
 * - Calls `get_all_last_digits` to fill the array.
 *
 * @param observed The observed PIN as a string.
 * @param count Pointer to a size_t variable that will hold the number of PIN variations.
 * 
 * @return A newly allocated array of strings containing all possible PINs.
 *         The caller must free it using `free_pins`.
 */
const char** get_pins(const char* observed, size_t* count)
{
	int len_tabs = (int)pow(5, strlen(observed)) + 1;

	char **array = malloc(sizeof(char *) * (len_tabs));
	for (int i = 0; i < len_tabs - 1; i++)
		array[i] = strdup(observed);
	array[len_tabs - 1] = NULL;

	int i = 0;
	get_all_last_digits(array, &i, 0, observed);
	*count = i;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
    return ((const char **)array);
}

/**
 * @brief Frees the memory allocated for an array of PIN strings.
 *
 * - Frees each string in the array.
 * 
 * - Frees the array itself.
 *
 * @param pins The array of PIN strings to free.
 */
void free_pins(const char ** pins)
{
	if (!pins)
		return;

	for(int i = 0; pins[i] ; i++)
		free((void *)pins[i]);
	free((void *)pins);
}

#include <stdio.h>

void	print_array(const char **array)
{
	if (!array)
	{
		printf("array == (null)\n");
		return ;
	}
	size_t i = 0;
	while (array[i])
		printf("array[%zu] == %s\n", i, array[i]), i++;
	printf("array[%zu] == (null)\n", i);
}

int main(void)
{
	size_t count;
	const char* observed = "33";

	const char **possibilities = get_pins(observed, &count);
	print_array(possibilities);
	printf("len = %zu\n", count);
	free_pins(possibilities);
	return (0);
}
