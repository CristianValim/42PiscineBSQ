/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:33:25 by fpedroso          #+#    #+#             */
/*   Updated: 2024/10/09 23:03:10 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"

// Find the biggest available square in the given map.
void	find_max_square(char **map)
{
	int				square_size;
	t_square_info	max_square;
	int				found_space;

	square_size = 1;
	max_square.x = -1;
	max_square.y = -1;
	max_square.size = 0;
	while (1)
	{
		found_space = 0;
		check_all_squares(map, square_size, &max_square, &found_space);
		if (found_space)
			square_size++;
		else
			break ;
	}
	if (max_square.size > 0)
		mark_square(map, max_square);
}

void	check_all_squares(char **map, int square_size,
		t_square_info *max_square, int *found_space)
{
	int	coord_x;
	int	coord_y;

	coord_x = 0;
	*found_space = 0;
	while (coord_x <= ROWS - square_size)
	{
		coord_y = 0;
		while (coord_y <= COLS - square_size)
		{
			if (check_fit_square(map, coord_x, coord_y, square_size))
			{
				*found_space = 1;
				update_max_square_info(coord_x, coord_y, square_size,
					max_square);
			}
			coord_y++;
		}
		coord_x++;
	}
}

int	check_fit_square(char **map, int coord_x, int coord_y,
		int square_size)
{
	int	i;
	int	j;

	i = 0;
	if (coord_x + square_size <= ROWS && coord_y + square_size <= COLS)
	{
		while (i < square_size)
		{
			j = 0;
			while (j < square_size)
			{
				if (map[coord_x + i][coord_y + j] != CHAR_EMPTY)
				{
					return (0);
				}
				j++;
			}
			i++;
		}
		return (1);
	}
	return (0);
}

// Mark the square on the map by changing empty characters to full.
void	mark_square(char **map, t_square_info square)
{
	int	i;
	int	j;

	i = 0;
	while (i < square.size)
	{
		j = 0;
		while (j < square.size)
		{
			map[square.x + i][square.y + j] = CHAR_FULL;
			j++;
		}
		i++;
	}
}

// Update the maximum square information if a larger square is found.
void	update_max_square_info(int coord_x, int coord_y, int square_size,
		t_square_info *max_square)
{
	if (square_size > max_square->size)
	{
		max_square->size = square_size;
		max_square->x = coord_x;
		max_square->y = coord_y;
	}
}
