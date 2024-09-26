/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:31:07 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/26 13:33:53 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_render(t_render *render)
{
	render->aspect_ratio = 16.0 / 9.0;
	render->image_width = 960;
	render->image_height = (int)(render->image_width / render->aspect_ratio);
	if (render->image_height < 1)
		render->image_height = 1;
}

void	init_viewport(t_camera *camera, t_render *render)
{
	double	aspect_ratio;
	double	h;

	camera->defocus_angle = 0;
	camera->focus_dist = 10;
	camera->theta = deg_to_rad(camera->fov);
	aspect_ratio = render->image_width / (double)render->image_height;
	h = tan(camera->theta / 2);
	camera->viewport_width = 2.0 * h * camera->focus_dist;
	camera->viewport_height = camera->viewport_width / aspect_ratio;
	camera->w = vector_scale(camera->lookat, -1);
	camera->u = cross_product(camera->w, camera->v_up);
	camera->v = cross_product(camera->u, camera->w);
	camera->viewport_u = vector_scale(camera->u, camera->viewport_width);
	camera->viewport_v = vector_scale(vector_scale(camera->v, -1),
			camera->viewport_height);
	camera->pixel_delta_u = vector_divide(camera->viewport_u,
			render->image_width);
	camera->pixel_delta_v = vector_divide(camera->viewport_v,
			render->image_height);
	camera->samples_per_pixel = SPP;
	printf("Samples per pixel: %d\n", camera->samples_per_pixel);
	camera->max_depth = MD;
	printf("Max depth: %d\n", camera->max_depth);
}

void	init_camera(t_camera *camera)
{
	double	defocus_radius;

	defocus_radius = camera->focus_dist * tan(deg_to_rad(camera->defocus_angle
				/ 2));
	camera->defocus_disk_u = vector_scale(camera->u, defocus_radius);
	camera->defocus_disk_v = vector_scale(camera->v, defocus_radius);
	camera->camera_center = camera->lookfrom;
	camera->viewport_upper_left = vector_subtract(vector_subtract(vector_subtract(camera->camera_center,
					vector_scale(camera->w, camera->focus_dist)),
				vector_divide(camera->viewport_u, 2)),
			vector_divide(camera->viewport_v, 2));
	camera->pixel00_loc.x = camera->viewport_upper_left.x + 0.5
		* (camera->pixel_delta_u.x + camera->pixel_delta_v.x);
	camera->pixel00_loc.y = camera->viewport_upper_left.y + 0.5
		* (camera->pixel_delta_u.y + camera->pixel_delta_v.y);
	camera->pixel00_loc.z = camera->viewport_upper_left.z + 0.5
		* (camera->pixel_delta_u.z + camera->pixel_delta_v.z);
}

void	add_light(t_scene *scene, t_vec3 position, t_vec3 color,
		double intensity)
{
	t_point_light	*new_light;

	new_light = malloc(sizeof(t_point_light));
	new_light->position = position;
	new_light->color = color;
	new_light->intensity = intensity;
	new_light->next = scene->lights;
	scene->lights = new_light;
	scene->num_lights++;
}

void	init_scene(t_scene *scene, char **argv)
{
	scene->num_lights = 0;
	scene->objects = NULL;
	parse_file(scene, argv);
	init_render(&scene->render);
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	scene->bvh = create_bvh_node(scene->objects);
}
