/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:03:08 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/09 20:25:22 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*check_lines(char *buffer, char **header, char ***map, int *total_lines)
{
	char	*newline;
	char	*map_start;
	char	*buffer_copy;
	char	*line;

	newline = ft_strchr(buffer, '\n');
	if (newline)
	{
		*header = ft_strndup(buffer, newline - buffer);
		map_start = newline + 1;
		buffer_copy = ft_strdup(map_start);
		if (!buffer_copy)
		{
			return (NULL);
		}
		line = ft_tiktok(buffer_copy, 10);
		*total_lines = 0;
		while (line != NULL)
		{
			(*total_lines)++;
			line = ft_tiktok(NULL, 10);
		}
		*map = malloc((*total_lines) * sizeof(char *));
		if (*map == NULL)
		{
			free(buffer_copy);
			return (NULL);
		}
		line = ft_tiktok(map_start, 10);
		for (int i = 0; i < *total_lines; i++)
		{
			if (line)
			{
				(*map)[i] = ft_strdup(line);
				if ((*map)[i] == NULL)
				{
					for (int j = 0; j < i; j++)
					{
						free((*map)[j]);
					}
					free(*map);
					free(buffer_copy);
					return (NULL);
				}
				line = ft_tiktok(NULL, 10);
			}
		}
		free(buffer_copy);
		return (buffer);
	}
	return (NULL);
}

char	*read_file(char *file_name, char **header, char ***map,
		int *total_lines, int *total_bytes)
{
	int		file_descriptor;
	char	temp;
	char	*buffer;
	int		bytes_read;
	char	*result;

	file_descriptor = open(file_name, O_RDONLY);
	if (file_descriptor == -1)
		return (NULL);
	*total_bytes = 0;
	while (read(file_descriptor, &temp, 1) > 0)
	{
		(*total_bytes)++;
	}
	if (*total_bytes == 0)
	{
		close(file_descriptor);
		return (NULL);
	}
	close(file_descriptor);
	file_descriptor = open(file_name, O_RDONLY);
	if (file_descriptor == -1)
	{
		return (NULL);
	}
	buffer = malloc(*total_bytes + 1);
	if (buffer == NULL)
	{
		close(file_descriptor);
		return (NULL);
	}
	bytes_read = read(file_descriptor, buffer, *total_bytes);
	if (bytes_read != *total_bytes)
	{
		free(buffer);
		close(file_descriptor);
		return (NULL);
	}
	buffer[*total_bytes] = '\0';
	close(file_descriptor);
	result = check_lines(buffer, header, map, total_lines);
	if (result == NULL)
		free(buffer);
	else
		printf("[read_file] Arquivo processado com sucesso.\n");
	return (result);
}

int	check_header(char *header, int *max_lines, char *empty, char *obstacle,
		char *full)
{
	char	*line_count_str;
	int		i;

	if (header == NULL || ft_strlen(header) < 4)
		return (0);
	*empty = header[ft_strlen(header) - 3];
	*obstacle = header[ft_strlen(header) - 2];
	*full = header[ft_strlen(header) - 1];
	line_count_str = ft_strndup(header, ft_strlen(header) - 3);
	i = 0;
	while (line_count_str[i] != '\0')
	{
		if (!(line_count_str[i] >= '0' && line_count_str[i] <= '9'))
		{
			free(line_count_str);
			return (0);
		}
		i++;
	}
	*max_lines = atoi(line_count_str);
	free(line_count_str);
	if (*empty == *obstacle || *empty == *full || *obstacle == *full)
		return (0);
	return (1);
}
int	check_map(char **map, int total_lines, int max_lines, char empty,
		char obstacle, char full)
{
	int		line_length;
	char	current_char;

	if (total_lines != max_lines)
	{
		return (0);
	}
	for (int i = 0; i < total_lines; i++)
	{
		line_length = ft_strlen(map[i]);
		if (line_length == 0)
			return (0);
		for (int j = 0; j < line_length; j++)
		{
			current_char = map[i][j];
			if (current_char != empty && current_char != obstacle
				&& current_char != full)
				return (0);
		}
	}
	return (1);
}

int	check_length(char **map, int total_lines)
{
	int	first_line_length;

	if (total_lines == 0)
	{
		return (1);
	}
	first_line_length = ft_strlen(map[0]);
	for (int i = 0; i < total_lines; i++)
	{
		if (ft_strlen(map[i]) != first_line_length)
		{
			return (0);
		}
	}
	return (1);
}

int	main(void)
{
	int		fd;
	char	*header;
	int		total_lines;
	char	*buffer;
	int		max_lines;
	char	*file_name;
	char	**map;
	int		total_bytes;

	file_name = "map3";
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	header = NULL;
	map = NULL;
	total_lines = 0;
	total_bytes = 0;
	buffer = read_file(file_name, &header, &map, &total_lines, &total_bytes);
	if (buffer)
	{
		char empty, obstacle, full;
		if (check_header(header, &max_lines, &empty, &obstacle, &full))
		{
			if (check_map(map, total_lines, max_lines, empty, obstacle, full))
			{
				if (check_length(map, total_lines))
				{
					printf("[main] Mapa valido.\n");
				}
				else
				{
					printf("[main] Mapa inválido: linhas de comprimentos diferentes.\n");
				}
			}
			else
			{
				printf("[main] Mapa inválido.\n");
			}
		}
		else
		{
			printf("[main] Cabeçalho inválido.\n");
		}
	}
	else
	{
		printf("[main] Erro ao ler o arquivo ou arquivo vazio.\n");
	}
	free(header);
	for (int i = 0; i < total_lines; i++)
	{
		free(map[i]);
	}
	free(map);
	free(buffer);
	close(fd);
	printf("[main] Execução finalizada.\n");
	return (0);
}
