/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdantas- <jdantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:07:20 by jdantas-          #+#    #+#             */
/*   Updated: 2023/02/06 11:50:38 by jdantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	show_map(t_mlx *window)
{
	int	y;
	int	x;

	y = -1;
	while (window->map[++y] != NULL)
	{
		x = 0;
		while (x < window->col)
		{
			if (window->map[y][x] == '1')
				put_image_to_window(window, window->brick, x, y);
			else if (window->map[y][x] == 'P')
				put_image_to_window(window, window->player, x, y);
			else if (window->map[y][x] == 'C')
				put_image_to_window(window, window->collec, x, y);
			else if (window->map[y][x] == 'E' && window->candle != 0)
				put_image_to_window(window, window->exit, x, y);
			else if (window->map[y][x] == 'E' && window->candle == 0)
				put_image_to_window(window, window->exit, x, y);
			else if (window->map[y][x] == '0')
				put_image_to_window(window, window->floor, x, y);
			x++;
		}
	}
	return (show_moves(window));
}

int	show_moves(t_mlx *window)
{
	char	*movements;

	mlx_string_put(window->mlx_ptr, window->win_ptr, 12, 15, \
	0xc0ff0000, "Moves: ");
	movements = ft_itoa(window->movements);
	mlx_string_put(window->mlx_ptr, window->win_ptr, 60, 15, \
	0xc0ff0000, movements);
	free(movements);
	return (0);
}

int	events(int key, t_mlx *window)
{
	if (key == XK_Escape)
	{
		close_map(window);
	}
	if (key == XK_a || key == XK_A || key == XK_Left)
	{
		event_arrow(window, -1, 0);
	}
	if (key == XK_d || key == XK_D || key == XK_Right)
	{
		event_arrow(window, +1, 0);
	}
	if (key == XK_w || key == XK_W || key == XK_Up)
	{
		event_arrow(window, 0, -1);
	}
	if (key == XK_s || key == XK_S || key == XK_Down)
	{
		event_arrow(window, 0, +1);
	}
	return (0);
}

void	event_arrow(t_mlx *window, int col, int line)
{
	locate_player(window);
	if (window->map[window->player_line + line][window->player_col + col] == 48)
	{
		window->map[window->player_line + line][window->player_col + col] = 80;
		window->map[window->player_line][window->player_col] = 48;
		window->movements ++;
	}
	if (window->map[window->player_line + line][window->player_col + col] == 67)
	{
		window->map[window->player_line + line][window->player_col + col] = 80;
		window->map[window->player_line][window->player_col] = 48;
		window->candle --;
		window->movements ++;
	}
	if (window->map[window->player_line + line][window->player_col + col] == 69 \
		&& window->candle == 0)
	{
		window->map[window->player_line][window->player_col] = 48;
		window->movements ++;
		print_error("\n***Congratulations! You Finished the Game!***\n\n");
		close_map(window);
	}
}

void	locate_player(t_mlx *window)
{
	int	x;
	int	y;

	y = 0;
	while (window->map[y] != NULL)
	{
		x = 0;
		while (window->map[y][x] != '\0')
		{
			if (window->map[y][x] == 'P')
			{
				window->player_line = y;
				window->player_col = x;
				return ;
			}
			x++;
		}
		y++;
	}
}
