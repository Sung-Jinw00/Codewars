/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knight.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 01:26:25 by marvin            #+#    #+#             */
/*   Updated: 2025/04/24 01:26:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <limits.h>

short moves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

short recursive_srch(short alpha, short nb, short goal_alpha, short goal_nb, short depth)
{
	if (alpha < 0 || alpha >= 8 || nb < 0 || nb >= 8 || depth > 6)
		return (SHRT_MAX);
	if (alpha == goal_alpha && nb == goal_nb)
		return (0);
	short min_path = SHRT_MAX;
	for (short i = 0; i < 8; i++)
	{
		short new_alpha = alpha + moves[i][0];
		short new_nb = nb + moves[i][1];
		short res = recursive_srch(new_alpha, new_nb, goal_alpha, goal_nb, depth + 1);
		if (res != SHRT_MAX)
			min_path = min_path < (res + 1) ? min_path : (res + 1);
	}
	return (min_path);
}

short knight(const char *p1, const char *p2)
{
	short x = p1[0] - 'a', y = p1[1] - '1', final_x = p2[0] - 'a', final_y = p2[1] - '1';
	if (!strcmp(p1, p2)
		|| x < 0 || x > 7 || y < 0 || y > 7
		|| final_x < 0 || final_x > 7 || final_y < 0 || final_y > 7)
		return (0);
	short answer = recursive_srch(x, y, final_x, final_y, 0);
	return (answer != SHRT_MAX) ? answer : 0;
}

#include <stdio.h>

int	main(void)
{
	short answer = knight("a1", "c1");
	printf("%d\n", answer);
	return (0);
}