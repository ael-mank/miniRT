/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:13:52 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/16 20:02:00 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_rt(t_scene *scene, int ac, char **av)
{
	int		fd;
	char	*element;

	element = NULL;
	if (ac != 2 || av[1] == NULL)
	{
		ft_putstr_fd("Usage: ./miniRT *.rc\n", 2);
		exit(0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror(av[1]);
		exit(1);
	}
	element = get_next_line(fd);
	while (element != NULL && parse_element(scene, element) == true)
	{
		free(element);
		element = get_next_line(fd);
	}
	free(element);
	close(fd);
}

bool	parse_element(t_scene *scene, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (!ft_strncmp(line, "A ", 2))
		return (parse_and_add_ambient(++line, scene));
	// if (!ft_strncmp(line, "C ", 2))
	// 	return (parse_and_add_camera(++line, scene));
	// if (!ft_strncmp(line, "L ", 2))
	// 	return (parse_and_add_light(++line, scene));
	// if (!ft_strncmp(line, "pl ", 3))
	// 	return (parse_and_add_plane(++line, scene));
	// if (!ft_strncmp(line, "sp ", 3))
	// 	return (parse_and_add_sphere(++line, scene));
	// if (!ft_strncmp(line, "cy ", 3))
	// 	return (parse_and_add_cylinder(++line, scene));
	else
	{
		ft_putstr_fd("Error: Wrong type of element.\n", 2);
		return (false);
	}
}

bool	parse_and_add_ambient(char *line, t_scene *scene)
{
	if (scene->a != NULL)
	{
		ft_putstr_fd("Error: Ambient light can only be declared once.\n", 2);
		return (false);
	}
	scene->a = malloc(sizeof(t_ambient));
	if (scene->a == NULL)
		return (false);
	// printf("+++%s\n", line);
	if (!parse_ratio(&line, &scene->a->ratio))
	{
		ft_putstr_fd("Error: Ambient light's ratio is invalid\n", 2);
		ft_putstr_fd("Ambient light must have a ratio in range [0.0,1.0]\n", 1);
		free(scene->a);
		return (false);
	}
	// printf("---%s\n", line);
	if (!parse_color(&line, &scene->a->color))
	{
		ft_putstr_fd("Error: Ambient lightning's color is invalid\n", 2);
		ft_putstr_fd("Ambient light must have R, G, B colors in range [0-255]\n", 1);
		return (false);
	}
	while (ft_isspace(*line))
		line++;
	if (*line == '\0')
	{
		printf("Ambient light | Ratio: %f | Color: %d,%d,%d\n", scene->a->ratio, scene->a->color.r, scene->a->color.g, scene->a->color.b);
		return (true);
	}
	free(scene->a);
	ft_putstr_fd("Error: Ambient light has noise information\n", 2);
	return (false);
}
