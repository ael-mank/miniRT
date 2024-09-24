/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:13:52 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/24 15:23:24 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_rt(t_scene *scene, int ac, char **av)
{
	int		fd;
	char	*element;
	bool	parse;

	element = NULL;
	parse = true;
	fd = try_open_file(ac, av);
	if (fd < 0)
		exit(1);
	element = get_next_line(fd);
	while (element != NULL)
	{
		if (parse == true)
			parse = parse_element(scene, element);
		free(element);
		element = get_next_line(fd);
	}
	close(fd);
	if (parse == false)
	{
		free_scene(scene);
		exit(1);
	}
}

int	try_open_file(int ac, char **av)
{
	int	fd;
	int	len;

	if (ac != 2 || av[1] == NULL)
	{
		ft_putstr_fd("Usage: ./miniRT *.rc\n", 2);
		exit(0);
	}
	len = ft_strlen(av[1]);
	if (ft_strnstr(av[1], ".rt", ft_strlen(av[1])) != av[1] + len - 3)
	{
		ft_putstr_fd("Error: Input must be .rc suffixed file\n", 2);
		exit(0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: ", 2);
		perror(av[1]);
	}
	return (fd);
}

bool	parse_element(t_scene *scene, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line == '\0')
		return (true);
	if (!ft_strncmp(line, "A ", 2))
		return (parse_and_add_ambient(++line, scene));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_and_add_camera(++line, scene));
	if (!ft_strncmp(line, "L ", 2))
		return (parse_and_add_light(++line, scene));
	if (!ft_strncmp(line, "pl ", 3))
		return (parse_and_add_plane(line, scene));
	if (!ft_strncmp(line, "sp ", 3))
		return (parse_and_add_sphere(line, scene));
	if (!ft_strncmp(line, "cy ", 3))
		return (parse_and_add_cylinder(line, scene));
	else
	{
		ft_putstr_fd("Error: Wrong type of element.\n", 2);
		return (false);
	}
}

bool	parse_and_add_ambient(char *line, t_scene *scene)
{
	t_ambient	*a;

	if (scene->a != NULL)
	{
		ft_putstr_fd("Error: Ambient light can only be declared once.\n", 2);
		return (false);
	}
	a = malloc(sizeof(t_ambient));
	if (a == NULL)
		return (false);
	if (!parse_ratio(&line, &a->ratio))
	{
		ft_putstr_fd("Error: Ambient light's ratio is invalid\n", 2);
		ft_putstr_fd("Ambient light must have a ratio in range [0.0,1.0]\n", 1);
		free(a);
		return (false);
	}
	if (!parse_color(&line, &a->color))
	{
		ft_putstr_fd("Error: Ambient lightning's color is invalid\n", 2);
		ft_putstr_fd("Ambient light must have R, G, B colors in range [0-255]\n", 1);
		free(a);
		return (false);
	}
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '\0')
	{
		printf("Ambient  | Ratio: %.1f | Color: %d,%d,%d\n", a->ratio,
			a->color.r, a->color.g, a->color.b);
		scene->a = a;
		return (true);
	}
	free(a);
	ft_putstr_fd("Error: Ambient light has noise information\n", 2);
	return (false);
}
