/**
 * @brief Calculates the score based on the count of each die value.
 *
 * Given an array representing the number of dice showing each value (1-6),
 * computes the total score according to the game rules:
 * 
 * - Three 1s → 1000 points
 * 
 * - Each additional 1 → 100 points
 * 
 * - Three 6s → 600 points
 * 
 * - Three 5s → 500 points
 * 
 * - Each additional 5 → 50 points
 * 
 * - Three 4s → 400 points
 * 
 * - Three 3s → 300 points
 * 
 * - Three 2s → 200 points
 *
 * @param nb_amount Array of 6 integers, where nb_amount[i] is the number
 *                  of dice showing the value i+1.
 * 
 * @return Total score for the given counts.
 */
int	get_score(int *nb_amount)
{
	int score = 0;

	if (nb_amount[0] >= 3)
		(score += 1000, nb_amount[0] -= 3);
	if (nb_amount[0] >= 1)
		score += 100 * nb_amount[0];
	if (nb_amount[5] >= 3)
		score += 600;
	if (nb_amount[4] >= 3)
		(score += 500, nb_amount[4] -= 3);
	if (nb_amount[4] >= 1)
		score += 50  * nb_amount[4];
	if (nb_amount[3] >= 3)
		score += 400;
	if (nb_amount[2] >= 3)
		score += 300;
	if (nb_amount[1] >= 3)
		score += 200;
	return (score);
}

/**
 * @brief Computes the score of a dice roll.
 *
 * Counts how many times each value appears in a 5-dice roll and
 * calculates the total score using get_score().
 *
 * @param dice Array of 5 integers representing the dice roll (values 1-6).
 * 
 * @return The total score of the roll.
 */
int score(const int dice[5])
{
	int	nb_amount[6] = {0};

	for (int i = 0; i < 5; i++)
		nb_amount[dice[i] - 1]++;
    return (get_score(nb_amount));
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
	const int *rolls[3] = {
		(const int[]){2, 3, 4, 6, 2},
		(const int[]){4, 4, 4, 3, 3},
		(const int[]){2, 4, 4, 5, 4}
	};
	int scores[] = {0, 400, 450}, answer;

	for (int i = 0; i < 3; i++)
	{
		answer = score(rolls[i]);
		printf(UNDERLINE BOLD"\n\nTest %d :\n"RESET"answer = %d\n", i + 1, answer);
		if (answer != scores[i])
			printf("\ndifference !\nexpected = %d\n", scores[i]);
		else
			printf("\nno diff, congrats !\n");
	}
	return (0);
}
