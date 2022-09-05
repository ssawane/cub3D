/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/05 15:48:33 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	walls_draw(t_game *game, t_ray *r)
{
	int	i;

	r->y = 0;
	while (r->y < SCREEN_H)
	{
		r->x = 0;
		while (r->x < SCREEN_W)
		{
			my_mlx_pixel_put(&game->img, r->x, r->y, r->buffer[r->y][r->x]);
			r->x++;
		}
		r->y++;
	}
	i = -1;
	while (++i < SCREEN_H)
		free(r->buffer[i]);
	free(r->buffer);
	r->buffer = NULL;
}

void	floor_ceiling_draw(t_game *game, t_ray *r)
{
	int	y;
	int	x;

	y = -1;
	while (++y < SCREEN_H)
	{
		x = -1;
		while (++x < SCREEN_W)
		{
			r->buffer[y][x] = game->img.floor_data;
			r->buffer[SCREEN_H - y - 1][x] = game->img.ceiling_data;
		}
	}
}

void	which_wall(t_game *game, t_ray *r)
{
	while (++r->y < r->lend)
	{
		r->tex_y = (int)r->texpos & (TEX_H - 1);
		r->texpos += r->step;
		if (r->hit == 1)
		{
			if (r->side == 1)
			{
				if (r->rdy > 0)
					r->color = game->img.no_data[TEX_H * r->tex_y + r->tex_x];
				else
					r->color = game->img.so_data[TEX_H * r->tex_y + r->tex_x];
			}
			else
			{
				if (r->rdx > 0)
					r->color = game->img.we_data[TEX_H * r->tex_y + r->tex_x];
				else
					r->color = game->img.ea_data[TEX_H * r->tex_y + r->tex_x];
			}
		}
		else if (r->hit == 2)
			r->color = game->img.dr_data[TEX_H * r->tex_y + r->tex_x];
		r->buffer[r->y][r->x] = r->color;
	}
}

void	texture_proc(t_game *game, t_ray *r)
{
	if (!r->side)
		r->wall_x = game->py + r->pwdist * r->rdy;
	else
		r->wall_x = game->px + r->pwdist * r->rdx;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)(TEX_W));
	if (!r->side && r->rdx > 0)
		r->tex_x = TEX_W - r->tex_x - 1;
	if (r->side == 1 && r->rdy < 0)
		r->tex_x = TEX_W - r->tex_x - 1;
	r->step = 1.0 * TEX_H / r->lheight;
	r->texpos = (r->lstart - SCREEN_H / 2 + r->lheight / 2) * r->step;
	r->y = r->lstart - 1;
}
