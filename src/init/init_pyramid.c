/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pyramid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:59:35 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/19 10:46:47 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"

// double	hit_pyramid_wrapper(t_ray r, void *object, t_interval ray_t,
// 		t_hitrecord *rec)
// {
// 	return (hit_pyramid(r, *(t_pyramid *)object, ray_t, rec));
// }

// t_material	*init_material(t_material_type type, t_vec3 color)
// {
// 	t_material	*mat;

// 	mat = create_material(type);
// 	if (!mat)
// 		return (NULL);
// 	mat->albedo = color;
// 	return (mat);
// }

// t_pyramid	*init_pyramid_data(t_vec3 base_vertices[4], t_vec3 apex,
// 		t_material *mat)
// {
// 	t_pyramid	*pyramid_data;
// 	int			i;

// 	i = -1;
// 	pyramid_data = malloc(sizeof(t_pyramid));
// 	if (!pyramid_data)
// 		return (NULL);
// 	while (++i < 4)
// 		pyramid_data->vertices[i] = base_vertices[i];
// 	pyramid_data->apex = apex;
// 	pyramid_data->mat = mat;
// 	return (pyramid_data);
// }

// t_object	*init_object(void *data, t_material *mat)
// {
// 	t_object	*new_object;

// 	new_object = malloc(sizeof(t_object));
// 	if (!new_object)
// 		return (NULL);
// 	new_object->object = data;
// 	new_object->mat = mat;
// 	new_object->hit = hit_pyramid_wrapper;
// 	new_object->next = NULL;
// 	return (new_object);
// }

// t_object	*create_pyramid(t_vec3 base_vertices[4], t_vec3 apex,
// 		t_material_type type, t_vec3 color)
// {
// 	t_material	*mat;
// 	t_pyramid	*pyramid_data;
// 	t_object	*new_object;

// 	mat = init_material(type, color);
// 	if (!mat)
// 		return (NULL);
// 	pyramid_data = init_pyramid_data(base_vertices, apex, mat);
// 	if (!pyramid_data)
// 	{
// 		free(mat);
// 		return (NULL);
// 	}
// 	new_object = init_object(pyramid_data, mat);
// 	if (!new_object)
// 	{
// 		free(pyramid_data);
// 		free(mat);
// 		return (NULL);
// 	}
// 	return (new_object);
// }

// t_object	*add_pyramid(t_object *head, t_vec3 center, float height,
// 		t_material_type material, t_vec3 color)
// {
// 	float		half_side;
// 	t_vec3		apex;
// 	t_object	*new_pyramid;
// 	t_vec3		base_vertices[4];

// 	base_vertices[0] = vec3(center.x - half_side, center.y, center.z
// 			- half_side);
// 	base_vertices[1] = vec3(center.x + half_side, center.y, center.z
// 			- half_side);
// 	base_vertices[2] = vec3(center.x + half_side, center.y, center.z
// 			+ half_side);
// 	base_vertices[3] = vec3(center.x - half_side, center.y, center.z
// 			+ half_side);
// 	half_side = 0.5;
// 	apex = vec3(center.x, center.y + height, center.z);
// 	new_pyramid = create_pyramid(base_vertices, apex, material, color);
// 	if (!new_pyramid)
// 		return (NULL);
// 	return (add_object_end(head, new_pyramid));
// }
