/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:33:28 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/26 16:54:42 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*add_object_end(t_object *head, t_object *new_object)
{
	t_object	*current;

	current = head;
	if (!head)
	{
		head = new_object;
		return (head);
	}
	while (current->next)
		current = current->next;
	current->next = new_object;
	return (head);
}
