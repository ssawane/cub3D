/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:38:30 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/28 14:03:47 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define W_UP 13
# define A_LEFT 0
# define S_DOWN 1
# define D_RIGHT 2
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define SCREEN_W 640
# define SCREEN_H 480
# define MVSPD 0.15
# define RTSPD 0.09
# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*north_wall;
	void	*south_wall;
	void	*east_wall;
	void	*west_wall;
	int		*no_data;
	int		*so_data;
	int		*ea_data;
	int		*we_data;
	int		floor_data;
	int		ceiling_data;
}	t_data;

typedef struct	s_ray {
	int		x;
	int		y;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lheight;
	int		lstart;
	int		lend;
	int		tex_x;
	int		tex_y;
	int		color;
	double	camx;
	double	rdx;
	double	rdy;
	double	sdistx;
	double	sdisty;
	double	ddistx;
	double	ddisty;
	double	pwdist;
	double	wall_x;
	double	step;
	double	texpos;
	int		**buffer;
}	t_ray;

typedef struct	s_game {
	t_ray	r;
	t_data	img;
	int		map_w;
	int		map_h;
	double	px;
	double	py;
	double	dirx;
	double	diry;
	double	plx;
	double	ply;
	double	oldplx;
	double	olddirx;
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

// parse
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

// render
void	window_draw(t_game *game, t_ray *r);
int		close_win(void);
int		buttonhooks(int keycode, t_game *game);
void	walls_draw(t_game *game, t_ray *r);
void	which_wall(t_game *game, t_ray *r);
void	texture_proc(t_game *game, t_ray *r);
void	floor_ceiling_draw(t_game *game, t_ray *r);
void	ray_init(t_ray *r);
void	escape(int keycode, t_game *game);



// temp
void	print_params(t_game *game);
void	print_map(t_game *game);
void	print_char(char **game);

#endif