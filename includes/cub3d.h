/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:38:30 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/22 14:15:54 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <fcntl.h>
# define SCREEN_W 640
# define SCREEN_H 480
# define MVSPD 1.0
# define RTSPD 1.0

typedef struct	s_ray {
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lheight;
	int		lstart;
	int		lend;
	double	camx;
	double	rdx;
	double	rdy;
	double	sdistx;
	double	sdisty;
	double	ddistx;
	double	ddisty;
	double	pwdist;
}	t_ray;

typedef struct	s_game {
	int		map_w;
	int		map_h;
	double	px;
	double	py;
	double	dirx;
	double	diry;
	double	plx;
	double	ply;
	int		floor[3];
	int		ceiling[3];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**map;
	void	*mlx;
	void	*mlx_win;
}	t_game;

typedef struct	s_cub {
	t_game	*game;
	int		fd;
	int		clr;
	int		infos;
	int		lines;
	int		mapstart;
	int		mapend;
	int		len;
	int		nosquare;
	char	*line;
	char	**par;
	char	**clrs;
}	t_cub;

char	*get_next_line(int fd);
int		main_parsing(int ac, char **av, t_cub *cub);
void	lines_count(char **av, t_cub *cub);
void	params(t_cub *cub);
void	pars_free(t_cub *cub, int flag);
void	free_mass(char **mass);
void	color_check(t_cub *cub, int type);
int		isempty(char *line);
int		ismap(char *line);
void	line_mod(t_cub *cub);
void	map_convert(t_cub *cub, int i);
void	map_checks(t_cub *cub);
void	borders_check(char **map, t_cub *cub);
void	start_playing(t_game *game);


// temp
void	print_params(t_game *game);
void	print_map(t_game *game);

#endif