/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:40:42 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/26 16:57:04 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180);
}

double	rand_double(double min, double max)
{
	return (min + (max - min) * random_double());
}

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

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
