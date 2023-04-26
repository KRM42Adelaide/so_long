/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmachaka <kmachaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:42:34 by kmachaka          #+#    #+#             */
/*   Updated: 2023/04/26 19:09:25 by kmachaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	horizon_wall(t_complete *game)
{
	int	i;
	int	j;

	i = game->mapwidth;
	j = 0;
	while (j < i)
	{
		if (game->map[0][i] == '1'
			&& game->map[game->mapheight - 1][j] == '1')
			return (0);
		j++;
	}
	return (1);
}

static int	vert_wall(t_complete *game)
{
	int	height;
	int	width;

	height = 0;
	width = game->mapwidth;
	while (height < game->mapheight)
	{
		if (!(game->map[height][0] == '1'
			&& game->map[height][width - 1] == '1'))
			return (0);
		height++;
	}
	return (1);
}

void	if_walls(t_complete *game)
{
	int	verticalwalls;
	int	horizontalwalls;

	verticalwalls = vert_wall(game);
	horizontalwalls = horizon_wall(game);
	if (!verticalwalls || !horizontalwalls)
	{
		printf("\nThis map is missing the walls\n");
		exit_point(game);
	}
}

void	count_checker(t_complete *game, int height, int width)
{
	if (game->map[height][width] != '1' &&
		game->map[height][width] != '0' &&
		game->map[height][width] != 'P' &&
		game->map[height][width] != 'E' &&
		game->map[height][width] != 'C' &&
		game->map[height][width] != '\n')
	{
		printf("\nError Here!%c\n", game->map[height][width]);
		exit_point(game);
	}
	if (game->map[height][width] == 'C')
			game->columncount++;
	if (game->map[height][width] == 'P')
			game->playercount++;
	if (game->map[height][width] == 'E')
			game->exitcount++;
}

void	valid_character(t_complete *game)
{
	int	height;
	int	width;

	height = 0;
	while (height < game->mapheight - 1)
	{
		width = 0;
		while (width <= game->mapwidth)
		{
			count_checker(game, height, width);
			width++;
		}
		height++;
	}
	if (!(game->playercount == 1 && game->columncount > 1
			&& game->exitcount == 1))
	{
		printf("\nError\nSomething is wrong!\n");
		printf("There is an issue with player, exit or collectable\n");
		exit_point(game);
	}
}
