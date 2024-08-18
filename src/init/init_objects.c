/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:33:28 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/18 00:50:10 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	int			i;

	i = -1;
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
	pyramid_data->mat = mat;
	while (++i < 4)
		pyramid_data->vertices[i] = base_vertices[i];
	pyramid_data->apex = apex;
	new_object->object = pyramid_data;
	new_object->mat = mat;
	new_object->hit = hit_pyramid_wrapper;
	new_object->next = NULL;
	return (new_object);
}

t_object	*add_pyramid(t_object *head, t_vec3 center, float height,
		t_material_type material, t_vec3 color)
{
	t_object	*new_pyramid;
	t_vec3		apex;
	float		half_side;

	half_side = 0.5;
	t_vec3 base_vertices[4] = {
		vec3(center.x - half_side, center.y, center.z - half_side),
		vec3(center.x + half_side, center.y, center.z - half_side),
		vec3(center.x + half_side, center.y, center.z + half_side),
		vec3(center.x - half_side, center.y, center.z + half_side)};
	apex = vec3(center.x, center.y + height, center.z);
	new_pyramid = create_pyramid(base_vertices, apex, material, color);
	if (!new_pyramid)
		return (NULL);
	return (add_object_end(head, new_pyramid));
}

t_object	*init_objects(void)
{
	t_object *head = NULL;

	head = add_sphere(head, vec3(0, -1000, -1), 1000, MATTE, vec3(0.8, 0.8,
				0.0));

	head = add_sphere(head, vec3(0, 1, 0), 1.0, GLASS, vec3(1.0, 1.0, 1.0));
	head = add_sphere(head, vec3(0, 1, 0), 0.9, BUBBLE, vec3(1.0, 1.0, 1.0));

	head = add_sphere(head, vec3(-4, 1, 0), 1, MATTE, vec3(0.4, 0.2, 0.1));

	head = add_pyramid(head, vec3(4.6, 0.7, 0.7), 1, MATTE, vec3(0.7, 0.6,
				0.5));

	head = add_sphere(head, vec3(4, 1, 0), 1, METAL, vec3(0.7, 0.6, 0.5));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			double choose_mat = random_double();
			t_vec3 center = vec3(a + 0.9 * random_double(), 0.2, b + 0.9
					* random_double());

			if (sqrt(pow(center.x - 4, 2) + pow(center.y - 0.2, 2)
					+ pow(center.z, 2)) > 0.9)
			{
				if (choose_mat < 0.8)
				{
					// Diffuse
					t_vec3 albedo = vec3(random_double(), random_double(),
							random_double());
					albedo = vec3(albedo.x * random_double(), albedo.y
							* random_double(), albedo.z * random_double());
					head = add_sphere(head, center, 0.2, MATTE, albedo);
				}
				else if (choose_mat < 0.95)
				{
					// Metal
					t_vec3 albedo = vec3(0.5 + 0.5 * random_double(), 0.5 + 0.5
							* random_double(), 0.5 + 0.5 * random_double());
					head = add_sphere(head, center, 0.2, METAL, albedo);
				}
				else
				{
					// Glass
					head = add_sphere(head, center, 0.2, GLASS, vec3(1.0, 1.0,
								1.0));
				}
			}
		}
	}
	return (head);
}