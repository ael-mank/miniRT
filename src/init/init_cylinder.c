/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:11:43 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/27 22:24:54 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*create_cylinder(t_cylinder *cylinder, t_material_type type,
		t_vec3 color)
{
	t_material	*mat;

	mat = create_material(type);
	if (!mat)
	{
		free(cylinder);
		return (NULL);
	}
	mat->albedo = color;
	cylinder->mat = mat;
	cylinder->axis = vector_normalize(cylinder->axis);
	return (cylinder);
}

static inline t_object	*allocate_object(t_cylinder *cylinder)
{
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	if (!new_object || !cylinder)
	{
		free(new_object);
		return (NULL);
	}
	new_object->object = cylinder;
	new_object->mat = cylinder->mat;
	new_object->hit = hit_cylinder_wrapper;
	new_object->free = free_cylinder;
	new_object->next = NULL;
	return (new_object);
}

static inline void	calculate_bounding_box(t_cylinder *cylinder,
		t_object *new_object)
{
	t_vec3		half_height_vec;
	t_vec3		radius_vec;
	t_point3	min;
	t_point3	max;

	half_height_vec = vector_scale(vector_normalize(cylinder->axis),
			cylinder->height / 2.0);
	radius_vec = vec3(cylinder->radius, cylinder->radius, cylinder->radius);
	min = vector_subtract(vector_subtract(cylinder->center, half_height_vec),
			radius_vec);
	max = vector_add(vector_add(cylinder->center, half_height_vec), radius_vec);
	min = vector_min(min, vector_subtract(vector_add(cylinder->center,
					half_height_vec), radius_vec));
	max = vector_max(max, vector_add(vector_subtract(cylinder->center,
					half_height_vec), radius_vec));
	new_object->box = aabb_points(min, max);
}

t_object	*add_cylinder(t_object *head, t_cylinder *cylinder)
{
	t_object	*new_object;

	new_object = allocate_object(cylinder);
	if (!new_object)
		return (NULL);
	calculate_bounding_box(cylinder, new_object);
	return (add_object_end(head, new_object));
}
