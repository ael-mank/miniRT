/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:31:07 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/12 16:05:56 by ael-mank         ###   ########.fr       */
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
	camera->samples_per_pixel = 50;
	camera->max_depth = 20;
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

t_object *add_object_end(t_object *head, t_object *new_object)
{
	t_object *current = head;
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

double hit_sphere_wrapper(t_ray r, void *object, t_interval ray_t, t_hitrecord *rec)
{
	return (hit_sphere(r, *(t_sphere *)object, ray_t, rec));
}

t_material *create_material(t_material_type type)
{
    t_material *mat = malloc(sizeof(t_material));
    if (!mat)
        return (NULL);
    if (type == MATTE)
        mat->scatter = lambertian_scatter;
    else if (type == METAL)
        mat->scatter = metal_scatter;
	else
	{
		free(mat);
		return (NULL);
	}
    return (mat);
}

t_object *add_sphere(t_object *head, t_point3 center, double radius, t_material_type type, t_vec3 color)
{
    t_object *new_object = malloc(sizeof(t_object));
    if (!new_object)
        return NULL;

    t_sphere *sphere = malloc(sizeof(t_sphere));
    if (!sphere) {
        free(new_object);
        return NULL;
    }

    t_material *mat = create_material(type);
    if (!mat) {
        free(sphere);
        free(new_object);
        return NULL;
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

t_object	*init_objects(void)
{
	t_object *head = NULL;
	head = add_sphere(head, vec3(0, 2, -5), 2, METAL, vec3(0.8, 0.8, 0.8));
	head = add_sphere(head, vec3(0.5, 0, -1), 0.5, MATTE, vec3(0.5, 1, 0));
	head = add_sphere(head, vec3(-0.5, 0, -1), 0.5, MATTE, vec3(1, 0.4, 0));
	head = add_sphere(head, vec3(0, -100.5, -1), 100, MATTE, vec3(0.8, 0.8, 0.8));
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