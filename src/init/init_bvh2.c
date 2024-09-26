/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bvh2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:50:13 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/26 16:56:34 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	longest_axis(t_aabb box)
{
	double	x_extent;
	double	y_extent;
	double	z_extent;

	x_extent = box.x.max - box.x.min;
	y_extent = box.y.max - box.y.min;
	z_extent = box.z.max - box.z.min;
	if (x_extent > y_extent && x_extent > z_extent)
		return (0);
	else if (y_extent > z_extent)
		return (1);
	else
		return (2);
}

t_bvh	*create_new_bvh_node(void)
{
	t_bvh	*node;

	node = malloc(sizeof(t_bvh));
	if (node == NULL)
	{
		return (NULL);
	}
	return (node);
}

void	handle_single_object(t_bvh *node, t_object *objects)
{
	node->left = NULL;
	node->right = NULL;
	node->object = objects;
	node->box = objects->box;
	node->hit = bvh_hit;
}

int	compare_objects(const void *a, const void *b, int axis)
{
	if (axis == 0)
		return (box_x_compare(a, b));
	if (axis == 1)
		return (box_y_compare(a, b));
	return (box_z_compare(a, b));
}

int	handle_two_objects(t_bvh *node, t_object *objects, int axis)
{
	swap_objects_if_needed(&objects, axis);
	return (create_bvh_nodes(node, objects));
}
