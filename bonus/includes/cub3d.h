/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:38:30 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/05 16:26:41 by ssawane          ###   ########.fr       */
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
# define TEX_W 64
# define TEX_H 64

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*nw;
	void	*sw;
	void	*ew;
	void	*ww;
	void	*door;
	void	*gun;
	int		*no_data;
	int		*so_data;
	int		*ea_data;
	int		*we_data;
	int		*dr_data;
	int		floor_data;
	int		ceiling_data;
}	t_data;

typedef struct s_ray {
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

typedef struct s_game {
	t_ray	r;
	t_data	img;
	int		w;
	int		h;
	int		map_w;
	int		map_h;
	int		mi;
	int		mj;
	int		miend;
	int		mjend;
	int		sf;
	int		mx;
	int		my;
	int		bx;
	int		by;
	int		add;
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
	char	*dr;
	char	*gn;
	char	**map;
	char	**dmap;
	void	*mlx;
	void	*mlx_win;
}	t_game;

typedef struct s_cub {
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
void	play_it(t_cub *cub, t_game *game);
void	window_draw(t_game *game, t_ray *r);
int		close_win(void);
int		buttonhooks(int keycode, t_game *game);
void	walls_draw(t_game *game, t_ray *r);
void	which_wall(t_game *game, t_ray *r);
void	texture_proc(t_game *game, t_ray *r);
void	floor_ceiling_draw(t_game *game, t_ray *r);
void	ray_init(t_ray *r);
void	escape(int keycode, t_game *game);
void	doors_open(t_game *game);
void	minimap(t_game *game);
void	door_map(t_cub *cub, t_game *game);
void	rotate_cam(int keycode, t_game *game);
int		mousehook(int x, int y, t_game *game);
void	gun_draw(t_game *game);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
char	*tabs_change(t_cub *cub, int k, int i);

#endif