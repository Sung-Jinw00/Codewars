/**
 * @brief Calculate the number of years required for a population to reach a target.
 *
 * This function computes the number of full years required for a town's population
 * to reach or exceed a desired population `p`, given an initial population `p0`,
 * a yearly growth rate `percent`, and a fixed number of inhabitants coming or leaving `aug`.
 *
 * @param p0 Initial population.
 * @param percent Percentage increase per year (e.g., 2.5 for 2.5%).
 * @param aug Net number of inhabitants added (or removed if negative) each year.
 * @param p Target population.
 *
 * @return 
 * Number of full years needed for the population to reach or exceed `p`.
 *
 * @example
 * int years = nbYear(1500, 5, 100, 5000);
 * printf("%d\n", years); // prints 15
 */
int nbYear(int p0, double percent, int aug, int p)
{
	int i;

	for (i = 0; p0 < p; i++)
		p0 += p0 * (percent / 100) + aug;
    return (i);
}

#include <stdio.h>

int main(void)
{
	int result;
	result = nbYear(1500, 5, 100, 5000);
	if (result == 15)
		printf("1st test passed\n");
	else
		return (printf("1st test failed\n"));
    result = nbYear(1500000, 2.5, 10000, 2000000);
	if (result == 10)
		printf("2nd test passed\n");
	else
		return (printf("1st test failed\n"));
	result = nbYear(1500000, 0.25, 1000, 2000000);
	if (result == 94)
		printf("3rd test passed\n");
	else
		return (printf("1st test failed\n"));
}
