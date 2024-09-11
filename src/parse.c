/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:13:52 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/11 20:41:13 by yrigny           ###   ########.fr       */
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
	if (!ft_strncmp(line, "C ", 2))
		return (parse_and_add_camera(++line, scene));
	if (!ft_strncmp(line, "L ", 2))
		return (parse_and_add_light(++line, scene));
	if (!ft_strncmp(line, "pl ", 3))
		return (parse_and_add_plane(++line, scene));
	if (!ft_strncmp(line, "sp ", 3))
		return (parse_and_add_sphere(++line, scene));
	if (!ft_strncmp(line, "cy ", 3))
		return (parse_and_add_cylinder(++line, scene));
	else
		return (false);
}

bool	parse_and_add_ambient(char *line, t_scene *scene)
{
	if (scene->a != NULL)
	{
		ft_putstr_fd("Error: Ambient light can only be declared once.\n", 2);
		return (false);
	}
	while (ft_isspace(*line))
		line++;
	// printf("+++%s\n", line);
	if (!parse_ratio(&line, &scene->a->ratio))
	{
		ft_putstr_fd("Error: Ambient light's ratio is invalid\n", 2);
		ft_printf("Ambient light must have a ratio in range [0.0,1.0]\n", 1);
		return (false);
	}
	while (ft_isspace(*line))
		line++;
	// printf("---%s\n", line);
	if (!parse_color(&line, &scene->a->color))
	{
		ft_putstr_fd("Error: Ambient lightning's color is invalid\n", 2);
		ft_printf("Ambient light must have R, G, B colors in range [0-255]\n", 1);
		return (false);
	}
	while (ft_isspace(*line))
		line++;
	if (*line == '\0')
		return (true);
}

bool	parse_ratio(char **line, double *ratio)
{
	char	*tmp;
	int		i;
	float	f;

	(void)ratio;
	tmp = *line;
	if (*tmp == '\0')
		return (false);
	i = 0;
	while (!ft_isspace(tmp[i]))
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, *line, i + 1);
	// printf("tmp: %s\n", tmp);
	if (!is_float_format(tmp))
		return (false);
	f = ft_atof(tmp);
	if (f < 0.0 || f > 1.0)
		return (false);
	*ratio = f;
	free(tmp);
	*line += i;
	return (true);
}

bool	parse_color(char **line, t_color *color)
{
	
}