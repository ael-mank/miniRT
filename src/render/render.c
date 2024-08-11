/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:17:54 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/11 21:56:21 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_hitrecord *rec, t_ray *r, t_sphere sphere,
		double root)
{
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	rec->normal = vector_divide(vector_subtract(rec->p, sphere.center),
								sphere.radius);
	rec->front_face = dot(r->dir, rec->normal) < 0;
}

double	hit_sphere(t_ray r, t_sphere sphere, t_interval ray_t, t_hitrecord *rec)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;

	oc = vector_subtract(sphere.center, r.org);
	a = vector_length_squared(r.dir);
	h = dot(r.dir, oc);
	c = vector_length_squared(oc) - sphere.radius * sphere.radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (h - sqrtd) / a;
	if (!surrond(ray_t, (t_interval){root, root}))
	{
		root = (h + sqrtd) / a;
		if (!surrond(ray_t, (t_interval){root, root}))
			return (0);
	}
	set_face_normal(rec, &r, sphere, root);
	rec->mat = sphere.mat;
	rec->mat->albedo = sphere.mat->albedo;
	return (1);
}

double	hit(t_ray r, t_object *objects, t_interval ray_t, t_hitrecord *rec)
{
	t_hitrecord	temp_rec;
	int			hit_anything;
	double		closest_so_far;

	hit_anything = 0;
	closest_so_far = ray_t.max;
	while (objects)
	{
		if (objects->hit(r, objects->object, ray_t, &temp_rec))
		{
			hit_anything = 1;
			if (temp_rec.t < closest_so_far)
			{
				closest_so_far = temp_rec.t;
				*rec = temp_rec;
			}
		}
		objects = objects->next;
	}
	return (hit_anything);
}

int lambertian_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_vec3 albedo)
{
	(void)r;
    t_vec3 direction;

    direction = vector_add(rec->normal, random_unit_vector());
	
	if (near_zero(direction))
		direction = rec->normal;
    ray_init(scattered, &rec->p, &direction);
    *attenuation = albedo;
    return (1);
}

int metal_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_vec3 albedo)
{
    t_vec3 direction;

    direction = reflect(vector_normalize(r->dir), rec->normal);
    ray_init(scattered, &rec->p, &direction);
    *attenuation = albedo;
    return (1);
}

t_vec3 ray_color(t_ray *r, int depth, t_object *objects)
{
    t_hitrecord rec;
    t_vec3 unit_direction;
    t_vec3 white;
    t_vec3 blue;
    t_vec3 attenuation;
    double t;
    t_ray scattered;

    white = vec3(1, 1, 1);
    blue = vec3(0.5, 0.7, 1.0);
    if (depth <= 0)
    {
        return (vec3(0, 0, 0));
    }
    if (hit(*r, objects, universe_interval, &rec))
    {
        if (rec.mat->scatter(r, &rec, &attenuation, &scattered, rec.mat->albedo))
        {
            return (vector_multiply(attenuation, ray_color(&scattered, depth - 1, objects)));
        }
        return (vec3(0, 0, 0));
    }
    unit_direction = vector_normalize(r->dir);
    t = 0.5 * (unit_direction.y + 1.0);
    return (vector_add(vector_scale(white, 1.0 - t), vector_scale(blue, t)));
}

t_vec3	calculate_pixel_position(int i, int j, t_camera *camera)
{
	t_vec3	pixel_center;

	pixel_center.x = camera->pixel00_loc.x + (i * camera->pixel_delta_u.x) + (j
			* camera->pixel_delta_v.x);
	pixel_center.y = camera->pixel00_loc.y + (i * camera->pixel_delta_u.y) + (j
			* camera->pixel_delta_v.y);
	pixel_center.z = camera->pixel00_loc.z + (i * camera->pixel_delta_u.z) + (j
			* camera->pixel_delta_v.z);
	return (pixel_center);
}

t_vec3	sample_square(void)
{
	return (vec3(random_double() - 0.5, random_double() - 0.5, 0));
}

t_ray	get_ray(int i, int j, t_camera *camera)
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
	ray_origin = camera->camera_center;
	ray_dir = vector_subtract(pixel_sample, camera->camera_center);
	ray_init(&r, &ray_origin, &ray_dir);
	return (r);
}

void	render_scene(t_scene *scene)
{
	t_vec3	color;
	int		sample;
	t_ray	r;
	clock_t	start_time;
	clock_t	end_time;
	double	elapsed_time;

	sample = 0;
	int i, j = 0;
	start_time = clock();
	while (j < scene->render.image_height)
	{
		i = 0;
		while (i < scene->render.image_width)
		{
			color = vec3(0, 0, 0);
			sample = 0;
			while (sample < scene->camera.samples_per_pixel)
			{
				r = get_ray(i, j, &scene->camera);
				color = vector_add(color, ray_color(&r, scene->camera.max_depth,
							scene->objects));
				sample++;
			}
			write_colors(&scene->mlx.img, i, j, color,
					scene->camera.samples_per_pixel);
			i++;
		}
		mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
			scene->mlx.img.img, 50, 28);
		j++;
	}
	end_time = clock();
	elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("Time to render: %.2f seconds\n", elapsed_time);
}

// void old_render_scene(t_scene *scene)
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