/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdantas- <jdantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:01:26 by jdantas-          #+#    #+#             */
/*   Updated: 2023/02/06 10:32:56 by jdantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	int		size;
	t_mlx	window;

	if (argc != 2)
	{
		print_error("Error! You must put only one argument!\n");
		return (1);
	}
	size = ft_strlen(argv[1]);
	if (size < 5 || ft_strncmp(".ber", argv[1] + size - 4, 5))
	{
		print_error("Error! Invalid extension!\n");
		return (1);
	}
	if (check_errors(&window, argv[1]) == 1)
		return (1);
	return (init_game(&window));
}

void	print_error(char *error)
{
	write (1, error, ft_strlen(error));
}

int	check_errors(t_mlx *window, char *path)
{
	int		err;
	char	**copy;

	err = 0;
	err += read_map(window, path);
	if (err != 0)
		return (1);
	err += create_map(window, path);
	if (err != 0)
		return (1);
	err += valid_walls(window) + valid_character(window);
	if (err != 0)
		return (1);
	copy = dup_map(window);
	if (copy == NULL)
		return (1);
	locate_player(window);
	test_path(copy, window->player_line, window->player_col, window);
	err += check_path(copy, window);
	free_map(copy);
	if (err != 0)
		return (1);
	return (0);
}
