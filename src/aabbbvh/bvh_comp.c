/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_comp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:58:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/20 21:45:03 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	box_x_compare(const void *a, const void *b)
{
	t_object	*object_a;
	t_object	*object_b;
	t_aabb		box_a;
	t_aabb		box_b;

	object_a = *(t_object **)a;
	object_b = *(t_object **)b;
	box_a = object_a->box;
	box_b = object_b->box;
	return ((box_a.x.min - box_b.x.min) < 0.0);
}

int	box_y_compare(const void *a, const void *b)
{
	t_object	*object_a;
	t_object	*object_b;
	t_aabb		box_a;
	t_aabb		box_b;

	object_a = *(t_object **)a;
	object_b = *(t_object **)b;
	box_a = object_a->box;
	box_b = object_b->box;
	return ((box_a.y.min - box_b.y.min) < 0.0);
}

int	box_z_compare(const void *a, const void *b)
{
	t_object	*object_a;
	t_object	*object_b;
	t_aabb		box_a;
	t_aabb		box_b;

	object_a = *(t_object **)a;
	object_b = *(t_object **)b;
	box_a = object_a->box;
	box_b = object_b->box;
	return ((box_a.z.min - box_b.z.min) < 0.0);
}

size_t	count_objects(t_object *objects)
{
	size_t	count;

	count = 0;
	while (objects)
	{
		count++;
		objects = objects->next;
	}
	return (count);
}
