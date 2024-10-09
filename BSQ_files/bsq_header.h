/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_header.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:03:08 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/09 21:51:07 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_HEADER_H
# define BSQ_HEADER_H

typedef struct s_map_chars
{
	char		empty;
	char		obstacle;
	char		full;
}				t_map_chars;

typedef struct s_map
{
	char		*header;
	char		**data;
	int			total_lines;
	int			max_lines;
	t_map_chars	chars;
}				t_map;

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

// ft functions:

void	ft_putchar(char c);
void	ft_putstr(char *str);
char	*ft_strndup(const char *s, int n);
char	*ft_strdup(char *s);
int		ft_strlen(char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_tiktok(char *str, char delim);

// specific functions:

void	print_map_error(void);

// atoi
int		ft_atoi(char *str);
int		calculate_sign(int sign, char c);
int		calculate_result(int result, char *str);
int		is_space(char c);

#endif
