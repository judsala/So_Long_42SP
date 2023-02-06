/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdantas- <jdantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:07:29 by jdantas-          #+#    #+#             */
/*   Updated: 2023/02/06 10:43:34 by jdantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h" 

int	valid_character(t_mlx *window)
{
	int	y;
	int	x;
	int	p;
	int	e;
	int	invalid;

	p = 0;
	e = 0;
	invalid = 0;
	y = -1;
	while (window->map[++y] != NULL)
	{
		x = -1;
		while (++x < window->col)
		{
			if (window->map[y][x] == 'P')
				p++;
			else if (window->map[y][x] == 'E')
				e++;
			else if (window->map[y][x] != 'C' && window->map[y][x] != '0' \
				&& window->map[y][x] != '1')
				invalid++;
		}
	}
	return (check_characters(window, e, p, invalid));
}

int	check_characters(t_mlx *window, int e, int p, int invalid)
{
	if (count_collec(window) == 1)
		print_error("Error! Invalid number of collectables!\n");
	if (e != 1)
		print_error("Error! There's a wrong number of exit on this map!\n");
	if (p != 1)
		print_error("Error! Oops... something is wrong with your player =(\n");
	if (invalid > 0)
		print_error("Error! There's a invalid character on your map!\n");
	if (window->candle == 0 || e != 1 || p != 1 || invalid > 0)
		return (1);
	return (0);
}

int	count_collec(t_mlx *window)
{
	int	x;
	int	y;

	window->candle = 0;
	y = 0;
	while (window->map[y] != NULL)
	{
		x = 0;
		while (window->map[y][x] != '\0')
		{
			if (window->map[y][x] == 'C')
			{
				window->candle = window->candle + 1;
			}
			x++;
		}
		y++;
	}
	if (window->candle == 0)
		return (1);
	else
		return (0);
}

int	check_path(char **copy, t_mlx *window)
{
	int	line;
	int	col;
	int	exit;
	int	collec;

	line = 0;
	exit = 0;
	collec = 0;
	col = 0;
	while (copy[line] != NULL)
	{
		col = 0;
		while (col < window->col)
		{
			if (copy[line][col] == 'E' && exit == 0)
				exit = 1;
			if (copy[line][col] == 'C' && collec == 0)
				collec = 1;
			col++;
		}
		line++;
	}
	return (check_exit(exit, collec));
}

int	check_exit(int exit, int collec)
{
	if (exit != 0)
		print_error("Oops! There's no exit on your map!\n");
	if (collec != 0)
		print_error("Oops! You can't access one or more collectables!\n");
	if (exit != 0 || collec != 0)
		return (1);
	return (0);
}
