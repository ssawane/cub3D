/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttonhooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:49:25 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/05 15:55:34 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	isstepable(t_game *game, double x, double y)
{
	double	rad_x;
	double	rad_y;
	double	rad;

	rad = 0.2;
	rad_x = -rad;
	while (rad_x <= 0.2)
	{
		rad_y = -rad;
		while (rad_y <= 0.2)
		{
			if (game->map[(int)(x + rad_x)][(int)(y + rad_y)] != '0')
				return (1);
			rad_y += rad;
		}
		rad_x += rad;
	}
	return (0);
}

void	rotate_cam(int keycode, t_game *game)
{
	if (keycode == RIGHT)
	{
		game->olddirx = game->dirx;
		game->dirx = game->dirx * cos(RTSPD) - game->diry * sin(RTSPD);
		game->diry = game->olddirx * sin(RTSPD) + game->diry * cos(RTSPD);
		game->oldplx = game->plx;
		game->plx = game->plx * cos(RTSPD) - game->ply * sin(RTSPD);
		game->ply = game->oldplx * sin(RTSPD) + game->ply * cos(RTSPD);
		window_draw(game, &game->r);
	}
	if (keycode == LEFT)
	{
		game->olddirx = game->dirx;
		game->dirx = game->dirx * cos(-RTSPD) - game->diry * sin(-RTSPD);
		game->diry = game->olddirx * sin(-RTSPD) + game->diry * cos(-RTSPD);
		game->oldplx = game->plx;
		game->plx = game->plx * cos(-RTSPD) - game->ply * sin(-RTSPD);
		game->ply = game->oldplx * sin(-RTSPD) + game->ply * cos(-RTSPD);
		window_draw(game, &game->r);
	}
}

void	move_up_down(int keycode, t_game *game)
{
	if (keycode == W_UP)
	{
		if (!isstepable(game, game->px + game->dirx * MVSPD, game->py))
			game->px += game->dirx * MVSPD;
		if (!isstepable(game, game->px, game->py + game->diry * MVSPD))
			game->py += game->diry * MVSPD;
		game->add++;
		window_draw(game, &game->r);
	}
	if (keycode == S_DOWN)
	{
		if (!isstepable(game, game->px - game->dirx * MVSPD, game->py))
			game->px -= game->dirx * MVSPD;
		if (!isstepable(game, game->px, game->py - game->diry * MVSPD))
			game->py -= game->diry * MVSPD;
		game->add++;
		window_draw(game, &game->r);
	}
}

void	move_left_right(int keycode, t_game *game)
{
	if (keycode == D_RIGHT)
	{
		if (!isstepable(game, game->px + game->plx * MVSPD, game->py))
			game->px += game->plx * MVSPD;
		if (!isstepable(game, game->px, game->py + game->ply * MVSPD))
			game->py += game->ply * MVSPD;
		game->add++;
		window_draw(game, &game->r);
	}
	if (keycode == A_LEFT)
	{
		if (!isstepable(game, game->px - game->plx * MVSPD, game->py))
			game->px -= game->plx * MVSPD;
		if (!isstepable(game, game->px, game->py - game->ply * MVSPD))
			game->py -= game->ply * MVSPD;
		game->add++;
		window_draw(game, &game->r);
	}
}

int	buttonhooks(int keycode, t_game *game)
{
	escape(keycode, game);
	rotate_cam(keycode, game);
	move_up_down(keycode, game);
	move_left_right(keycode, game);
	return (0);
}
