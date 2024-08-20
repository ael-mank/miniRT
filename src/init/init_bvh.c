/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:00:30 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/20 22:23:10 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*insertion_sort(t_object *head, int (*comparator)(const void *,
			const void *))
{
	t_object	*sorted;
	t_object	*current;
	t_object	*next;

	sorted = NULL;
	current = head;
	while (current)
	{
		next = current->next;
		sorted = sorted_insert(sorted, current, comparator);
		current = next;
	}
	return (sorted);
}

t_object	*sorted_insert(t_object *sorted, t_object *new_node,
		int (*comparator)(const void *, const void *))
{
	t_object	*current;

	if (!sorted || comparator(&new_node, &sorted) < 0)
	{
		new_node->next = sorted;
		return (new_node);
	}
	current = sorted;
	while (current->next && comparator(&new_node, &current->next) >= 0)
	{
		current = current->next;
	}
	new_node->next = current->next;
	current->next = new_node;
	return (sorted);
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
	node->box.hit = hit_aabb;
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
	t_object	*temp;

	if (compare_objects(&objects, &objects->next, axis) > 0)
	{
		temp = objects;
		objects = objects->next;
		objects->next = temp;
		temp->next = NULL;
	}
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
	node->left->box.hit = hit_aabb;
	node->right->box.hit = hit_aabb;
	node->left->hit = bvh_hit;
	node->right->hit = bvh_hit;
	node->box = aabb_aabb(node->left->box, node->right->box);
	node->box.hit = hit_aabb;
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
	node->box.hit = hit_aabb;
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
	{
		free(node);
		return (NULL);
	}
	axis = rand() % 3;
	if (object_count == 1)
		handle_single_object(node, objects);
	else if (object_count == 2)
	{
		if (handle_two_objects(node, objects, axis) != 0)
		{
			free(node);
			return (NULL);
		}
	}
	else
	{
		if (handle_multiple_objects(node, objects, object_count, axis) != 0)
		{
			free(node);
			return (NULL);
		}
	}
	return (node);
}
