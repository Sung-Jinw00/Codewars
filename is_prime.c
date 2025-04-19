/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_prime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:47:50 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 17:03:03 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>

bool is_prime(int num)
{
	if (num < 2)
		return false;
	if (num == 2 || num == 3)
        return true;
    if (num % 2 == 0 || num % 3 == 0)
        return false;
	for (int i = 5; i <= sqrt(num); i += 6)
	{
		if (num % i == 0 || num % (i + 2) == 0)
			return false;
	}
    return true;
}

#include <stdio.h>

int main(void)
{
	bool res = is_prime(75);
	return (printf("%d", res));
}