/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:33:28 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/26 16:01:38 by ael-mank         ###   ########.fr       */
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

t_object *make_box(t_object *head, t_point3 center, double height, t_material_type type, t_vec3 color) {
    t_quad *quad;
    double half_height = height / 2.0;

    // Create the six faces of the cube
    // Bottom face
    quad = create_quad(
        (t_point3){center.x - half_height, center.y - half_height, center.z - half_height},
        (t_vec3){height, 0, 0},
        (t_vec3){0, height, 0},
        type,
		color
    );
    head = add_quad(head, quad);

    // Top face
    quad = create_quad(
        (t_point3){center.x - half_height, center.y - half_height, center.z + half_height},
        (t_vec3){height, 0, 0},
        (t_vec3){0, height, 0},
        type,
		color
    );
    head = add_quad(head, quad);

    // Front face
    quad = create_quad(
        (t_point3){center.x - half_height, center.y - half_height, center.z - half_height},
        (t_vec3){height, 0, 0},
        (t_vec3){0, 0, height},
        type,
		color
    );
    head = add_quad(head, quad);

    // Back face
    quad = create_quad(
        (t_point3){center.x - half_height, center.y + half_height, center.z - half_height},
        (t_vec3){height, 0, 0},
        (t_vec3){0, 0, height},
        type,
		color
    );
    head = add_quad(head, quad);

    // Left face
    quad = create_quad(
        (t_point3){center.x - half_height, center.y - half_height, center.z - half_height},
        (t_vec3){0, height, 0},
        (t_vec3){0, 0, height},
       type,
		color
    );
    head = add_quad(head, quad);

    // Right face
    quad = create_quad(
        (t_point3){center.x + half_height, center.y - half_height, center.z - half_height},
        (t_vec3){0, height, 0},
        (t_vec3){0, 0, height},
        type,
		color
    );
    head = add_quad(head, quad);

    return head;
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

	// Spotlight
	quad = create_quad((t_point3){343, 554, 332}, (t_vec3){-130, 0, 0}, (t_vec3){0, 0, 150}, LIGHT, (t_vec3){17, 17, 17});
	head = add_quad(head, quad);
	
	quad = create_quad((t_point3){0, 0, 0}, (t_vec3){555, 0, 0}, (t_vec3){0, 0, 555}, MATTE, (t_vec3){0.73, 0.73, 0.73});
    head = add_quad(head, quad);

    quad = create_quad((t_point3){0, 555, 0}, (t_vec3){555, 0, 0}, (t_vec3){0, 0, 555}, MATTE, (t_vec3){0.73, 0.73, 0.73});
    head = add_quad(head, quad);

    quad = create_quad((t_point3){0, 0, 555}, (t_vec3){555, 0, 0}, (t_vec3){0, 555, 0}, MATTE, (t_vec3){0.0, 0.0, 1.0});
    head = add_quad(head, quad);

    // // Back Plane
    // quad = create_quad((t_point3){0, 0, 0}, (t_vec3){555, 0, 0}, (t_vec3){0, 555, 0}, MATTE, (t_vec3){0.73, 0.73, 0.73});
    // head = add_quad(head, quad);
    
    sphere = create_sphere((t_point3){200, 100, 265}, 100, METAL, (t_vec3){0.7, 0.7, 0.7});
    head = add_sphere(head, sphere);

	// sphere = create_sphere((t_point3){400, 100, 400}, 100, METAL, (t_vec3){1, 1, 1});
	// head = add_sphere(head, sphere);

	// Box
	head = make_box(head, (t_point3){380, 150, 350}, 150, LIGHT, (t_vec3){3, 3, 3});
    return head;
}
