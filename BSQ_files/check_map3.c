/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:42 by fpedroso          #+#    #+#             */
/*   Updated: 2024/10/09 23:19:29 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"

int	process_map(char *map_start, t_map *map)
{
	if (!allocate_map_data(map))
		return (0);
	return (fill_map_data(map_start, map));
}

char	*allocate_buffer(int size)
{
	char	*buffer;

	buffer = malloc(size + 1);
	if (buffer)
		buffer[0] = '\0';
	return (buffer);
}

char	*expand_buffer(char *buffer, int new_size)
{
	char	*new_buffer;
	int		i;

	new_buffer = allocate_buffer(new_size);
	if (new_buffer)
	{
		i = 0;
		while (i < new_size)
		{
			new_buffer[i] = buffer[i];
			i++;
		}
		free(buffer);
	}
	return (new_buffer);
}
