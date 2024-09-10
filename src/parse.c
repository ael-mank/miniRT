/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:13:52 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/10 19:52:57 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_rt(t_scene *scene, int ac, char **av)
{
	int		fd;
	char	*line;

	line = NULL;
	if (ac != 2 || av[1] == NULL)
	{
		printf("Usage: ./miniRT *.rc\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror(av[1]);
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL && parse_element(scene, line) == true)
	{
		line = get_next_line(fd);
	}
	close(fd);
}

bool	parse_element(t_scene *scene, char *element)
{
	
}