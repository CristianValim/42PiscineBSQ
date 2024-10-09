/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:34:07 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/09 22:56:54 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"

char	*process_header(char *buffer, t_map *map)
{
	char	*newline;
	char	*map_start;
	char	*buffer_copy;
	char	*line;

	newline = ft_strchr(buffer, '\n');
	if (newline)
	{
		map->header = ft_strndup(buffer, newline - buffer);
		map_start = newline + 1;
		buffer_copy = ft_strdup(map_start);
		if (!buffer_copy)
			return (NULL);
		line = ft_tiktok(buffer_copy, 10);
		map->total_lines = 0;
		while (line)
		{
			(map->total_lines)++;
			line = ft_tiktok(NULL, 10);
		}
		free(buffer_copy);
		return (map_start);
	}
	return (NULL);
}

int	check_header(char *header, t_map *map)
{
	char	*line_count_str;

	if (!header || ft_strlen(header) < 4)
		return (0);
	map->chars.empty = header[ft_strlen(header) - 3];
	map->chars.obstacle = header[ft_strlen(header) - 2];
	map->chars.full = header[ft_strlen(header) - 1];
	line_count_str = ft_strndup(header, ft_strlen(header) - 3);
	if (!validate_line_count(line_count_str))
	{
		free(line_count_str);
		return (0);
	}
	map->max_lines = atoi(line_count_str);
	free(line_count_str);
	return (map->chars.empty != map->chars.obstacle
		&& map->chars.empty != map->chars.full
		&& map->chars.obstacle != map->chars.full);
}

int	validate_line_count(char *line_count_str)
{
	int	i;

	i = 0;
	while (line_count_str[i])
	{
		if (!(line_count_str[i] >= '0' && line_count_str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_length(t_map *map)
{
	int	first_line_length;
	int	i;

	if (map->total_lines == 0)
		return (1);
	first_line_length = ft_strlen(map->data[0]);
	i = 0;
	while (i < map->total_lines)
	{
		if (ft_strlen(map->data[i]) != first_line_length)
			return (0);
		i++;
	}
	return (1);
}

int	check_lines(char *buffer, t_map *map)
{
	char	*map_start;

	map_start = process_header(buffer, map);
	if (!map_start)
	{
		free(map->header);
		return (0);
	}
	if (!process_map(map_start, map))
	{
		free(map->header);
		return (0);
	}
	return (1);
}
