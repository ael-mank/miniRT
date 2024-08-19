/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:33:28 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/19 10:48:31 by ael-mank         ###   ########.fr       */
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

t_object	*init_objects(void)
{
	t_object	*head;
	t_sphere	*sphere;

	head = NULL;
	sphere = create_sphere(vec3(0, -1000, -1), 1000, MATTE, vec3(0.8, 0.8,
				0.0));
	head = add_sphere(head, sphere);
	sphere = create_sphere(vec3(0, 1, 0), 1.0, GLASS, vec3(1.0, 1.0, 1.0));
	head = add_sphere(head, sphere);
	sphere = create_sphere(vec3(0, 1, 0), 0.9, BUBBLE, vec3(1.0, 1.0, 1.0));
	head = add_sphere(head, sphere);
	sphere = create_sphere(vec3(-4, 1, 0), 1, MATTE, vec3(0.4, 0.2, 0.1));
	head = add_sphere(head, sphere);
	sphere = create_sphere(vec3(4, 1, 0), 1, METAL, vec3(0.7, 0.6, 0.5));
	head = add_sphere(head, sphere);
	return (head);
}
