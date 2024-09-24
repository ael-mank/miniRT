/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:05:04 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/24 20:46:19 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_atof(char *s)
{
	int		integer;
	int		fraction;
	int		sign;
	double	res;

	if (!ft_strchr(s, '.'))
		return ((double)ft_atoi(s));
	sign = 1;
	integer = ft_atoi(s);
	if (*s == '-' && integer == 0)
		sign = -1;
	while (*s != '.')
		s++;
	s += 1;
	fraction = ft_atoi(s);
	res = sign * (integer + fraction / pow(10, ft_strlen(s)));
	return (res);
}

t_color	ft_atorgb(char *s)
{
	char	**parts;
	t_color	color;

	parts = ft_split(s, ',');
	color.r = ft_atoi(parts[0]);
	color.g = ft_atoi(parts[1]);
	color.b = ft_atoi(parts[2]);
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (color);
}

t_vec3	ft_atovec3(char *s)
{
	char	**parts;
	t_vec3	vec;

	parts = ft_split(s, ',');
	vec.x = ft_atof(parts[0]);
	vec.y = ft_atof(parts[1]);
	vec.z = ft_atof(parts[2]);
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (vec);
}

bool	add_to_obj_list(void *obj, t_scene *scene, t_obj_type type)
{
	t_obj	*new;
	t_obj	*node;

	new = malloc(sizeof(t_obj));
	if (!new)
		return (false);
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
	return (true);
}

void	print_cylinder(t_cylinder *cy)
{
	printf("Cylinder | Center: %.1f,%.1f,%.1f | Axis: %.1f,%.1f,%.1f | "
		"Diameter: %.1f | Height: %.1f | Color: %d,%d,%d\n",
		cy->center.x, cy->center.y, cy->center.z, cy->axis.x, cy->axis.y,
		cy->axis.z, cy->diameter, cy->height, cy->color.r, cy->color.g,
		cy->color.b);
}
