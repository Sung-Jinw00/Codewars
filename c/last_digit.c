/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_digit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:52:19 by marvin            #+#    #+#             */
/*   Updated: 2025/04/16 10:52:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <string.h>

int last_digit(const char *a, const char *b)
{
    if (*b == '0')
		return (1);
    if (*a == '0')
		return (0);
    
	size_t	len_b = strlen(b);
    // take last digit of a
    int x = a[strlen(a) - 1] - '0';
    // take last digit of b
    int y = (b[len_b - 1] - '0');
	// take before-last digit of b
    if (len_b > 1)
		y += (b[len_b - 2] - '0') * 10;
    y = y % 4 + 4;  
    return ((int)pow(x, y) % 10);
}

#include <stdio.h>

int main(void)
{
	char *d1 = "0";
	char *d2 = "1";
	int expected = 1;
	int answer = last_digit(d1, d2);

	printf("answer = %d\n", answer);
	if (answer != expected)
		printf("\ndifference !\nexpected = %d\n", expected);
	else
		printf("\nno diff, congrats !\n");
	return (0);
}