/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:25:55 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:46:55 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	skip_whitespace_and_commas(char **line)
{
	while (**line && (ft_isspace(**line) || **line == ','
			|| ft_isdigit(**line)))
	{
		(*line)++;
	}
}

int	parse_light(t_scene *scene, char *line)
{
	t_vec3	position;
	double	ambient_value;
	int		rgb[3];

	line++;
	if (!parse_vector(&position, &line))
		return (0);
	if (!parse_double(&ambient_value, &line))
		return (0);
	if (!get_color(&rgb[0], &rgb[1], &rgb[2], line))
		return (0);
	skip_whitespace_and_commas(&line);
	add_light(scene, position, vec3(rgb[0] / 255.0, rgb[1] / 255.0, rgb[2]
			/ 255.0), ambient_value);
	return (1);
}

int	parse_sphere(t_scene *scene, char *line)
{
	t_vec3		position;
	double		radius;
	t_sphere	*sphere;
	char		*type;
	int			rgb[3];

	line += 2;
	if (!parse_vector(&position, &line))
		return (0);
	if (!parse_double(&radius, &line))
		return (0);
	radius /= 2;
	if (!get_color(&rgb[0], &rgb[1], &rgb[2], line))
		return (0);
	skip_whitespace_and_commas(&line);
	get_string(line, &type);
	sphere = create_sphere(position, radius, get_type(type), vec3(rgb[0]
				/ 255.0, rgb[1] / 255.0, rgb[2] / 255.0));
	scene->objects = add_sphere(scene->objects, sphere);
	return (1);
}

int	parse_plane(t_scene *scene, char *line)
{
	t_vec3	position;
	t_vec3	normale;
	t_plane	*plane;
	char	*type;
	int		rgb[3];

	line += 2;
	if (!parse_vector(&position, &line))
		return (0);
	if (!parse_vector(&normale, &line))
		return (0);
	if (!get_color(&rgb[0], &rgb[1], &rgb[2], line))
		return (0);
	skip_whitespace_and_commas(&line);
	get_string(line, &type);
	plane = create_plane(position, normale, get_type(type), vec3(rgb[0] / 255.0,
				rgb[1] / 255.0, rgb[2] / 255.0));
	scene->objects = add_plane(scene->objects, plane);
	return (1);
}

int	parse_cylinder(t_scene *scene, char *line)
{
	t_cylinder	*cylinder;
	char		*type;
	int			rgb[3];

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	line += 2;
	if (!parse_vector(&cylinder->center, &line))
		return (0);
	if (!parse_vector(&cylinder->axis, &line))
		return (0);
	if (!parse_double(&cylinder->radius, &line))
		return (0);
	cylinder->radius /= 2.0;
	if (!parse_double(&cylinder->height, &line))
		return (0);
	if (!get_color(&rgb[0], &rgb[1], &rgb[2], line))
		return (0);
	skip_whitespace_and_commas(&line);
	get_string(line, &type);
	create_cylinder(cylinder, get_type(type), vec3(rgb[0] / 255.0, rgb[1]
			/ 255.0, rgb[2] / 255.0));
	scene->objects = add_cylinder(scene->objects, cylinder);
	return (1);
}
