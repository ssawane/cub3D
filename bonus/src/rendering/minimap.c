/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:40:39 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/04 14:29:22 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_square(t_game *game)
{
	game->bx = game->mx + game->sf;
	game->by = game->my + game->sf;
	while (game->my < game->by)
	{
		while (game->mx < game->bx)
		{
			if (game->map[game->mi][game->mj] == '1')
				my_mlx_pixel_put(&game->img, game->mj + game->mx,
					game->mi + game->my, 0xC0D34141);
			else
				my_mlx_pixel_put(&game->img, game->mj + game->mx,
					game->mi + game->my, 0xA07BADCD);
			game->mx++;
		}
		game->mx -= game->sf;
		game->my++;
	}
	game->my -= game->sf;
}

void	miniborders_init(t_game *game, int *mj, int *mx)
{
	game->sf = 5;
	game->mi = (int)game->py - 5;
	game->mj = (int)game->px - 5;
	game->miend = (int)game->py + 5;
	game->mjend = (int)game->px + 5;
	game->mx = SCREEN_W / 16;
	game->my = SCREEN_H / 16;
	while (game->mi < 0)
	{
		game->my += game->sf;
		game->mi++;
	}
	while (game->mj < 0)
	{
		game->mx += game->sf;
		game->mj++;
	}
	*mj = game->mj;
	*mx = game->mx;
}

void	minimap(t_game *game)
{
	int	tmp_j;
	int	tmp_x;

	miniborders_init(game, &tmp_j, &tmp_x);
	while (game->map[game->mi] && game->mi <= game->miend)
	{
		while (game->map[game->mi][game->mj] && game->mj <= game->mjend)
		{
			if (game->map[game->mi][game->mj] == '1'
				|| (game->mj == (int)(game->py)
				&& game->mi == (int)(game->px)))
				draw_square(game);
			game->mj++;
			game->mx += game->sf;
		}
		game->my += game->sf;
		game->mx = tmp_x;
		game->mj = tmp_j;
		game->mi++;
	}
}

void	door_map(t_cub *cub, t_game *game)
{
	int	i;

	i = -1;
	game->dmap = malloc(sizeof(char *) * (cub->lines + 1));
	if (!game->dmap)
		pars_free(cub, 2);
	while (game->map[++i])
		game->dmap[i] = ft_strdup(game->map[i]);
	game->dmap[i] = 0;
}

int	mousehook(int x, int y, t_game *game)
{
	static int	current;

	if (x >= 0 && x <= SCREEN_W && y >= 0 && y <= SCREEN_H)
	{
		if (x > current)
			rotate_cam(124, game);
		if (x < current)
			rotate_cam(123, game);
		current = x;
	}
	return (0);
}
