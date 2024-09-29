/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_amb_cam.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:25:37 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:26:22 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(t_scene *scene, char *line)
{
	double	ambient_value;
	int		rgb[3];

	line++;
	while (ft_isspace(*line))
		line++;
	ambient_value = ft_atof(line);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	while (ft_isspace(*line))
		line++;
	if (!get_color(&rgb[0], &rgb[1], &rgb[2], line))
		return (0);
	scene->bg_color = vec3(rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0);
	scene->bg_color = vector_scale(scene->bg_color, ambient_value);
	scene->c_and_a += 1;
	return (1);
}

int	parse_camera(t_scene *scene, char *line)
{
	t_vec3	vecs[2];
	double	params[2];

	line++;
	if (!parse_vector(&vecs[0], &line))
		return (0);
	if (!parse_vector(&vecs[1], &line))
		return (0);
	if (!parse_double(&params[0], &line))
		return (0);
	scene->camera.lookfrom = vecs[0];
	scene->camera.lookat = vecs[1];
	scene->camera.v_up = vec3(0, 1, 0);
	scene->camera.fov = params[0];
	params[1] = scene->camera.lookfrom.z / cos((scene->camera.fov / 2.0) * (M_PI
				/ 180.0) + 555);
	if (params[1] <= 0)
		params[1] = 555;
	*get_plane_interval() = (t_interval){-params[1], params[1]};
	scene->c_and_a += 1;
	return (1);
}

int	check_char(t_scene *scene, char *line)
{
	if (*line == 'A' || *line == 'a')
		return (parse_ambient(scene, line));
	else if (*line == 'c' && *(line + 1) == 'y')
		return (parse_cylinder(scene, line));
	else if (*line == 'C' || *line == 'c')
		return (parse_camera(scene, line));
	else if (*line == 'L' || *line == 'l')
		return (parse_light(scene, line));
	else if (*line == 's' && *(line + 1) == 'p')
		return (parse_sphere(scene, line));
	else if (*line == 'p' && *(line + 1) == 'l')
		return (parse_plane(scene, line));
	else if (*line == '#')
		return (1);
	else
		return (0);
}
