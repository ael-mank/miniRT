/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:31:07 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/04 14:59:02 by ael-mank         ###   ########.fr       */
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
	double	h;

	camera->v_up = vec3(0, 1, 0);
	camera->fov = 40;
	camera->defocus_angle = 0;
	camera->focus_dist = 10;
	camera->theta = deg_to_rad(camera->fov);
	h = tan(camera->theta / 2);
	camera->viewport_height = 2.0 * h * camera->focus_dist;
	camera->viewport_width = camera->viewport_height * (render->image_width
			/ (double)render->image_height);
	camera->w = unit_vector(vector_subtract(camera->lookfrom, camera->lookat));
	camera->u = unit_vector(cross_product(camera->v_up, camera->w));
	camera->v = cross_product(camera->w, camera->u);
	camera->viewport_u = vector_scale(camera->u, camera->viewport_width);
	camera->viewport_v = vector_scale(vector_scale(camera->v, -1),
			camera->viewport_height);
	camera->pixel_delta_u = vector_divide(camera->viewport_u,
			render->image_width);
	camera->pixel_delta_v = vector_divide(camera->viewport_v,
			render->image_height);
	camera->samples_per_pixel = 2;
	camera->max_depth = 25;
}
 
void	init_camera(t_camera *camera)
{
	double	defocus_radius;

	defocus_radius = camera->focus_dist * tan(deg_to_rad(camera->defocus_angle
				/ 2));
	camera->defocus_disk_u = vector_scale(camera->u, defocus_radius);
	camera->defocus_disk_v = vector_scale(camera->v, defocus_radius);
	camera->camera_center = camera->lookfrom;
	camera->viewport_upper_left = vector_subtract(
			vector_subtract(vector_subtract(camera->camera_center,
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

void	init_scene(t_scene *scene, char **argv)
{
	parse_file(scene, argv);
	scene->mouse_mode = 0;
	init_render(&scene->render);
	scene->camera.lookfrom = vec3(278, 278, -800);
	scene->camera.lookat = vec3(278, 278, 0);
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	scene->objects = init_objects();
	scene->bvh = create_bvh_node(scene->objects);
	//print_bvh_tree(scene->bvh, 0);
}
