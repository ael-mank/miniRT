/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:00:30 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/26 16:53:02 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	swap_objects_if_needed(t_object **objects, int axis)
{
	t_object	*temp;

	if (compare_objects(objects, &(*objects)->next, axis) > 0)
	{
		temp = *objects;
		*objects = (*objects)->next;
		(*objects)->next = temp;
		temp->next = NULL;
	}
}

int	create_bvh_nodes(t_bvh *node, t_object *objects)
{
	node->left = create_new_bvh_node();
	node->right = create_new_bvh_node();
	if (node->left == NULL || node->right == NULL)
	{
		free(node->left);
		free(node->right);
		return (-1);
	}
	node->left->object = objects;
	node->right->object = objects->next;
	node->left->left = NULL;
	node->left->right = NULL;
	node->right->left = NULL;
	node->right->right = NULL;
	node->left->box = objects->box;
	node->right->box = objects->next->box;
	node->left->hit = bvh_hit;
	node->right->hit = bvh_hit;
	node->box = aabb_aabb(node->left->box, node->right->box);
	node->hit = bvh_hit;
	node->object = NULL;
	return (0);
}

t_object	*split_list(t_object *objects, size_t mid)
{
	t_object	*current;
	t_object	*second_half;
	size_t		i;

	i = 0;
	current = objects;
	while (i < mid - 1)
	{
		current = current->next;
		i++;
	}
	second_half = current->next;
	current->next = NULL;
	return (second_half);
}

int	handle_multiple_objects(t_bvh *node, t_object *objects, size_t object_count,
		int axis)
{
	size_t		mid;
	t_object	*second_half;

	if (axis == 0)
		objects = insertion_sort(objects, compare_objects_x);
	else if (axis == 1)
		objects = insertion_sort(objects, compare_objects_y);
	else
		objects = insertion_sort(objects, compare_objects_z);
	mid = object_count / 2;
	second_half = split_list(objects, mid);
	node->left = create_bvh_node(objects);
	node->right = create_bvh_node(second_half);
	if (node->left == NULL || node->right == NULL)
	{
		free(node->left);
		free(node->right);
		return (-1);
	}
	node->box = aabb_aabb(node->left->box, node->right->box);
	node->hit = bvh_hit;
	node->object = NULL;
	return (0);
}

t_bvh	*create_bvh_node(t_object *objects)
{
	t_bvh	*node;
	size_t	object_count;
	int		axis;

	node = create_new_bvh_node();
	if (node == NULL)
		return (NULL);
	object_count = count_objects(objects);
	if (object_count == 0)
		return (free(node), NULL);
	axis = longest_axis(objects->box);
	if (object_count == 1)
		handle_single_object(node, objects);
	else if (object_count == 2)
	{
		if (handle_two_objects(node, objects, axis) != 0)
			return (free(node), NULL);
	}
	else
	{
		if (handle_multiple_objects(node, objects, object_count, axis) != 0)
			return (free(node), NULL);
	}
	return (node);
}
