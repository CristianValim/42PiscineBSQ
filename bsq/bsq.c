/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:37:31 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/09 23:37:55 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"

static int	process_file(char *filename)
{
	int		fd;
	char	*buffer;
	int		total_bytes;
	t_map	map;

	map = (t_map){0};
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_map_error();
		return (1);
	}
	buffer = read_file(filename, &map, &total_bytes);
	if (!buffer || !check_header(map.header, &map) || !check_length(&map))
	{
		cleanup(&map, buffer, fd);
		return (1);
	}
	find_max_square(map.data);
	print_map(map.data);
	ft_putchar('\n');
	cleanup(&map, buffer, fd);
	return (0);
}

int	main(int argc, char **argv)
{
	int	overall_status;
	int	i;

	if (argc < 2)
	{
		print_map_error();
		return (1);
	}
	overall_status = 0;
	i = 1;
	while (i < argc)
	{
		overall_status |= process_file(argv[i]);
		i++;
	}
	return (overall_status);
}
