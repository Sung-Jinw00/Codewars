/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   human_readable_time.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:16:16 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 18:27:33 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char *human_readable_time(unsigned seconds, char *time_string)
{
	sprintf(time_string, "%02d:%02d:%02d", seconds / 3600, seconds / 60 % 60, seconds % 60);
	return time_string;
}

int main(void)
{
	char time[9] = {0};
	
	human_readable_time(1, time);
	return (printf("%s\n", time));
}