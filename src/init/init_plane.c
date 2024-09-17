/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:01:57 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/17 09:55:10 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*create_plane(t_point3 point, t_vec3 normal, t_material_type type,
		t_vec3 color)
{
	t_plane		*plane;
	t_material	*mat;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	mat = create_material(type);
	if (!mat)
	{
		free(plane);
		return (NULL);
	}
	mat->albedo = color;
	plane->mat = mat;
	plane->point = point;
	plane->normal = unit_vector(normal);
	plane->d = dot_product(plane->normal, point);
	return (plane);
}

inline t_object	*create_new_object(t_plane *plane)
{
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	if (!new_object || !plane)
	{
		free(new_object);
		return (NULL);
	}
	new_object->object = plane;
	new_object->mat = plane->mat;
	new_object->hit = hit_plane_wrapper;
	new_object->free = free_plane;
	new_object->next = NULL;
	return (new_object);
}

inline t_interval	get_interval(double normal_component,
		double point_component)
{
	t_interval	*plane_interval_ptr;

	plane_interval_ptr = get_plane_interval();
	if (normal_component == 0)
	{
		return (*plane_interval_ptr);
	}
	else
	{
		return (interval(point_component, point_component));
	}
}

static inline t_aabb	create_aabb(t_plane *plane)
{
	t_interval	x;
	t_interval	y;
	t_interval	z;

	x = get_interval(plane->normal.x, plane->point.x);
	y = get_interval(plane->normal.y, plane->point.y);
	z = get_interval(plane->normal.z, plane->point.z);
	return (aabb(x, y, z));
}

t_object	*add_plane(t_object *head, t_plane *plane)
{
	t_object	*new_object;

	new_object = create_new_object(plane);
	if (!new_object)
	{
		return (NULL);
	}
	new_object->box = create_aabb(plane);
	return (add_object_end(head, new_object));
}
