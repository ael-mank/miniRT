/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:31:07 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/09 22:19:08 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_render(t_render *render)
{
	render->aspect_ratio = 16.0 / 9.0;
	render->image_width = 860;
	render->image_height = (int)(render->image_width / render->aspect_ratio);
	if (render->image_height < 1)
		render->image_height = 1;
}

void	init_viewport(t_camera *camera, t_render *render)
{
	camera->viewport_height = 2.0;
	camera->viewport_width = camera->viewport_height * (render->image_width
			/ (double)render->image_height);
	camera->viewport_u = vec3(camera->viewport_width, 0, 0);
	camera->viewport_v = vec3(0, -camera->viewport_height, 0);
	camera->pixel_delta_u = vector_divide(camera->viewport_u,
											render->image_width);
	camera->pixel_delta_v = vector_divide(camera->viewport_v,
											render->image_height);
}

void	init_camera(t_camera *camera)
{
	camera->focal_length = 1.0;
	camera->camera_center = vec3(0, 0, 0);
	camera->viewport_upper_left.x = camera->camera_center.x
		- (camera->viewport_u.x / 2) - (camera->viewport_v.x / 2);
	camera->viewport_upper_left.y = camera->camera_center.y
		- (camera->viewport_u.y / 2) - (camera->viewport_v.y / 2);
	camera->viewport_upper_left.z = camera->camera_center.z
		- camera->focal_length - (camera->viewport_u.z / 2)
		- (camera->viewport_v.z / 2);
	camera->pixel00_loc.x = camera->viewport_upper_left.x + 0.5
		* (camera->pixel_delta_u.x + camera->pixel_delta_v.x);
	camera->pixel00_loc.y = camera->viewport_upper_left.y + 0.5
		* (camera->pixel_delta_u.y + camera->pixel_delta_v.y);
	camera->pixel00_loc.z = camera->viewport_upper_left.z + 0.5
		* (camera->pixel_delta_u.z + camera->pixel_delta_v.z);
}

//needs to be automated after by reading the .rt file
t_object	*init_objects(void)
{
	t_object	*head;
	t_object	*second;
	t_object	*third;
	t_sphere	*sphere1;
	t_sphere	*sphere2;
	t_sphere	*sphere3;

	head = malloc(sizeof(t_object));
	second = malloc(sizeof(t_object));
	third = malloc(sizeof(t_object));
	sphere1 = malloc(sizeof(t_sphere));
	sphere2 = malloc(sizeof(t_sphere));
	sphere3 = malloc(sizeof(t_sphere));
	if (!head || !second || !third || !sphere1 || !sphere2 || !sphere3)
	{
		// Handle memory allocation failure
		exit(EXIT_FAILURE);
	}
	// Initialize the first sphere
	sphere1->x = 0.0;
	sphere1->y = 0.0;
	sphere1->z = -1.0;
	sphere1->radius = 0.5;
	// Initialize the second sphere
	sphere2->x = 1.0;
	sphere2->y = 0.0;
	sphere2->z = -1.0;
	sphere2->radius = 0.5;
	// Initialize the third sphere
	sphere3->x = -1.0;
	sphere3->y = 0.0;
	sphere3->z = -1.0;
	sphere3->radius = 0.5;
	// Set up the first object
	head->object = sphere1;
	head->hit = hit_sphere;
	head->next = second;
	// Set up the second object
	second->object = sphere2;
	second->hit = hit_sphere;
	second->next = third;
	// Set up the third object
	third->object = sphere3;
	third->hit = hit_sphere;
	third->next = NULL;
	return (head);
}

void	init_scene(t_scene *scene)
{
	ft_bzero(&scene->render, sizeof(t_render));
	init_render(&scene->render);
	ft_bzero(&scene->camera, sizeof(t_camera));
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	ft_bzero(&scene->objects, sizeof(t_object));
	scene->objects = init_objects();
}