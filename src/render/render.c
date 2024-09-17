/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:17:54 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/17 14:19:19 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EPSILON 1e-4

t_vec3	calculate_lighting(t_hitrecord *rec, t_scene *scene)
{
	t_vec3			final_color;
	t_point_light	*light;
	t_vec3			light_dir;
	double			light_distance;
	t_ray			shadow_ray;
	t_hitrecord 	shadow_rec;
	double			diff;
	t_vec3			diffuse;

	final_color = vec3(0, 0, 0);
	ft_bzero(&shadow_rec, sizeof(t_hitrecord));
	t_vec3 material_color = rec->mat->texture(rec->mat, rec);
	light = scene->lights;
	while (light != NULL)
	{
		light_dir = vector_subtract(light->position, rec->p);
		light_distance = vector_length(light_dir);
		light_dir = vector_normalize(light_dir);
		shadow_ray = (t_ray){rec->p, light_dir};
		if (bvh_hit(scene->bvh, shadow_ray, (t_interval){0.001, light_distance},
				&shadow_rec))
		{
			light = light->next;
			continue ;
		}
		diff = fmax(0.0, dot(rec->normal, light_dir));
		diffuse = vector_scale(vector_multiply(material_color, light->color),
				diff * light->intensity);
		final_color = vector_add(final_color, diffuse);
		light = light->next;
	}
	final_color = vector_scale(final_color, 1.5);
	return (final_color);
}

t_vec3	ray_color(t_ray *r, int depth, t_bvh *bvh, t_scene *scene)
{
	t_hitrecord	rec;
	t_vec3		attenuation;
	t_ray		scattered;
	t_vec3		color_from_scatter;
	t_vec3		emission;
	t_vec3		lighting;

	if (depth <= 0)
		return (vec3(0, 0, 0));
	if (!bvh_hit(bvh, *r, universe_interval, &rec))
		return (scene->bg_color);
	if (!rec.mat->scatter(r, &rec, &attenuation, &scattered, rec.mat))
		return (rec.mat->emission(rec.mat, &rec));
	color_from_scatter = vector_multiply(attenuation, ray_color(&scattered,
				depth - 1, bvh, scene));
	emission = rec.mat->emission(rec.mat, &rec);
	lighting = calculate_lighting(&rec, scene);
	return (vector_add(vector_add(color_from_scatter, emission), lighting));
}

// t_vec3	ray_color(t_ray *r, int depth, t_bvh *bvh)
// {
// 	t_hitrecord	rec;
// 	t_vec3		unit_direction;
// 	t_vec3		attenuation;
// 	double		t;
// 	t_ray		scattered;

// 	if (depth <= 0)
// 		return (vec3(0, 0, 0));
// 	if (bvh_hit(bvh, *r, universe_interval, &rec))
// 	{
// 		if (rec.mat->scatter(r, &rec, &attenuation, &scattered, rec.mat))
// 		{
// 			return (vector_multiply(attenuation, ray_color(&scattered, depth
// 						- 1, bvh)));
// 		}
// 		return (vec3(0, 0, 0));
// 	}
// 	unit_direction = vector_normalize(r->dir);
// 	t = 0.5 * (unit_direction.y + 1.0);
// 	return (vector_add(vector_scale(vec3(1, 1, 1), 1.0 - t),
// 			vector_scale(vec3(0.5, 0.7, 1.0), t)));
// }

static inline t_vec3	defocus_disk_sample(t_camera *camera)
{
	t_vec3	p;
	t_vec3	offset;

	offset = random_in_unit_disk();
	p = vector_add(camera->camera_center,
			vector_add(vector_scale(camera->defocus_disk_u, offset.x),
				vector_scale(camera->defocus_disk_v, offset.y)));
	return (p);
}

static inline t_ray	get_ray(int i, int j, t_camera *camera)
{
	t_ray		r;
	t_vec3		offset;
	t_vec3		ray_origin;
	t_vec3		ray_dir;
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

void	render_scene(t_scene *scene)
{
	clock_t	start_time;
	clock_t	end_time;
	double	elapsed_time;

	start_time = clock();
	while (scene->rdr.j < scene->render.image_height)
	{
		scene->rdr.i = 0;
		while (scene->rdr.i < scene->render.image_width)
		{
			scene->rdr.color = vec3(0, 0, 0);
			scene->rdr.sample = 0;
			while (scene->rdr.sample < scene->camera.samples_per_pixel)
			{
				scene->rdr.r = get_ray(scene->rdr.i, scene->rdr.j,
						&scene->camera);
				scene->rdr.color = vector_add(scene->rdr.color,
						ray_color(&scene->rdr.r, scene->camera.max_depth,
							scene->bvh, scene));
				scene->rdr.sample++;
			}
			write_colors(&scene->mlx.img, scene->rdr.i, scene->rdr.j,
				scene->rdr.color);
			scene->rdr.i++;
		}
		scene->rdr.j++;
	}
	scene->rdr.j = 0;
	scene->rdr.i = 0;
	end_time = clock();
	elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("Time to render: %.10f seconds\n", elapsed_time);
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
		scene->mlx.img.img, 0, 0);
}

// static inline t_vec3	calculate_pixel_position(int i, int j, t_camera *camera)
// {
// 	t_vec3	pixel_center;

// 	pixel_center.x = camera->pixel00_loc.x + (i * camera->pixel_delta_u.x) + (j
// 			* camera->pixel_delta_v.x);
// 	pixel_center.y = camera->pixel00_loc.y + (i * camera->pixel_delta_u.y) + (j
// 			* camera->pixel_delta_v.y);
// 	pixel_center.z = camera->pixel00_loc.z + (i * camera->pixel_delta_u.z) + (j
// 			* camera->pixel_delta_v.z);
// 	return (pixel_center);
// }
// void old_render_scene(t_scene *scene) NO ANTIALIASING
// {
// 	t_vec3	color;
// 	int		sample_per_pixel;
// 	int		sample;
// 	t_vec3	pixel_center;
// 	t_vec3	ray_dir;

// 	int i, j = 0;
// 	while (j < scene->render.image_height)
// 	{
// 		i = 0;
// 		while (i < scene->render.image_width)
// 		{
// 			pixel_center = calculate_pixel_position(i, j, &scene->camera);
// 			ray_dir = vector_subtract(pixel_center,
// 					scene->camera.camera_center);
// 			ray_init(&scene->r, &scene->camera.camera_center, &ray_dir);
// 			color = ray_color(&scene->r, scene->objects);
// 			write_colors(&scene->mlx.img, i, j, color, sample_per_pixel);
// 			i++;
// 		}
// 		j++;
// 	}
// 	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
// 			scene->mlx.img.img, 50, 28);
// }