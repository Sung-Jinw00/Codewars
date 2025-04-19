/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isValidWalk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:07:56 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 18:13:00 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>

bool isValidWalk(const char *walk)
{
	int x = 0, y = 0;
	
	if (strlen(walk) != 10)
		return false;
	for(int i = 0; walk[i]; i++)
	{
		if (walk[i] == 'n')
			x++;
		else if (walk[i] == 's')
			x--;
		else if (walk[i] == 'e')
			y++;
		else if (walk[i] == 'w')
			y--;
	}
   	return (!x && !y);
}