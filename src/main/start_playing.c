/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_playing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:09:47 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/22 11:31:35 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_direction(t_game *game, char c)
{
	if (c == 'N')
	{
		game->diry = 1;
		game->plx = 0.66;
	}
	else if (c == 'S')
	{
		game->diry = -1;
		game->plx = -0.66;
	}
	else if (c == 'W')
	{
		game->dirx = -1;
		game->ply = 0.66;
	}
	else if (c == 'E')
	{
		game->dirx = 1;
		game->ply = -0.66;
	}
}

void	init_map(t_game *game)
{
	int	i;
	int	j;

	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3D");
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while(game->map[i][++j])
		{
			if (game->map[i][j] == 'N'
				|| game->map[i][j] == 'S'
				|| game->map[i][j] == 'W'
				|| game->map[i][j] == 'E')
			{
				game->px = (double)j;
				game->py = (double)i;
				init_direction(game, game->map[i][j]);
				break ;
			}
		}
	}
}

int	movings(int keycode, t_game *game)
{
	double	olddirx;
	double	oldplx;

	if (keycode == 13) // up
    {
		if (!game->map[int(game->px + game->dirx * MVSPD)][int(game->py)])
			game->px += game->dirx * MVSPD;
		if (!game->map[int(game->px)][int(game->py + game->diry * MVSPD)])
			game->py += game->diry * MVSPD;
    }
    if (keycode == 1) // down
	{
		if (!game->map[int(game->px - game->dirx * MVSPD)][int(game->py)])
	  		game->px -= game->dirx * MVSPD;
		if (!game->map[int(game->px)][int(game->py - game->diry * MVSPD)])
			game->py -= game->diry * MVSPD;
    }
    if (keycode == 2) // right
	{
		olddirx = game->dirx;
		game->dirx = game->dirx * cos(-RTSPD) - game->diry * sin(-RTSPD);
		game->diry = olddirx * sin(-RTSPD) + game->diry * cos(-RTSPD);
		oldplx = game->plx;
		game->plx = game->plx * cos(-RTSPD) - game->ply * sin(-RTSPD);
		game->ply = oldplx * sin(-RTSPD) + game->ply * cos(-RTSPD);
	}
    if (keycode == 0) // left
    {
		olddirx = game->dirx;
		game->dirx = game->dirx * cos(RTSPD) - game->diry * sin(RTSPD);
		game->diry = olddirx * sin(RTSPD) + game->diry * cos(RTSPD);
		oldplx = game->plx;
		game->plx = game->plx * cos(RTSPD) - game->ply * sin(RTSPD);
		game->ply = oldplx * sin(RTSPD) + game->ply * cos(RTSPD);
	}
}

void	play_game(t_game *game)
{
	int		x;
	t_ray	r;

	x = -1;
	while (++x < SCREEN_W)
	{
		r = malloc(sizeof(t_ray));
		r.camx = 2 * x / (double)SCREEN_W - 1;
		r.rdx = game->dirx + game->plx * r.camx;
      	r.rdy = game->diry + game->ply * r.camx;

		r.mapx = (int)game->px;
		r.mapy = (int)game->py;

		if (r.rdx)
			r.ddistx = abs(1 / r.rdx)
		else
			r.ddistx = 1e30;
		if (r.rdy)
			r.ddisty = abs(1 / r.rdy)
		else
			r.ddisty = 1e30;

		r.hit = 0;
		if(r.rdx < 0)
		{
			r.stepx = -1;
			r.sdistx = (game->px - r.mapx) * r.ddistx;
		}
		else
		{
			r.stepx = 1;
			r.sdistx = (r.mapx + 1.0 - game->px) * r.ddistx;
		}
		if(r.rdy < 0)
		{
			r.stepy = -1;
			r.sdisty = (game->py - r.mapy) * r.ddisty;
		}
		else
		{
			r.stepy = 1;
			r.sdisty = (r.mapy + 1.0 - game->py) * r.ddisty;
		}

		while(!r.hit)
		{
			if(r.sdistx < r.sdisty)
			{
				r.sdistx += r.ddistx;
				r.mapx += r.stepx;
				r.side = 0;
			}
			else
			{
				r.sdisty += r.ddisty;
				r.mapy += r.stepy;
				r.side = 1;
			}
			if(game->map[r.mapx][r.mapy] != 0)
				r.hit = 1;
		}

		if(!r.side)
			r.pwdist = (r.sdistx - r.ddistx);
		else
	  		r.pwdist = (r.sdisty - r.ddisty);
		
		r.lheight = (int)(SCREEN_H / r.pwdist);

		r.lstart = -r.lheight / 2 + SCREEN_H / 2;
		if(r.lstart < 0)
			r.lstart = 0;
		r.lend = r.lheight / 2 + SCREEN_H / 2;
		if(r.lend >= SCREEN_H)
			r.lend = SCREEN_H - 1;
	}
	mlx_key_hook(game->mlx_win, movings, game);
}

void	start_playing(t_game *game)
{
	init_map(game);
	mlx_loop_hook(game->mlx, play_game, game);
	// mlx_hook(game->mlx_win, 17, 0L, &quit, &game); // catch exit
	mlx_loop(game->mlx);
}
