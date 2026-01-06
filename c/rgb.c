/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:29:44 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 16:46:41 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	rgb(int r, int g, int b, char hex[6 + 1])
{
	int colours[3] = {r, g, b};

	for (int i = 0; i < 3; i++)
	{
		if (colours[i] > 255)
			colours[i] = 255;
		else if (colours[i] < 0)
			colours[i] = 0;
	}
	sprintf(hex, "%02X%02X%02X", colours[0], colours[1], colours[2]);
}

#include <string.h>

int main(void)
{
	char res[6];

	rgb(0, 0, 0, res);
	if (!strcmp(res, "000000"))
		printf("1st test passed\n");
	else
		return (printf("1st test failed, res = %s, expected = 000000\n", res));

	rgb(1, 2, 3, res);
	if (!strcmp(res, "010203"))
		printf("2nd test passed\n");
	else
		return (printf("2nd test failed, res = %s, expected = 010203\n", res));

	rgb(255, 255, 255, res);
	if (!strcmp(res, "FFFFFF"))
		printf("3rd test passed\n");
	else
		return (printf("3rd test failed, res = %s, expected = FFFFFF\n", res));

	rgb(254, 253, 252, res);
	if (!strcmp(res, "FEFDFC"))
		printf("4th test passed\n");
	else
		return (printf("4th test failed, res = %s, expected = FEFDFC\n", res));

	rgb(-20, 275, 125, res);
	if (!strcmp(res, "00FF7D"))
		printf("5th test passed\n");
	else
		return (printf("5th test failed, res = %s, expected = 00FF7D\n", res));
}
