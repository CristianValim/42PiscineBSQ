/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:03:10 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/09 22:16:57 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_header.h"

char	*ft_tiktok(char *str, char delimiter)
{
	static char	*current_position;
	char		*start;

	if (str)
	{
		current_position = str;
	}
	if (!current_position || *current_position == '\0')
	{
		return (NULL);
	}
	start = current_position;
	while (*current_position && *current_position != delimiter)
	{
		current_position++;
	}
	if (*current_position)
	{
		*current_position = '\0';
		current_position++;
	}
	return (start);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*final;

	final = (char *)malloc((n + 1) * sizeof(char));
	if (final == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] && i < n)
	{
		final[i] = s[i];
		i++;
	}
	final[i] = '\0';
	return (final);
}
