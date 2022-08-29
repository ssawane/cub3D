/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:09:47 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/28 13:56:05 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_direction(t_game *game, char c)
{
	if (c == 'N')
	{
		game->dirx = 1;
		game->ply = 0.66;
	}
	else if (c == 'S')
	{
		game->dirx = -1;
		game->ply = -0.66;
	}
	else if (c == 'W')
	{
		game->diry = -1;
		game->plx = 0.66;
	}
	else if (c == 'E')
	{
		game->diry = 1;
		game->plx = -0.66;
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
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'N'
				|| game->map[i][j] == 'S'
				|| game->map[i][j] == 'W'
				|| game->map[i][j] == 'E')
			{
				game->px = (double)j;
				game->py = (double)i;
				game->map[i][j] = '0';
				init_direction(game, game->map[i][j]);
				break ;
			}
		}
	}
}

void	ray_init(t_ray *r)
{
	int	i;

	r->x = 0;
	r->hit = 0;
	i = -1;
	r->buffer = malloc(sizeof (int *) * SCREEN_H);
	if (!r->buffer)
		exit(1);
	while (++i < SCREEN_H)
	{
		r->buffer[i] = malloc(sizeof(int) * SCREEN_W);
		if (!r->buffer[i])
			exit (1);
	}
}

void	data_load(t_cub *cub, t_game *game, t_data *img)
{
	int		w;
	int		h;

	img->north_wall = mlx_xpm_file_to_image(game->mlx, game->no, &w, &h);
	img->east_wall = mlx_xpm_file_to_image(game->mlx, game->ea, &w, &h);
	img->west_wall = mlx_xpm_file_to_image(game->mlx, game->we, &w, &h);
	img->south_wall = mlx_xpm_file_to_image(game->mlx, game->so, &w, &h);
	if (!game->img.north_wall || !game->img.south_wall
		|| !game->img.east_wall || !game->img.west_wall)
		pars_free(cub, 1);
	img->no_data = (int *)mlx_get_data_addr(img->north_wall,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	img->so_data = (int *)mlx_get_data_addr(img->south_wall,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	img->ea_data = (int *)mlx_get_data_addr(img->east_wall,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	img->we_data = (int *)mlx_get_data_addr(img->west_wall,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	img->floor_data = (256 * 256 * game->floor[0]
			+ 256 * game->floor[1] + game->floor[2]);
	img->ceiling_data = (256 * 256 * game->ceiling[0]
			+ 256 * game->ceiling[1] + game->ceiling[2]);
}

void	play_it(t_cub *cub, t_game *game)
{
	init_map(game);
	data_load(cub, game, &game->img);
	window_draw(game, &game->r);
	mlx_hook(game->mlx_win, 17, 0, close_win, 0);
	mlx_hook(game->mlx_win, 2, 1L << 0, buttonhooks, game);
	mlx_loop(game->mlx);
}
