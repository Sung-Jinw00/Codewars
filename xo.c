/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xo.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:31:12 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/29 19:36:07 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	xo(const char *s)
{
	int x = 0, o = 0;

	for(;*s; s++)
	{
		if (*s == 'o' || *s == 'O') 
			o++;
		else if (*s == 'x' || *s == 'X')
			x++;
	}
	return (o == x);
}
