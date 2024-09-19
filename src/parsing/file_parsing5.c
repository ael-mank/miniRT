/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:19:21 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/19 19:42:18 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cylinder(t_scene *scene, char *line)
{
	t_cylinder      *cylinder;
	t_point3		center;
	t_vec3			axis;
	double 			diameter;
	double 			height;
	char			*type;

	int			r, g, b;
	if (!parse_position(&center, &line))
		return (0);
	if (!parse_vector(&axis, &line))
		return (0);
	diameter = parse_radius(&line);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	height = parse_radius(&line);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	if (!parse_color(&r, &g, &b, &line))
		return (0);
	while (ft_isdigit(*line) || *line == ',' || ft_isspace(*line))
		line++;
	get_string(line, &type);
	cylinder = create_cylinder(center, axis, diameter, height, get_type(type), vec3(r/255.0, g/255.0, b/255.0));
	free(type);
	scene->objects = add_cylinder(scene->objects, cylinder);
	return (1);
}
