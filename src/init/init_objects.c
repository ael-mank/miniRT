/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:33:28 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/25 11:05:05 by ael-mank         ###   ########.fr       */
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
    t_quad		*quad;
    t_sphere	*sphere;

    head = NULL;

    // Quads
    quad = create_quad((t_point3){555, 0, 0}, (t_vec3){0, 555, 0}, (t_vec3){0, 0, 555}, MATTE, (t_vec3){0.12, 0.45, 0.15});
    head = add_quad(head, quad);

    quad = create_quad((t_point3){0, 0, 0}, (t_vec3){0, 555, 0}, (t_vec3){0, 0, 555}, MATTE, (t_vec3){0.65, 0.05, 0.05});
    head = add_quad(head, quad);

    quad = create_quad((t_point3){0, 0, 0}, (t_vec3){555, 0, 0}, (t_vec3){0, 0, 555}, MATTE, (t_vec3){0.73, 0.73, 0.73});
    head = add_quad(head, quad);

    quad = create_quad((t_point3){0, 555, 0}, (t_vec3){555, 0, 0}, (t_vec3){0, 0, 555}, MATTE, (t_vec3){0.73, 0.73, 0.73});
    head = add_quad(head, quad);

    quad = create_quad((t_point3){0, 0, 555}, (t_vec3){555, 0, 0}, (t_vec3){0, 555, 0}, MATTE, (t_vec3){0.94, 0.92, 0.84});
    head = add_quad(head, quad);

    // Back Plane
    // quad = create_quad((t_point3){0, 0, 0}, (t_vec3){555, 0, 0}, (t_vec3){0, 555, 0}, MATTE, (t_vec3){0.73, 0.73, 0.73});
    // head = add_quad(head, quad);
    
    sphere = create_sphere((t_point3){200, 100, 200}, 100, METAL, (t_vec3){0.7, 0.6, 0.5});
    head = add_sphere(head, sphere);

    return head;
}
