/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:30:35 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/05 15:37:32 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cub_init(t_cub *cub)
{
	cub->infos = 0;
	cub->lines = 0;
	cub->mapstart = 0;
	cub->mapend = 0;
	cub->len = 0;
	cub->nosquare = 0;
	cub->par = NULL;
	cub->line = NULL;
	cub->par = NULL;
	cub->clrs = NULL;
	cub->game = malloc(sizeof(t_game));
	cub->game->no = NULL;
	cub->game->so = NULL;
	cub->game->we = NULL;
	cub->game->ea = NULL;
	cub->game->map = NULL;
	cub->game->dirx = 0;
	cub->game->diry = 0;
	cub->game->plx = 0;
	cub->game->ply = 0;
}

int	main(int ac, char **av)
{
	t_cub	cub;

	cub_init(&cub);
	if (!main_parsing(ac, av, &cub))
		play_it(&cub, cub.game);
	return (0);
}
