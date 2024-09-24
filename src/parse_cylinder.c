/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:19:29 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/24 15:19:45 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_and_add_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		return (false);
	while (!ft_isspace(*line))
		line++;
	if (!parse_point(&line, &cy->center))
	{
		ft_putstr_fd("Error: Cylinder's center is invalid\n", 2);
		free(cy);
		return (false);
	}
	if (!parse_direction(&line, &cy->axis))
	{
		ft_putstr_fd("Error: Cylinder's axis is invalid\n", 2);
		ft_putstr_fd("Axis must have x, y, z in range [-1,1]\n", 1);
		free(cy);
		return (false);
	}
	if (!parse_length(&line, &cy->diameter))
	{
		ft_putstr_fd("Error: Cylinder's diameter is invalid\n", 2);
		ft_putstr_fd("Diameter must be positive numeric value\n", 1);
		free(cy);
		return (false);
	}
	if (!parse_length(&line, &cy->height))
	{
		ft_putstr_fd("Error: Cylinder's height is invalid\n", 2);
		ft_putstr_fd("Height must be positive numeric value\n", 1);
		free(cy);
		return (false);
	}
	if (!parse_color(&line, &cy->color))
	{
		ft_putstr_fd("Error: Cylinder's color is invalid\n", 2);
		ft_putstr_fd("Color must have R, G, B values in range [0-255]\n", 1);
		free(cy);
		return (false);
	}
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '\0')
	{
		printf("Cylinder | Center: %.1f,%.1f,%.1f | Axis: %.1f,%.1f,%.1f | Diameter: %.1f | Height: %.1f | Color: %d,%d,%d\n",
			cy->center.x, cy->center.y, cy->center.z, cy->axis.x, cy->axis.y,
			cy->axis.z, cy->diameter, cy->height, cy->color.r, cy->color.g,
			cy->color.b);
		cy->radius = cy->diameter / 2;
		cy->axis = vector_normalize(cy->axis);
		add_to_obj_list(cy, scene, CYLINDER);
		return (true);
	}
	free(cy);
	ft_putstr_fd("Error: Cylinder has noise information\n", 2);
	return (false);
}
