/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:19:21 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 12:01:28 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	parse_cylinder_position(t_cylinder *cylinder, char **line)
{
	return (parse_position(&cylinder->center, line));
}

static inline int	parse_cylinder_vector(t_cylinder *cylinder, char **line)
{
	return (parse_vector(&cylinder->axis, line));
}

static inline void	parse_cylinder_radius_height(t_cylinder *cylinder,
		char **line)
{
	cylinder->radius = parse_radius(line) / 2.0;
	while (ft_isdigit(**line) || **line == '.')
		(*line)++;
	cylinder->height = parse_radius(line);
	while (ft_isdigit(**line) || **line == '.')
		(*line)++;
}

static inline int	parse_cylinder_color(int *r, int *g, int *b, char **line)
{
	return (parse_color(r, g, b, line));
}

int	parse_cylinder(t_scene *scene, char *line)
{
	t_cylinder	*cylinder;
	char		*type;
	int			r;
	int			g;
	int			b;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	if (!parse_cylinder_position(cylinder, &line)
		|| !parse_cylinder_vector(cylinder, &line))
		return (0);
	parse_cylinder_radius_height(cylinder, &line);
	if (!parse_cylinder_color(&r, &g, &b, &line))
		return (0);
	while (ft_isdigit(*line) || *line == ',' || ft_isspace(*line))
		line++;
	get_string(line, &type);
	create_cylinder(cylinder, get_type(type), vec3(r / 255.0, g / 255.0, b
			/ 255.0));
	free(type);
	scene->objects = add_cylinder(scene->objects, cylinder);
	return (1);
}
