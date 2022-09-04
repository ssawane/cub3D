/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:27:16 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/04 14:29:57 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_val(t_game *game, t_ray *r)
{
	r->camx = 2 * r->x / (double)SCREEN_W - 1;
	r->rdx = game->dirx + game->plx * r->camx;
	r->rdy = game->diry + game->ply * r->camx;
	r->mapx = (int)game->px;
	r->mapy = (int)game->py;
	if (r->rdx == 0)
		r->ddistx = 1e30;
	else
		r->ddistx = fabs(1 / r->rdx);
	if (r->rdy == 0)
		r->ddisty = 1e30;
	else
		r->ddisty = fabs(1 / r->rdy);
}

void	dda_init(t_game *game, t_ray *r)
{
	if (r->rdx < 0)
	{
		r->stepx = -1;
		r->sdistx = (game->px - r->mapx) * r->ddistx;
	}
	else
	{
		r->stepx = 1;
		r->sdistx = (r->mapx + 1 - game->px) * r->ddistx;
	}
	if (r->rdy < 0)
	{
		r->stepy = -1;
		r->sdisty = (game->py - r->mapy) * r->ddisty;
	}
	else
	{
		r->stepy = 1;
		r->sdisty = (r->mapy + 1 - game->py) * r->ddisty;
	}
}

void	dda_proc(t_game *game, t_ray *r)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->sdistx < r->sdisty)
		{
			r->sdistx += r->ddistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sdisty += r->ddisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (game->map[r->mapx][r->mapy] == '1')
			r->hit = 1;
		else if (game->map[r->mapx][r->mapy] == 'D')
			r->hit = 2;
	}
}

void	line_end_start(t_ray *r)
{
	if (!r->side)
		r->pwdist = (r->sdistx - r->ddistx);
	else
		r->pwdist = (r->sdisty - r->ddisty);
	r->lheight = (int)(SCREEN_H / r->pwdist);
	r->lstart = -r->lheight / 2 + SCREEN_H / 2;
	if (r->lstart < 0)
		r->lstart = 0;
	r->lend = r->lheight / 2 + SCREEN_H / 2;
	if (r->lend >= SCREEN_H)
		r->lend = SCREEN_H - 1;
}

void	window_draw(t_game *game, t_ray *r)
{
	ray_init(r);
	game->img.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	floor_ceiling_draw(game, r);
	doors_open(game);
	while (r->x < SCREEN_W)
	{
		init_val(game, r);
		dda_init(game, r);
		dda_proc(game, r);
		line_end_start(r);
		texture_proc(game, r);
		which_wall(game, r);
		r->x += 1;
	}
	minimap(game);
	walls_draw(game, r);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	gun_draw(game);
	mlx_destroy_image(game->mlx, game->img.img);
}
