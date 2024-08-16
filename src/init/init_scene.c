/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:31:07 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/16 15:55:56 by ael-mank         ###   ########.fr       */
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

	camera->lookfrom = vec3(4, 2, 0);
	camera->lookat = vec3(0, 0, -1);
	camera->v_up = vec3(0, 1, 0);
	camera->fov = 30;
	camera->defocus_angle = 10;
	camera->focus_dist = 4.6;
	camera->theta = deg_to_rad(camera->fov);
	h = tan(camera->theta / 2);
	camera->viewport_height = 2.0 * h * camera->focus_dist;
	camera->viewport_width = camera->viewport_height * (render->image_width
			/ (double)render->image_height);
	camera->w = unit_vector(vector_subtract(camera->lookfrom, camera->lookat));
	camera->u = unit_vector(cross_product(camera->v_up, camera->w));
	camera->v = cross_product(camera->w, camera->u);
	camera->viewport_u = vector_scale(camera->u, camera->viewport_width);
	camera->viewport_v = vector_scale(vector_scale(camera->v, -1), camera->viewport_height);
	camera->pixel_delta_u = vector_divide(camera->viewport_u,
										render->image_width);
	camera->pixel_delta_v = vector_divide(camera->viewport_v,
										render->image_height);
	camera->samples_per_pixel = 50;
	camera->max_depth = 25;
}

void	init_camera(t_camera *camera)
{
	double	defocus_radius;

	defocus_radius = camera->focus_dist * tan(deg_to_rad(camera->defocus_angle / 2));
	camera->defocus_disk_u = vector_scale(camera->u, defocus_radius);
	camera->defocus_disk_v = vector_scale(camera->v, defocus_radius);
	camera->camera_center = camera->lookfrom;
	camera->viewport_upper_left = vector_subtract(vector_subtract(vector_subtract(camera->camera_center, vector_scale(camera->w, camera->focus_dist)),vector_divide(camera->viewport_u, 2)), vector_divide(camera->viewport_v, 2));
	camera->pixel00_loc.x = camera->viewport_upper_left.x + 0.5
		* (camera->pixel_delta_u.x + camera->pixel_delta_v.x);
	camera->pixel00_loc.y = camera->viewport_upper_left.y + 0.5
		* (camera->pixel_delta_u.y + camera->pixel_delta_v.y);
	camera->pixel00_loc.z = camera->viewport_upper_left.z + 0.5
		* (camera->pixel_delta_u.z + camera->pixel_delta_v.z);
}

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

double	hit_sphere_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_sphere(r, *(t_sphere *)object, ray_t, rec));
}

double	hit_pyramid_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_pyramid(r, *(t_pyramid *)object, ray_t, rec));
}

t_material	*create_material(t_material_type type)
{
	t_material	*mat;

	mat = malloc(sizeof(t_material));
	if (!mat)
		return (NULL);
	if (type == MATTE)
	{
		mat->scatter = lambertian_scatter;
		mat->fuzz = 0;
		mat->ref_indx = 0;
	}
	else if (type == METAL)
	{
		mat->scatter = metal_scatter;
		mat->fuzz = 0;
		mat->ref_indx = 0;
	}
	else if (type == GLASS)
	{
		mat->scatter = glass_scatter;
		mat->fuzz = 0;
		mat->ref_indx = 1.50;
	}
	else if (type == BUBBLE)
	{
		mat->scatter = glass_scatter;
		mat->fuzz = 0;
		mat->ref_indx = 1.00 / 1.50;
	}
	else
	{
		write(1, "Invalid material type\n", 22);
		free(mat);
		return (NULL);
	}
	return (mat);
}

t_object	*add_sphere(t_object *head, t_point3 center, double radius,
		t_material_type type, t_vec3 color)
{
	t_object	*new_object;
	t_sphere	*sphere;
	t_material	*mat;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return (NULL);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
	{
		free(new_object);
		return (NULL);
	}
	mat = create_material(type);
	if (!mat)
	{
		free(sphere);
		free(new_object);
		return (NULL);
	}
	mat->albedo = color;
	sphere->mat = mat;
	sphere->center = center;
	sphere->radius = radius;
	new_object->object = sphere;
	new_object->mat = mat;
	new_object->center = center;
	new_object->hit = hit_sphere_wrapper;
	new_object->next = NULL;
	return (add_object_end(head, new_object));
}

t_object	*create_pyramid(t_vec3 base_vertices[4], t_vec3 apex,
		t_material_type type, t_vec3 color)
{
	t_object	*new_object;
	t_pyramid	*pyramid_data;
	t_material	*mat;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return (NULL);
	pyramid_data = malloc(sizeof(t_pyramid));
	if (!pyramid_data)
	{
		free(new_object);
		return (NULL);
	}
	mat = create_material(type);
	if (!mat)
	{
		free(pyramid_data);
		free(new_object);
		return (NULL);
	}
	mat->albedo = color;
	pyramid_data->mat = mat; // Assign the material to the pyramid
	pyramid_data->vertices[0] = base_vertices[0];
	pyramid_data->vertices[1] = base_vertices[1];
	pyramid_data->vertices[2] = base_vertices[2];
	pyramid_data->vertices[3] = base_vertices[3];
	pyramid_data->apex = apex;
	new_object->object = pyramid_data;
	new_object->mat = mat; // Assign the material to the object
	new_object->hit = hit_pyramid_wrapper;
	// Assuming you have a hit function for the pyramid
	new_object->next = NULL;
	return (new_object);
}

t_object	*add_pyramid(t_object *head, t_vec3 center, float height,
		t_material_type material, t_vec3 color)
{
	t_object	*new_pyramid;
	t_vec3		apex;

	float half_side = 0.5; // Assuming the base is a square with side length 1
	t_vec3 base_vertices[4] = {
		vec3(center.x - half_side, center.y, center.z - half_side),
		// Bottom-left
		vec3(center.x + half_side, center.y, center.z - half_side),
		// Bottom-right
		vec3(center.x + half_side, center.y, center.z + half_side), // Top-right
		vec3(center.x - half_side, center.y, center.z + half_side)  // Top-left
	};
	apex = vec3(center.x, center.y + height, center.z);
	// Apex above the center of the base
	new_pyramid = create_pyramid(base_vertices, apex, material, color);
	if (!new_pyramid)
		return (NULL);
	return (add_object_end(head, new_pyramid));
}

t_object	*init_objects(void)
{
	t_object	*head;

	head = NULL;
	// Ground sphere
	head = add_sphere(head, vec3(0, -100.5, -1), 100, MATTE, vec3(0.8, 0.8,
				0.0));
	head = add_sphere(head, vec3(-1, 0, -1), 0.5, GLASS, vec3(1.0, 1.0, 1.0));
	head = add_sphere(head, vec3(-1, 0, -1), 0.4, BUBBLE, vec3(1.0, 1.0, 1.0));
	head = add_sphere(head, vec3(0, 0, -1.2), 0.5, MATTE, vec3(0.1, 0.2, 0.5));
	head = add_sphere(head, vec3(1, 0, -1), 0.5, METAL, vec3(0.8, 0.6, 0.2));
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
