/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdantas- <jdantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:21:21 by jdantas-          #+#    #+#             */
/*   Updated: 2023/02/06 10:30:12 by jdantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../GNL/get_next_line.h"
# include <mlx.h>
# include <fcntl.h>
# include <X11/keysym.h>

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	void	*player;
	void	*collec;
	void	*exit;
	void	*brick;
	void	*floor;
	int		candle;
	int		movements;
	int		col;
	int		line;
	int		player_line;
	int		player_col;
}	t_mlx;

int		check_characters(t_mlx *window, int e, int p, int invalid);
int		check_exit(int exit, int collec);
int		check_path(char **copy, t_mlx *window);
int		check_errors(t_mlx *window, char *path);
void	test_path(char **copy, int line, int col, t_mlx *window);
int		valid_character(t_mlx *window);
int		valid_walls(t_mlx *window);
void	print_error(char *error);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);
int		count_col(char *temp);
int		count_collec(t_mlx *window);
int		count_lines(int fd, char *temp, t_mlx *window);
int		create_map(t_mlx *window, char *path);
char	**dup_map(t_mlx *window);
int		init_game(t_mlx *window);
int		read_map(t_mlx *window, char *path);
int		show_map(t_mlx *window);
int		events(int key, t_mlx *window);
void	event_arrow(t_mlx *window, int col, int line);
int		show_moves(t_mlx *window);
void	locate_player(t_mlx *window);
void	put_image_to_window(t_mlx *window, void *image, int x, int y);
void	put_sprites(t_mlx *window);
void	sprites(t_mlx *window, void **image, char *path);
int		close_map(t_mlx *window);
int		close_and_free(int fd, char *temp);
void	free_map(char **map);

#endif