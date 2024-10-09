/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:35:08 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/09 23:23:32 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"
#include <fcntl.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*buffer;
	t_map	map;

	int total_bytes; // Declare total_bytes to hold the number of bytes read
	if (argc < 2)
	{
		print_map_error(); // Error message if no file is provided
		return (1);
	}
	fd = open(argv[1], O_RDONLY); // Open the file specified as an argument
	if (fd < 0)
	{
		print_map_error(); // Error handling for failed file open
		return (1);
	}
	map = (t_map){0};                                // Initialize map structure
	buffer = read_file(argv[1], &map, &total_bytes); // Pass total_bytes address
	if (!buffer || !check_header(map.header, &map) || !check_length(&map))
	{
		print_map_error();         // Handle any errors related to the map
		cleanup(&map, buffer, fd); // Clean up allocated memory
		return (1);
	}
	find_max_square(map.data); // Process the map to find the largest square
	print_map(map.data);       // Print the result
	ft_putchar('\n');
	cleanup(&map, buffer, fd); // Clean up before exiting
	return (0);
}
