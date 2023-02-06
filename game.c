/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdantas- <jdantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:06:56 by jdantas-          #+#    #+#             */
/*   Updated: 2023/02/06 10:33:47 by jdantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_game(t_mlx *window)
{
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
	{
		print_error("Error! Something is wrong with your mlx!\n");
		return (1);
	}
	window->win_ptr = mlx_new_window(window->mlx_ptr, window->col * \
		32, window->line * 32, "So_long - Some Nightmares");
	if (window->win_ptr == NULL)
	{
		print_error("Error! Something is wrong with your mlx!\n");
		return (1);
	}
	window->movements = 0;
	put_sprites(window);
	mlx_hook(window->win_ptr, 2, (1L << 0), &events, window);
	mlx_hook(window->win_ptr, 17, 0, &close_map, window);
	mlx_loop_hook(window->mlx_ptr, &show_map, window);
	mlx_loop(window->mlx_ptr);
	return (0);
}

void	put_sprites(t_mlx *window)
{
	sprites(window, &window->player, "sprites/player.xpm");
	sprites(window, &window->brick, "sprites/brick.xpm");
	sprites(window, &window->collec, "sprites/candle.xpm");
	sprites(window, &window->exit, "sprites/door.xpm");
	sprites(window, &window->floor, "sprites/floor.xpm");
}

void	sprites(t_mlx *window, void **image, char *path)
{
	int	width;
	int	height;

	*image = mlx_xpm_file_to_image(window->mlx_ptr, path, &width, &height);
	if (*image == NULL)
	{	
		print_error("Something is wrong with your sprites\n");
		close_map(window);
	}
}

int	close_map(t_mlx *window)
{
	mlx_destroy_image(window->mlx_ptr, window->player);
	mlx_destroy_image(window->mlx_ptr, window->collec);
	mlx_destroy_image(window->mlx_ptr, window->exit);
	mlx_destroy_image(window->mlx_ptr, window->brick);
	mlx_destroy_image(window->mlx_ptr, window->floor);
	free_map(window->map);
	mlx_destroy_window (window->mlx_ptr, window->win_ptr);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	exit (0);
	return (0);
}
