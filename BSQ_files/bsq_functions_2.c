/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_functions_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:16:36 by fpedroso          #+#    #+#             */
/*   Updated: 2024/10/09 23:04:01 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strdup(char *s)
{
	int		i;
	char	*final;
	int		len;

	len = ft_strlen(s);
	final = (char *)malloc((len + 1) * sizeof(char));
	if (final == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		final[i] = s[i];
		i++;
	}
	final[i] = '\0';
	return (final);
}

void	print_map_error(void)
{
	write(2, "map error\n", 10);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
