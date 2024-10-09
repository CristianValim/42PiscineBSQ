/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:37:07 by fpedroso          #+#    #+#             */
/*   Updated: 2024/10/09 23:21:54 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"

int	validate_map_structure(t_map *map)
{
	if (map->total_lines != map->max_lines)
	{
		print_map_error();
		return (0);
	}
	return (1);
}

int	validate_map_characters(t_map *map)
{
	int	i;
	int	line_length;
	int	j;

	i = 0;
	while (i < map->total_lines)
	{
		line_length = ft_strlen(map->data[i]);
		if (line_length == 0)
			return (0);
		j = 0;
		while (j < line_length)
		{
			if (map->data[i][j] != map->chars.empty
				&& map->data[i][j] != map->chars.obstacle
				&& map->data[i][j] != map->chars.full)
			{
				print_map_error();
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map(t_map *map)
{
	if (!validate_map_structure(map))
		return (0);
	if (!validate_map_characters(map))
		return (0);
	return (1);
}

void	cleanup(t_map *map, char *buffer, int file_descriptor)
{
	int	i;

	free(map->header);
	i = 0;
	while (i < map->total_lines)
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
	free(buffer);
	close(file_descriptor);
}
