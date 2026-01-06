/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:06:26 by marvin            #+#    #+#             */
/*   Updated: 2025/04/16 15:06:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
