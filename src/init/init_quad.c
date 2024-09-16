/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_quad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:58:29 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/16 16:12:08 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quad	*create_quad(t_point3 start, t_vec3 u, t_vec3 v, t_material_type type, t_vec3 color)
{
	t_quad	*quad;
	t_material	*mat;


	quad = malloc(sizeof(t_quad));
	if (!quad)
		return (NULL);
	mat = create_material(type);
	if (!mat)
	{
		free(quad);
		return (NULL);
	}
	mat->albedo = color;
	quad->mat = mat;
	quad->start = start;
	quad->u = u;
	quad->v = v;
	t_vec3 n = cross_product(u, v);
	quad->normal = unit_vector(n);
	quad->d = dot_product(quad->normal, start);
	quad->w = vector_divide(n, dot_product(n, n));
	return (quad);
}



t_object	*add_quad(t_object *head, t_quad *quad)
{
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return (NULL);
	if (!quad)
	{
		free(new_object);
		return (NULL);
	}
	new_object->object = quad;
	new_object->mat = quad->mat;
	new_object->hit = hit_quad_wrapper;
	new_object->free = free_quad;
	t_aabb bbox_diag1 = aabb_points(quad->start, vector_add(vector_add(quad->start, quad->u), quad->v));
	t_aabb bbox_diag2 = aabb_points(vector_add(quad->start, quad->u), vector_add(quad->start, quad->v));
	new_object->box = aabb_aabb(bbox_diag1, bbox_diag2);
	new_object->next = NULL;
	return (add_object_end(head, new_object));
}
