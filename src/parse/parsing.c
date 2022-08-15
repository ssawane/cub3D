/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:29:46 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/13 10:19:16 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_checks(int ac, char **av, t_cub *cub)
{
	int	i;

	if (ac != 2)
	{
		printf("%s\n", "error: arguments");
		exit(1);
	}
	i = ft_strlen(av[1]) - 1;
	if (i < 4 || av[1][i] != 'b' || av[1][i - 1] != 'u'
		|| av[1][i - 2] != 'c' || av[1][i - 3] != '.')
	{
		printf("%s\n", "error: format");
		exit (1);
	}
	lines_count(av, cub);
	cub->fd = open(av[1], O_RDONLY);
	if (cub->fd <= 0)
	{
		perror("error: cannot open the map");
		exit(1);
	}
}

int	main_parsing(int ac, char **av, t_cub *cub)
{
	int		i;

	i = 0;
	init_checks(ac, av, cub);
	while (++i < cub->mapstart)
	{
		cub->line = get_next_line(cub->fd);
		params(cub);
	}
	cub->line = NULL;
	if (cub->infos != 6)
		pars_free(cub, 1);
	map_convert(cub, i);
	map_checks(cub);
	close(cub->fd);
	return (0);
}