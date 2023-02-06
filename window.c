/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdantas- <jdantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:07:40 by jdantas-          #+#    #+#             */
/*   Updated: 2023/02/06 10:31:48 by jdantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_walls(t_mlx *window)
{
	int	x;
	int	max;

	x = 0;
	max = window->col;
	if (window->col < window->line)
		max = window->line;
	while (x < max)
	{
		if (window->col - x > 0)
			if (window->map[0][x] != '1' || \
				window->map[window->line - 1][x] != '1')
				break ;
		if (window->line - x > 0)
			if (window->map[x][0] != '1' || \
				window->map[x][window->col - 1] != '1')
				break ;
		x++;
	}
	if (x != max)
	{
		print_error("Oops! Something is wrong with your walls!\n");
		return (1);
	}
	return (0);
}

void	test_path(char **copy, int line, int col, t_mlx *window)
{
	if (copy[line][col] == 'X' || copy[line][col] == '1' || \
	copy[line][col] == 'S')
		return ;
	if (copy[line][col] == 'E')
	{
		copy[line][col] = 'S';
		return ;
	}
	else
		copy[line][col] = 'X';
	test_path(copy, line - 1, col, window);
	test_path(copy, line + 1, col, window);
	test_path(copy, line, col - 1, window);
	test_path(copy, line, col + 1, window);
}

int	count_lines(int fd, char *temp, t_mlx *window)
{
	int		count_line_break;

	count_line_break = 0;
	window->line = 0;
	window->col = count_col (temp);
	while (temp != NULL)
	{
		if (temp[0] != '\n' && count_line_break == 0)
			window->line++;
		else if (temp[0] != '\n' && count_line_break != 0)
			return (close_and_free(fd, temp));
		else if (temp[0] == '\n')
			count_line_break++;
		free(temp);
		temp = get_next_line(fd);
		if (temp && temp[0] != '\n' && window->col != count_col(temp))
			return (close_and_free(fd, temp));
	}
	close (fd);
	return (0);
}

int	count_col(char *temp)
{
	int	i;

	i = 0;
	while (temp != NULL && temp[i] != 0 && temp[i] != '\n' && temp[i] != '\r')
		i++;
	return (i);
}

int	close_and_free(int fd, char *temp)
{
	print_error("Oops! Something is wrong with your map!\n");
	free(temp);
	close(fd);
	return (1);
}
