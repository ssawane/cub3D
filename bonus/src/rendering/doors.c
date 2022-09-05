/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 12:08:42 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/05 15:40:23 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	player_around(t_game *game, int x, int y)
{
	int	rad_x;
	int	rad_y;
	int	rad;

	rad = 1;
	rad_x = -rad;
	while (rad_x <= 1)
	{
		rad_y = -rad;
		while (rad_y <= 1)
		{
			if (x + rad_x == (int)(game->px)
				&& y + rad_y == (int)(game->py))
				return (1);
			rad_y += rad;
		}
		rad_x += rad;
	}
	return (0);
}

void	doors_open(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (game->dmap[++x])
	{
		y = -1;
		while (game->dmap[x][++y])
		{
			if (game->dmap[x][y] == 'D')
			{
				if (player_around(game, x, y) && game->map[x][y] == 'D')
					game->map[x][y] = '0';
				else if (!player_around(game, x, y) && game->map[x][y] == '0')
					game->map[x][y] = 'D';
			}
		}
	}
}

void	gun_draw(t_game *game)
{
	int	delta;

	if (game->add == 14)
		game->add = -7;
	if (game->add >= -7 && game->add < 7)
		delta = game->add;
	else if (game->add >= 7 && game->add < 14)
		delta = (game->add - 10) * -2;
	mlx_put_image_to_window(game->mlx,
		game->mlx_win, game->img.gun, -50, 230 + delta);
}
