/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdantas- <jdantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:07:06 by jdantas-          #+#    #+#             */
/*   Updated: 2023/02/06 11:19:48 by jdantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h" 

void	put_image_to_window(t_mlx *window, void *image, int x, int y)
{
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, \
		image, 32 * x, 32 * y);
}

int	create_map(t_mlx *window, char *path)
{
	int		y;
	int		fd;
	char	*temp;

	y = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error("Error! Something is wrong with your file!\n");
	temp = get_next_line(fd);
	if (temp == NULL)
		return (1);
	window->map = malloc((window->line + 1) * sizeof(char *));
	if (window->map == NULL)
		return (1);
	while (y < window->line)
	{
		window->map[y] = temp;
		y++;
		temp = get_next_line(fd);
		if (y < window->line && temp == NULL)
			return (1);
	}
	close (fd);
	window->map[y] = NULL;
	return (0);
}

char	**dup_map(t_mlx *window)
{
	char	**copy;
	int		y;

	copy = malloc((window->line + 1) * sizeof(char *));
	y = 0;
	while (window->map[y] != NULL)
	{
		copy[y] = ft_strdup(window->map[y]);
		if (copy[y] == NULL)
		{
			free_map(copy);
			return (NULL);
		}
		copy[y][window->col] = '\0';
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

void	free_map(char **map)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
	{
		free (map[i]);
		i++;
	}
	free(map);
}

int	read_map(t_mlx *window, char *path)
{
	int		fd;
	char	*temp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error! Something is wrong with your file!\n");
		return (1);
	}
	temp = get_next_line(fd);
	if (temp == NULL)
		print_error("Error! Empty map!\n");
	if (temp[0] != '1')
		print_error("Error! Invalid map!\n");
	if (temp == NULL || temp[0] != '1')
		return (1);
	if (count_lines(fd, temp, window) == 1)
		return (1);
	if (window->col > 60 || window->line > 32)
	{
		print_error("Error! This map is too big!\n");
		return (1);
	}
	return (0);
}
