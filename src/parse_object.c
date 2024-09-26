/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:02:26 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/26 13:25:44 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_and_add_ambient(char *line, t_scene *scene)
{
	t_ambient	*a;

	if (scene->a != NULL)
		return (err("Error: Ambient light ", REPETITION));
	a = malloc(sizeof(t_ambient));
	if (a == NULL)
		return (false);
	if (!parse_ratio(&line, &a->ratio))
		return (free(a), err("Error: Ambient light's ratio ", RATIO));
	if (!parse_color(&line, &a->color))
		return (free(a), err("Error: Ambient light's color ", COLOR));
	while (*line && ft_isspace(*line))
		line++;
	if (*line != '\0')
		return (free(a), err("Error: Ambient light ", NOISE));
	printf("Ambient  | Ratio: %.1f | Color: %d,%d,%d\n", a->ratio,
		a->color.r, a->color.g, a->color.b);
	scene->a = a;
	return (true);
}

bool	parse_and_add_light(char *line, t_scene *scene)
{
	t_light	*l;

	if (scene->l != NULL)
		return (err("Error: Light ", REPETITION));
	l = malloc(sizeof(t_light));
	if (l == NULL)
		return (false);
	if (!parse_point(&line, &l->org))
		return (free(l), err("Error: Light point ", POINT));
	if (!parse_ratio(&line, &l->ratio))
		return (free(l), err("Error: Light brightness ratio ", RATIO));
	if (!parse_color(&line, &l->color))
		return (free(l), err("Error: Light's color ", COLOR));
	while (*line && ft_isspace(*line))
		line++;
	if (*line != '\0')
		return (free(l), err("Error: Light ", NOISE));
	printf("Light    | Point: %.1f,%.1f,%.1f | Ratio: %.1f | "
		"Color: %d,%d,%d\n", l->org.x, l->org.y, l->org.z, l->ratio,
		l->color.r, l->color.g, l->color.b);
	scene->l = l;
	return (true);
}

bool	parse_and_add_plane(char *line, t_scene *scene)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (pl == NULL)
		return (false);
	while (*line && !ft_isspace(*line))
		line++;
	if (!parse_point(&line, &pl->point))
		return (free(pl), err("Error: Plane's point instance ", POINT));
	if (!parse_direction(&line, &pl->normal))
		return (free(pl), err("Error: Plane's normal vector ", DIRECTION));
	if (!parse_color(&line, &pl->color))
		return (free(pl), err("Error: Plane's color ", COLOR));
	while (*line && ft_isspace(*line))
		line++;
	if (*line != '\0')
		return (free(pl), err("Error: Plane ", NOISE));
	printf("Plane    | Point: %.1f,%.1f,%.1f | Normal: %.1f,%.1f,%.1f | Color:"
		" %d,%d,%d\n", pl->point.x, pl->point.y, pl->point.z, pl->normal.x,
		pl->normal.y, pl->normal.z, pl->color.r, pl->color.g, pl->color.b);
	pl->normal = vector_normalize(pl->normal);
	return (add_to_obj_list(pl, scene, PLANE));
}

bool	parse_and_add_sphere(char *line, t_scene *scene)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (sp == NULL)
		return (false);
	while (!ft_isspace(*line))
		line++;
	if (!parse_point(&line, &sp->center))
		return (free(sp), err("Error: Sphere's center ", POINT));
	if (!parse_length(&line, &sp->diameter))
		return (free(sp), err("Error: Sphere's diameter ", POS_NUM));
	if (!parse_color(&line, &sp->color))
		return (free(sp), err("Error: Sphere's color ", COLOR));
	while (*line && ft_isspace(*line))
		line++;
	if (*line != '\0')
		return (free(sp), err("Error: Sphere ", NOISE));
	printf("Sphere   | Center: %.1f,%.1f,%.1f | Diameter: %.1f | Color: "
		"%d,%d,%d\n", sp->center.x, sp->center.y, sp->center.z, sp->diameter,
		sp->color.r, sp->color.g, sp->color.b);
	sp->radius = sp->diameter / 2;
	return (add_to_obj_list(sp, scene, SPHERE));
}

bool	parse_and_add_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		return (false);
	while (*line && !ft_isspace(*line))
		line++;
	if (!parse_point(&line, &cy->center))
		return (free(cy), err("Error: Cylinder's center ", POINT));
	if (!parse_direction(&line, &cy->axis))
		return (free(cy), err("Error: Cylinder's axis ", DIRECTION));
	if (!parse_length(&line, &cy->diameter))
		return (free(cy), err("Error: Cylinder's diameter ", POS_NUM));
	if (!parse_length(&line, &cy->height))
		return (free(cy), err("Error: Cylinder's height ", POS_NUM));
	if (!parse_color(&line, &cy->color))
		return (free(cy), err("Error: Cylinder's color ", COLOR));
	while (*line && ft_isspace(*line))
		line++;
	if (*line != '\0')
		return (free(cy), err("Error: Cylinder ", NOISE));
	print_cylinder(cy);
	cy->radius = cy->diameter / 2;
	cy->axis = vector_normalize(cy->axis);
	return (add_to_obj_list(cy, scene, CYLINDER));
}
