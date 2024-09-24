/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:22:04 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/24 15:22:11 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_and_add_plane(char *line, t_scene *scene)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (pl == NULL)
		return (false);
	while (!ft_isspace(*line))
		line++;
	if (!parse_point(&line, &pl->point))
	{
		ft_putstr_fd("Error: The point in the plane is invalid\n", 2);
		free(pl);
		return (false);
	}
	if (!parse_direction(&line, &pl->normal))
	{
		ft_putstr_fd("Error: The normal vector of the plane is invalid\n", 2);
		ft_putstr_fd("Normal vector must have x, y, z in range [-1,1]\n", 1);
		free(pl);
		return (false);
	}
	if (!parse_color(&line, &pl->color))
	{
		ft_putstr_fd("Error: Plane's color is invalid\n", 2);
		ft_putstr_fd("Color must have R, G, B values in range [0-255]\n", 1);
		free(pl);
		return (false);
	}
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '\0')
	{
		printf("Plane    | Point: %.1f,%.1f,%.1f | Normal: %.1f,%.1f,%.1f | Color: %d,%d,%d\n", pl->point.x, pl->point.y,
			pl->point.z, pl->normal.x, pl->normal.y, pl->normal.z, pl->color.r,
			pl->color.g, pl->color.b);
		add_to_obj_list(pl, scene, PLANE);
		return (true);
	}
	free(pl);
	ft_putstr_fd("Error: Plane has noise information\n", 2);
	return (false);
}

void	add_to_obj_list(void *obj, t_scene *scene, t_obj_type type)
{
	t_obj	*new;
	t_obj	*node;

	new = malloc(sizeof(t_obj));
	if (!new)
		return ;
	new->type = type;
	new->obj = obj;
	new->next = NULL;
	if (scene->objs == NULL)
		scene->objs = new;
	else
	{
		node = scene->objs;
		while (node->next)
			node = node->next;
		node->next = new;
	}
}
