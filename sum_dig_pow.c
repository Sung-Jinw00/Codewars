/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_dig_pow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:22:21 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 20:37:10 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  don't allocate memory for the results array
//  assign values to the provided results array
//  set length pointer as size of results array
//  after calculations return the results array

#include <stddef.h>
#include <limits.h>
#include <math.h>

typedef unsigned long long ull;

ull	pow_sum(ull cur_nb)
{
	ull cpy = cur_nb, powr = 1, res = 0;

	while (cpy >= 10)
	{
		cpy /= 10;
		powr++;
	}
	cpy = cur_nb;
	while (cur_nb >= 10)
	{
		if (cpy >= 10)
			cpy %= 10;
		res += pow(cpy, powr--);
		cur_nb /= 10;
		cpy = cur_nb;
	}
	res += cur_nb;
	return (res);
}

ull *sum_dig_pow(ull a, ull b, ull *results, size_t *length)
{
    ull cur_nb = a, i = 1, sum = 0;
	int count = 0;

	while (cur_nb <= b)
	{
		if (cur_nb < 10)
			results[count++] = cur_nb;
		else
		{
			sum = pow_sum(cur_nb);
			if (sum == cur_nb)
				results[count++] = cur_nb;
			i = 1;
			sum = 0;
		}
		cur_nb++;
	}
	*length = count;
    return (results);
}

#include <stdio.h>

int main(void)
{
	ull a = 0, b = 100, results[500] = {0};
	size_t length = 0, i = 0;
	sum_dig_pow(a, b, results, &length);
	printf("%zu\n", length);
	while (i < length)
	{
		printf("%llu", results[i]);
		if (i + 1 < length)
			printf(", ");
		i++;
	}
	printf("\n");
	return (0);
}