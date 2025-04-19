/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:59:33 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 14:31:03 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned long long	times_10_cal(unsigned long long result)
{
	unsigned long long n = 10;

	if (result == 0)
		return (1);
	while(result >= 10)
	{
		result /= 10;
		n *= 10;
	}
	return (n);
}

unsigned long long square_digits(unsigned n)
{
	unsigned digit = 0, times_10 = 0;
	unsigned long long result = 0;

	while (n > 0)
	{
		digit = n % 10;
		if (digit == 0)
			times_10++;
		else
			digit *= digit;
		if (times_10 != 0 && digit != 0)
		{
			while (times_10-- > 0)
				digit *= 10;
			result += digit * times_10_cal(result);
			times_10 = 0;
		}
		else
			result += digit * times_10_cal(result);
		n /= 10;
	}
	return (result);
}

#include <limits.h>

int main(void)
{
	unsigned long long result, cmp;
	
	result = square_digits(3212);
	if (result == 9414)
		printf("1st test was a success\n");
	else
		return (printf("1st test failed, expected : 9414, got : %llu\n", result));
	result = square_digits(2112);
	if (result == 4114)
		printf("2nd test was a success\n");
	else
		return (printf("2nd test failed expected : 4114, got : %llu\n", result));
	result = square_digits(0);
	if (result == 0)
		printf("3rd test was a success\n");
	else
		return (printf("3rd test failed, expected : 0, got : %llu\n", result));
	result = square_digits(999);
	if (result == 818181)
		printf("4th test was a success\n");
	else
		return (printf("4th test failed, expected : 818181, got : %llu\n", result));
	
	result = square_digits(10001);
	if (result == 10001)
		printf("5th test was a success\n");
	else
		return (printf("5th test failed, expected : 10001, got : %llu\n", result));
	result = square_digits(3210987654);
	if (result == 9410816449362516)
		printf("6th test was a success\n");
	else
		return (printf("6th test failed, expected : 9410816449362516, got : %llu\n", result));
	result = square_digits(399999999);
	cmp = 98181818181818181;
	if (result == cmp)
		printf("7th test was a success\n");
	else
		return (printf("7th test failed, expected : 9818181818181818181, got : %llu\n", result));
	result = square_digits(UINT_MAX);
	cmp = 164811681364948125;
	if (result == cmp)
		return (printf("8th and last test was a success\n"));
	else
		return (printf("8th test failed expected : 164811681364948125, got : %llu\n", result));
}
