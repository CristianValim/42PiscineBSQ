/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:03:05 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/08 17:37:23 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"

#define ROWS 10
#define COLS 10
#define CHAR_EMPTY '.'
#define CHAR_FULL 'X'

void	find_max_square(char map[ROWS][COLS]);
void	check_all_squares(char map[ROWS][COLS], int square_size,
			int *max_coord_x, int *max_coord_y, int *biggest_size,
			int *found_space);
int		check_fit_square(char map[ROWS][COLS], int coord_x, int coord_y,
			int square_size);
void	mark_square(char map[ROWS][COLS], int coord_x, int coord_y,
			int square_size);
void	print_map(char mapa[ROWS][COLS]);

int	main(void)
{
	char map[ROWS][COLS] = {
		{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', 'o', '.', '.', '.', '.', '.', '.', 'o', '.'},
		{'.', '.', '.', '.', '.', '.', 'o', '.', '.', '.'},
		{'.', '.', '.', '.', '.', '.', '.', '.', 'o', '.'},
		{'.', 'o', '.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', '.', '.', '.', '.', '.', '.', 'o', '.', '.'},
		{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', '.', 'o', '.', '.', '.', '.', '.', 'o', '.'},
		{'.', 'o', '.', '.', '.', '.', '.', '.', '.', '.'},
		{'.', '.', '.', 'o', '.', '.', '.', '.', '.', '.'},
	};
	find_max_square(map);
	print_map(map);
	ft_putchar('\n');
	return (0);
}

// Find the biggest available square in the given map.
void	find_max_square(char map[ROWS][COLS])
{
	int	square_size;
	int	max_coord_x;
	int	max_coord_y;
	int	biggest_size;
	int	found_space;

	square_size = 1;
	max_coord_x = -1;
	max_coord_y = -1;
	biggest_size = 0;
	while (1)
	{
		found_space = 0;
		check_all_squares(map, square_size, &max_coord_x, &max_coord_y,
			&biggest_size, &found_space);
		if (found_space)
			square_size++;
		else
			break ;
	}
	if (biggest_size > 0)
		mark_square(map, max_coord_x, max_coord_y, biggest_size);
}

// Verify all possible spaces for a square of size `square_size` at each coordinate.
void	check_all_squares(char map[ROWS][COLS], int square_size,
		int *max_coord_x, int *max_coord_y, int *biggest_size, int *found_space)
{
	int	coord_x;
	int	coord_y;

	coord_x = 0;
	coord_y = 0;
	*found_space = 0;
	while (coord_x <= ROWS - square_size)
	{
		coord_y = 0;
		while (coord_y <= COLS - square_size)
		{
			if (check_fit_square(map, coord_x, coord_y, square_size))
			{
				*found_space = 1;
				if (square_size > *biggest_size)
				{
					*biggest_size = square_size;
					*max_coord_x = coord_x;
					*max_coord_y = coord_y;
				}
			}
			coord_y++;
		}
		coord_x++;
	}
}

// Check if a square of size `square_size` fits inside the specified coordinates.
int	check_fit_square(char map[ROWS][COLS], int coord_x, int coord_y,
		int square_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (coord_x + square_size <= ROWS && coord_y + square_size <= COLS)
	{
		i = 0;
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
void	mark_square(char map[ROWS][COLS], int coord_x, int coord_y,
		int square_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < square_size)
	{
		j = 0;
		while (j < square_size)
		{
			map[coord_x + i][coord_y + j] = CHAR_FULL;
			j++;
		}
		i++;
	}
}

// Prints the map, showing the largest square at the top-left position.
void	print_map(char mapa[ROWS][COLS])
{
	int	i;
	int	j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			ft_putchar(mapa[i][j]);
			j++;
		}
		ft_putstr("\n");
		i++;
	}
}
