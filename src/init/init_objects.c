/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:33:28 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/16 16:12:36 by ael-mank         ###   ########.fr       */
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

// t_object *make_box(t_object *head, t_point3 center, double height, t_material_type type, t_vec3 color) {
//     t_quad *quad;
//     double half_height = height / 2.0;

//     // Create the six faces of the cube
//     // Bottom face
//     quad = create_quad(
//         (t_point3){center.x - half_height, center.y - half_height, center.z - half_height},
//         (t_vec3){height, 0, 0},
//         (t_vec3){0, height, 0},
//         type,
// 		color
//     );
//     head = add_quad(head, quad);

//     // Top face
//     quad = create_quad(
//         (t_point3){center.x - half_height, center.y - half_height, center.z + half_height},
//         (t_vec3){height, 0, 0},
//         (t_vec3){0, height, 0},
//         type,
// 		color
//     );
//     head = add_quad(head, quad);

//     // Front face
//     quad = create_quad(
//         (t_point3){center.x - half_height, center.y - half_height, center.z - half_height},
//         (t_vec3){height, 0, 0},
//         (t_vec3){0, 0, height},
//         type,
// 		color
//     );
//     head = add_quad(head, quad);

//     // Back face
//     quad = create_quad(
//         (t_point3){center.x - half_height, center.y + half_height, center.z - half_height},
//         (t_vec3){height, 0, 0},
//         (t_vec3){0, 0, height},
//         type,
// 		color
//     );
//     head = add_quad(head, quad);

//     // Left face
//     quad = create_quad(
//         (t_point3){center.x - half_height, center.y - half_height, center.z - half_height},
//         (t_vec3){0, height, 0},
//         (t_vec3){0, 0, height},
//        type,
// 		color
//     );
//     head = add_quad(head, quad);

//     // Right face
//     quad = create_quad(
//         (t_point3){center.x + half_height, center.y - half_height, center.z - half_height},
//         (t_vec3){0, height, 0},
//         (t_vec3){0, 0, height},
//         type,
// 		color
//     );
//     head = add_quad(head, quad);

//     return head;
// }

t_object	*init_objects(void)
{
    t_object	*head;
    // t_quad		*quad;
    // t_sphere	*sphere;
	// t_triangle	*triangle;

    head = NULL;

	// Box
	// head = make_box(head, (t_point3){390, 150, 350}, 150, MATTE, (t_vec3){3, 3, 3});

	// Triangle on top in the middle 
// triangle = create_triangle(
//     (t_point3){150, 300, 100},  // Top vertex (height of 200 units above y = 200)
//     (t_point3){100, 200, 150},  // Bottom left vertex (base length of 100 units)
//     (t_point3){200, 200, 250},  // Bottom right vertex (base length of 100 units)
//     MATTE, 
//     (t_vec3){0, 1, 0.73}
// );

// head = add_triangle(head, triangle);
    return head;
}
