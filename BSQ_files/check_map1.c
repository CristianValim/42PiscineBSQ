/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:19:21 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/09 22:30:56 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1

static int	open_file_safe(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	return ((fd == -1) ? -1 : fd);
}

char	*read_file(char *file_name, t_map *map, int *total_bytes)
{
	int		file_descriptor;
	char	*buffer;

	file_descriptor = open_file_safe(file_name);
	if (file_descriptor == -1)
		return (NULL);
	buffer = read_file_content(file_descriptor, total_bytes);
	close(file_descriptor);
	if (!buffer || !check_lines(buffer, map))
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

static char	*read_file_content(int fd, int *total_bytes)
{
	char	*buffer;
	int		count;
	int		bytes_read;

	buffer = allocate_buffer(0);
	if (!buffer)
		return (NULL);
	count = 0;
	while (1)
	{
		bytes_read = read(fd, buffer + count, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		count += bytes_read;
		buffer = expand_buffer(buffer, count);
	}
	buffer[count] = '\0';
	*total_bytes = count;
	return (buffer);
}

int	allocate_map_data(t_map *map)
{
	map->data = malloc((map->total_lines + 1) * sizeof(char *));
	return (map->data != NULL);
}

int	fill_map_data(char *map_start, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	if (!allocate_map_data(map)) // Call allocate_map_data here
		return (0);
	line = ft_tiktok(map_start, 10);
	while (i < map->total_lines && line)
	{
		map->data[i] = ft_strdup(line);
		if (!map->data[i])
		{
			while (i > 0)
				free(map->data[--i]);
			free(map->data);
			return (0);
		}
		line = ft_tiktok(NULL, 10);
		i++;
	}
	map->data[i] = NULL; // Make sure to NULL terminate the array
	return (1);
}

int	main(void)
{
	int		fd;
	int		total_bytes;
	t_map	map; // Remove duplicate declaration
	char	*buffer;

	fd = open("map", O_RDONLY);
	if (fd < 0)
	{
		print_map_error();
		return (1);
	}

	// Initialize map
	map = (t_map){0}; // Use aggregate initialization

	buffer = read_file("map", &map, &total_bytes);
	if (!buffer)
	{
		print_map_error();
		cleanup(&map, buffer, fd);
		return (0);
	}
	if (!check_header(map.header, &map))
	{
		cleanup(&map, buffer, fd);
		return (1);
	}
	if (!check_map(&map))
	{
		cleanup(&map, buffer, fd);
		return (1);
	}
	if (!check_length(&map))
	{
		cleanup(&map, buffer, fd);
		return (1);
	}
	cleanup(&map, buffer, fd);
	return (0);
}
