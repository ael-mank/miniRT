/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:58:29 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/16 18:01:42 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*create_sphere(t_point3 center, double radius, t_material_type type,
		t_vec3 color)
{
	t_sphere	*sphere;
	t_material	*mat;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	mat = create_material(type);
	if (!mat)
	{
		free(sphere);
		return (NULL);
	}
	mat->albedo = color;
	sphere->mat = mat;
	sphere->center = center;
	sphere->radius = radius;
	return (sphere);
}

t_object	*add_sphere(t_object *head, t_sphere *sphere)
{
	t_object	*new_object;
	t_vec3		rvec;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return (NULL);
	if (!sphere)
	{
		free(new_object);
		return (NULL);
	}
	new_object->object = sphere;
	new_object->mat = sphere->mat;
	new_object->hit = hit_sphere_wrapper;
	new_object->free = free_sphere;
	rvec = vec3(sphere->radius, sphere->radius, sphere->radius);
	new_object->box = aabb_points(
			vector_subtract(sphere->center, rvec),
			vector_add(sphere->center, rvec));
	new_object->next = NULL;
	return (add_object_end(head, new_object));
}
