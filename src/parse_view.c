/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:13:52 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/24 20:36:10 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_element(t_scene *scene, char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '\0')
		return (true);
	if (!ft_strncmp(line, "C ", 2))
		return (parse_and_add_camera(++line, scene));
	if (!ft_strncmp(line, "A ", 2))
		return (parse_and_add_ambient(++line, scene));
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

bool	parse_and_add_camera(char *line, t_scene *scene)
{
	t_cam	*c;

	if (scene->c != NULL)
		return (err("Error: Camera ", REPETITION));
	c = malloc(sizeof(t_cam));
	if (c == NULL)
		return (false);
	if (!parse_point(&line, &c->org))
		return (free(c), err("Error: Camera's view point ", POINT));
	if (!parse_direction(&line, &c->dir))
		return (free(c), err("Error: Camera's orientation ", DIRECTION));
	if (!parse_fov(&line, &c->fov))
		return (free(c), err("Error: Camera's field of view ", FOV));
	while (*line && ft_isspace(*line))
		line++;
	if (*line != '\0')
		return (free(c), err("Error: Camera ", NOISE));
	printf("Camera   | Point: %.1f,%.1f,%.1f | Orientation: %.1f,%.1f,%.1f | "
		"FOV: %.0f\n", c->org.x, c->org.y, c->org.z, c->dir.x, c->dir.y,
		c->dir.z, c->fov);
	c->dir = vector_normalize(c->dir);
	c->theta_radian = c->fov / 2 * (PI / 180);
	init_viewport(c);
	scene->c = c;
	return (true);
}

bool	parse_fov(char **line, double *fov)
{
	char	*tmp;
	int		i;
	bool	res;

	while (**line && ft_isspace(**line))
		(*line)++;
	tmp = *line;
	if (*tmp == '\0')
		return (false);
	i = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, *line, i + 1);
	res = is_float_format(tmp);
	if (res == true)
	{
		*fov = ft_atof(tmp);
		if (*fov < 0 || *fov > 180)
			res = false;
	}
	free(tmp);
	*line += i;
	return (res);
}

void	find_viewport_dir(t_cam *cam, t_vec3 *v1, t_vec3 *v2)
{
	v1->y = 0;
	if (cam->dir.x != 0)
	{
		v1->z = 1;
		v1->x = -cam->dir.z / cam->dir.x;
	}
	else if (cam->dir.z != 0)
	{
		v1->x = 1;
		v1->z = -cam->dir.x / cam->dir.z;
	}
	else
		*v1 = vec3(1, 0, 0);
	*v2 = cross_product(cam->dir, *v1);
	if (cam->dir.z * v1->x < 0)
		*v1 = vector_scale(*v1, -1);
	if (v2->y > 0)
		*v2 = vector_scale(*v2, -1);
	*v1 = vector_normalize(*v1);
	*v2 = vector_normalize(*v2);
}

void	init_viewport(t_cam *cam)
{
	t_vec3	v1;
	t_vec3	v2;

	find_viewport_dir(cam, &v1, &v2);
	cam->v.w = F_LENGTH * tan(cam->theta_radian) * 2;
	cam->v.h = cam->v.w / ((double)LENGTH / (double)HEIGHT);
	cam->v.u = vector_scale(v1, cam->v.w);
	cam->v.v = vector_scale(v2, cam->v.h);
	cam->v.pixel_delta_u = vector_scale(cam->v.u, 1.0 / LENGTH);
	cam->v.pixel_delta_v = vector_scale(cam->v.v, 1.0 / HEIGHT);
	cam->v.upperleft = vector_subtract(vector_add(cam->org,
				vector_scale(cam->dir, F_LENGTH)),
			vector_add(vector_scale(cam->v.u, 0.5), vector_scale(cam->v.v,
					0.5)));
	cam->v.pixel00 = vector_add(cam->v.upperleft,
			vector_scale(vector_add(cam->v.pixel_delta_u, cam->v.pixel_delta_v),
				0.5));
}
