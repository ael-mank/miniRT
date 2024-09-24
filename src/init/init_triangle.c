/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:58:29 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/24 16:00:23 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	create_triangle_aabb(t_triangle *triangle)
{
	t_point3(min_point) = {fmin(fmin(triangle->v0.x, triangle->v1.x),
			triangle->v2.x), fmin(fmin(triangle->v0.y, triangle->v1.y),
			triangle->v2.y), fmin(fmin(triangle->v0.z, triangle->v1.z),
			triangle->v2.z)};
	t_point3(max_point) = {fmax(fmax(triangle->v0.x, triangle->v1.x),
			triangle->v2.x), fmax(fmax(triangle->v0.y, triangle->v1.y),
			triangle->v2.y), fmax(fmax(triangle->v0.z, triangle->v1.z),
			triangle->v2.z)};
	return (aabb_points(min_point, max_point));
}

t_triangle	*create_triangle(t_tri3 tri, t_material_type type, t_vec3 color)
{
	t_triangle	*triangle;
	t_material	*mat;
	t_vec3		n;

	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		return (NULL);
	mat = create_material(type);
	if (!mat)
	{
		free(triangle);
		return (NULL);
	}
	mat->albedo = color;
	triangle->mat = mat;
	triangle->v0 = tri.v0;
	triangle->v1 = tri.v1;
	triangle->v2 = tri.v2;
	n = cross_product(vector_subtract(tri.v1, tri.v0), vector_subtract(tri.v2,
				tri.v0));
	triangle->normal = unit_vector(n);
	triangle->d = dot_product(triangle->normal, tri.v0);
	return (triangle);
}

t_object	*add_triangle(t_object *head, t_triangle *triangle)
{
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return (NULL);
	if (!triangle)
	{
		free(new_object);
		return (NULL);
	}
	new_object->object = triangle;
	new_object->mat = triangle->mat;
	new_object->hit = hit_triangle_wrapper;
	new_object->free = free_triangle;
	new_object->box = create_triangle_aabb(triangle);
	new_object->next = NULL;
	return (add_object_end(head, new_object));
}
