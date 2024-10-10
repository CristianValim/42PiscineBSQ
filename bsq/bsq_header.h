/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_header.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvalim-d <cvalim-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:03:08 by cvalim-d          #+#    #+#             */
/*   Updated: 2024/10/09 23:02:26 by cvalim-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_HEADER_H
# define BSQ_HEADER_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_temp
{
	int				x;
	int				y;
	int				size;
}					t_square_info;

typedef struct s_characters
{
	char			empty;
	char			obstacle;
	char			full;
}					t_characters;

typedef struct s_map
{
	char			**data;
	char			*header;
	t_characters	chars;
	int				total_lines;
	int				max_lines;
}					t_map;

// ft functions:

void				ft_putchar(char c);
void				ft_putstr(char *str);
char				*ft_strndup(const char *s, int n);
char				*ft_strdup(char *s);
int					ft_strlen(char *str);
char				*ft_strchr(const char *str, int c);
char				*ft_tiktok(char *str, char delimiter);

// specific functions:
void				print_map_error(void);

// atoi
int					ft_atoi(char *str);
int					calculate_sign(int sign, char c);
int					calculate_result(int result, char *str);
int					is_space(char c);

// from find_map.c >>>OK!!!
# define ROWS 10
# define COLS 10
# define CHAR_EMPTY '.'
# define CHAR_FULL 'X'

void				find_max_square(char **map);
void				check_all_squares(char **map, int square_size,
						t_square_info *max_square, int *found_space);
int					check_fit_square(char **map, int coord_x, int coord_y,
						int square_size);
void				mark_square(char **map, t_square_info square);
void				update_max_square_info(int coord_x, int coord_y,
						int square_size, t_square_info *max_square);
void				print_map(char **map);

// from check_map1 to 4 >>> OK!!
int					process_map(char *map_start, t_map *map);
char				*allocate_buffer(int size);
char				*expand_buffer(char *buffer, int new_size);
int					validate_map_structure(t_map *map);
int					validate_map_characters(t_map *map);
int					check_map(t_map *map);
void				cleanup(t_map *map, char *buffer, int file_descriptor);
int					open_file_safe(char *file_name);
char				*read_file(char *file_name, t_map *map, int *total_bytes);
char				*read_file_content(int fd, int *total_bytes);
int					allocate_map_data(t_map *map);
int					fill_map_data(char *map_start, t_map *map);
char				*process_header(char *buffer, t_map *map);
int					check_header(char *header, t_map *map);
int					validate_line_count(char *line_count_str);
int					check_length(t_map *map);
int					check_lines(char *buffer, t_map *map);

#endif
