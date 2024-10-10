/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:42:01 by fpedroso          #+#    #+#             */
/*   Updated: 2024/10/09 23:33:43 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"

void	print_map(char **map)
{
	int	i;
	int	j;

	{
		i = 0;
		while (i < ROWS)
		{
			j = 0;
			while (j < COLS)
			{
				ft_putchar(map[i][j]);
				j++;
			}
			ft_putstr("\n");
			i++;
		}
	}
}
