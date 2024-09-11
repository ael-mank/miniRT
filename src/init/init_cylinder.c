/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:43:40 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/11 18:05:53 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	cylinder_init()
{
	t_cylinder	cy;

	cy.center = vec3(0, -1, 20);
	cy.axis = vec3(-0.2, 1, 0.2);
	cy.radius = 20.0 / 2;
	cy.height = 0.5;
	cy.color = vec3(0, 1, 0.73);
	return (cy);
}

t_object	*add_cylinder(t_object *head, t_cylinder *cy)
{
	t_object	*new_object;
	t_vec3		rvec;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return (NULL);
	if (!cy)
	{
		free(new_object);
		return (NULL);
	}
	new_object->object = cy;
	// new_object->mat = sphere->mat;
	// new_object->hit = hit_sphere_wrapper;
	// new_object->free = free_sphere;
	rvec = vec3(cy->radius, cy->radius, cy->height / 2.0);
	// Assuming vector_subtract and vector_add are correctly implemented
	new_object->box = aabb_points(
		vector_subtract(cy->center, rvec),
			// Subtract radius vector from center
		vector_add(cy->center, rvec)       // Add radius vector to center
	);
	new_object->next = NULL;
	return (add_object_end(head, new_object));
}
