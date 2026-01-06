/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbyear.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:02:26 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 15:08:44 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int nbYear(int p0, double percent, int aug, int p)
{
	int i;

	for (i = 0; p0 < p; i++)
		p0 = p0 + p0 * (percent / 100) + aug;
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
		printf("1st test passed\n");
	else
		return (printf("1st test failed\n"));
	result = nbYear(1500000, 0.25, 1000, 2000000);
	if (result == 94)
		printf("1st test passed\n");
	else
		return (printf("1st test failed\n"));
}
