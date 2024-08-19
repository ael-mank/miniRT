/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:58:29 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/19 08:18:18 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_sphere(r, *(t_sphere *)object, ray_t, rec));
}

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

// Function to add a sphere to the object list
t_object	*add_sphere(t_object *head, t_sphere *sphere)
{
	t_object	*new_object;

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
	new_object->center = sphere->center;
	new_object->hit = hit_sphere_wrapper;
	new_object->next = NULL;
	return (add_object_end(head, new_object));
}
