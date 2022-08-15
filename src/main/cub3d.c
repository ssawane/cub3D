/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:30:35 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/13 11:05:06 by ssawane          ###   ########.fr       */
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
}

int	main(int ac, char **av)
{
	t_cub	cub;

	cub_init(&cub);
	if (!main_parsing(ac, av, &cub))
	{
		print_params(cub.game);
		printf("%d cub lines\n", cub.lines);
		printf("%d cub mapstart\n", cub.mapstart);
		printf("%d cub mapend\n", cub.mapend);
		printf("%d cub infos\n", cub.infos);
		print_map(cub.game);
	}
	// while (1);
	return (0);
}