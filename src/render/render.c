/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:17:54 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/13 20:00:05 by ael-mank         ###   ########.fr       */
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

void	set_face_normal_tri(t_hitrecord *rec, t_ray *r, t_vec3 v0, t_vec3 v1, t_vec3 v2, double root)
{
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	rec->normal = vector_normalize(cross_product(vector_subtract(v1, v0), vector_subtract(v2, v0)));
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
int hit_triangle(t_ray *r, t_vec3 v0, t_vec3 v1, t_vec3 v2, t_interval ray_t, t_hitrecord *rec, t_material *mat) {
    t_vec3 edge1, edge2, h, s, q;
    double a, f, u, v, t;

    edge1 = vector_subtract(v1, v0);
    edge2 = vector_subtract(v2, v0);
    h = cross_product(r->dir, edge2);
    a = dot(edge1, h);
    if (a > -0.000001 && a < 0.000001)
        return 0; // This ray is parallel to this triangle.

    f = 1.0 / a;
    s = vector_subtract(r->org, v0);
    u = f * dot(s, h);
    if (u < 0.0 || u > 1.0)
        return 0;

    q = cross_product(s, edge1);
    v = f * dot(r->dir, q);
    if (v < 0.0 || u + v > 1.0)
        return 0;

    t = f * dot(edge2, q);
    if (t < ray_t.min || t > ray_t.max)
        return 0;

    rec->t = t;
    rec->p = ray_at(r, t);
    rec->normal = vector_normalize(cross_product(edge1, edge2));
    set_face_normal_tri(rec, r, v0, v1, v2, t);
    rec->mat = mat; // Ensure the material is set correctly
    return 1;
}
				
double hit_pyramid(t_ray r, t_pyramid pyramid, t_interval ray_t, t_hitrecord *rec) {
    int hit_anything = 0;
    double closest_so_far = ray_t.max;

    // Check intersection with each triangular face
    for (int i = 0; i < 4; i++) {
        if (hit_triangle(&r, pyramid.vertices[i], pyramid.vertices[(i + 1) % 4], pyramid.apex, ray_t, rec, pyramid.mat)) {
            hit_anything = 1;
            closest_so_far = rec->t;
            ray_t.max = closest_so_far; // Update the interval max to the closest hit
        }
    }

    // Check intersection with the base (assuming it's a quadrilateral)
    if (hit_triangle(&r, pyramid.vertices[0], pyramid.vertices[1], pyramid.vertices[2], ray_t, rec, pyramid.mat)) {
        hit_anything = 1;
        closest_so_far = rec->t;
        ray_t.max = closest_so_far; // Update the interval max to the closest hit
    }
    if (hit_triangle(&r, pyramid.vertices[0], pyramid.vertices[2], pyramid.vertices[3], ray_t, rec, pyramid.mat)) {
        hit_anything = 1;
        closest_so_far = rec->t;
        ray_t.max = closest_so_far; // Update the interval max to the closest hit
    }

    return hit_anything;
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