/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:33:28 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/20 17:19:27 by ael-mank         ###   ########.fr       */
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
    sphere = create_sphere(vec3(0, -1000, -1), 1000, MATTE, vec3(0.8, 0.8, 0.0));
    head = add_sphere(head, sphere);
    sphere = create_sphere(vec3(0, 1, 0), 1.0, GLASS, vec3(1.0, 1.0, 1.0));
    head = add_sphere(head, sphere);
    sphere = create_sphere(vec3(0, 1, 0), 0.9, BUBBLE, vec3(1.0, 1.0, 1.0));
    head = add_sphere(head, sphere);
    sphere = create_sphere(vec3(-4, 1, 0), 1, MATTE, vec3(0.4, 0.2, 0.1));
    head = add_sphere(head, sphere);
    sphere = create_sphere(vec3(4, 1, 0), 1, METAL, vec3(0.7, 0.6, 0.5));
    head = add_sphere(head, sphere);

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double choose_mat = random_double();
            t_vec3 center = vec3(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if (sqrt(pow(center.x - 4, 2) + pow(center.y - 0.2, 2) + pow(center.z, 2)) > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    // Diffuse
                    t_vec3 albedo = vec3(random_double(), random_double(), random_double());
                    albedo = vec3(albedo.x * random_double(), albedo.y * random_double(), albedo.z * random_double());
                    sphere = create_sphere(center, 0.2, MATTE, albedo);
                    head = add_sphere(head, sphere);
                }
                else if (choose_mat < 0.95)
                {
                    // Metal
                    t_vec3 albedo = vec3(0.5 + 0.5 * random_double(), 0.5 + 0.5 * random_double(), 0.5 + 0.5 * random_double());
                    sphere = create_sphere(center, 0.2, METAL, albedo);
                    head = add_sphere(head, sphere);
                }
                else
                {
                    // Glass
                    sphere = create_sphere(center, 0.2, GLASS, vec3(1.0, 1.0, 1.0));
                    head = add_sphere(head, sphere);
                }
            }
        }
    }
    return (head);
}
