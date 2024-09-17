/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:20:49 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/17 12:01:03 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_val(int *color, char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line))
		return (0);
	*color = ft_atoi(*line);
	if (*color < 0 || *color > 255)
		return (0);
	while (ft_isdigit(**line))
		(*line)++;
	return (1);
}

int	get_color(int *r, int *g, int *b, char *line)
{
	if (!get_val(r, &line))
		return (0);
	if (*line != ',')
		return (0);
	line++;
	if (!get_val(g, &line))
		return (0);
	if (*line != ',')
		return (0);
	line++;
	if (!get_val(b, &line))
		return (0);
	return (1);
}

int	parse_ambient(t_scene *scene, char *line)
{
	char	*start;
	double	ambient_value;
	int		r;
	int		g;
	int		b;

	line++;
	while (ft_isspace(*line))
		line++;
	start = line;
	ambient_value = ft_atof(start);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	while (ft_isspace(*line))
		line++;
	if (!get_color(&r, &g, &b, line))
		return (0);
	scene->bg_color = vec3(r / 255.0, g / 255.0, b / 255.0);
	scene->bg_color = vector_scale(scene->bg_color, ambient_value);
	scene->c_and_a += 1;
	return (1);
}

int	parse_vector(t_vec3 *vec, char **line)
{
	if (!parse_double(&vec->x, line))
		return (0);
	if (**line != ',')
		return (0);
	(*line)++;
	if (!parse_double(&vec->y, line))
		return (0);
	if (**line != ',')
		return (0);
	(*line)++;
	if (!parse_double(&vec->z, line))
		return (0);
	return (1);
}

int	parse_camera(t_scene *scene, char *line)
{
	t_vec3	position;
	t_vec3	orientation;
	double	fov;

	line++;
	while (ft_isspace(*line))
		line++;
	if (!parse_vector(&position, &line))
		return (0);
	while (ft_isspace(*line))
		line++;
	if (!parse_vector(&orientation, &line))
		return (0);
	while (ft_isspace(*line))
		line++;
	if (!parse_double(&fov, &line))
		return (0);
	scene->camera.lookfrom = position;
	scene->camera.lookat = orientation;
	scene->camera.v_up = vec3(0, 1, 0);
	scene->camera.fov = fov;
	double view_distance = scene->camera.lookfrom.z / cos((scene->camera.fov / 2.0) * (M_PI / 180.0) + 555);
	if (view_distance <= 0)
		view_distance = 555;
	*get_plane_interval() = (t_interval){-view_distance, view_distance};
	scene->c_and_a += 1;
	return (1);
}
