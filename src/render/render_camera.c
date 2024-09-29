/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:52:46 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:52:49 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_vec3	defocus_disk_sample(t_camera *camera)
{
	t_vec3	offset;

	offset = random_in_unit_disk();
	return (vector_add(camera->camera_center,
			vector_add(vector_scale(camera->defocus_disk_u, offset.x),
				vector_scale(camera->defocus_disk_v, offset.y))));
}

t_ray	get_ray(int i, int j, t_camera *camera)
{
	t_vec3		offset;
	t_vec3		ray_origin;
	t_vec3		ray_dir;
	t_ray		r;
	t_point3	pixel_sample;

	offset = sample_square();
	pixel_sample = vector_add(camera->pixel00_loc,
			vector_add(vector_scale(camera->pixel_delta_u, i + offset.x),
				vector_scale(camera->pixel_delta_v, j + offset.y)));
	if (camera->defocus_angle <= 0)
		ray_origin = camera->camera_center;
	else
		ray_origin = defocus_disk_sample(camera);
	ray_dir = vector_subtract(pixel_sample, ray_origin);
	ray_init(&r, &ray_origin, &ray_dir);
	return (r);
}
