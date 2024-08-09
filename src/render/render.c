/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:17:54 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/09 23:09:05 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(t_vec3 center, double radius, t_ray r)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;

	oc = vector_subtract(center, r.org);
	a = vector_length_squared(r.dir);
	h = dot(r.dir, oc);
	c = vector_length_squared(oc) - radius * radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
	{
		return (-1.0);
	}
	else
	{
		return ((h - sqrt(discriminant)) / a);
	}
}

t_vec3	ray_color(t_ray *r, t_object *objects)
{
	t_object	*current;
	t_sphere	*sphere;
	t_vec3		center;
	double		t;
	t_vec3		hit_point;
	t_vec3		normal;
	t_vec3		unit_direction;

	current = objects;
	while (current)
	{
		sphere = (t_sphere *)current->object;
		center = vec3(sphere->x, sphere->y, sphere->z);
		t = current->hit(center, sphere->radius, *r);
		//printf(" t val = %f", t);
		if (t > 0.0)
		{
			//printf("I hit\n");
			hit_point = ray_at(r, t);
			normal = vector_normalize(vector_subtract(hit_point, center));
			return (vector_scale(vector_add(normal, vec3(1, 1, 1)), 0.5));
		}
		current = current->next;
	}
	// Background gradient
	unit_direction = vector_normalize(r->dir);
	t = 0.5 * (unit_direction.y + 1.0);
	return (vector_add(vector_scale(vec3(1.0, 1.0, 1.0), 1.0 - t),
			vector_scale(vec3(0.5, 0.7, 1.0), t)));
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

void	render_scene(t_scene *scene)
{
	t_vec3 pixel_center;
	t_vec3 ray_dir;
	t_vec3 color;
	int i, j = 0;

	while (j < scene->render.image_height)
	{
		i = 0;
		while (i < scene->render.image_width)
		{
			pixel_center = calculate_pixel_position(i, j, &scene->camera);
			ray_dir = vector_subtract(pixel_center,
					scene->camera.camera_center);
			ray_init(&scene->r, &scene->camera.camera_center, &ray_dir);
			color = ray_color(&scene->r, scene->objects);
			write_colors(&scene->mlx.img, i, j, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
			scene->mlx.img.img, 50, 28);
}
