/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:11:43 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/17 11:20:30 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*create_cylinder(t_point3 center, t_vec3 axis, double diameter, double height, t_material_type type, t_vec3 color)
{
    t_cylinder	*cylinder;
    t_material	*mat;

    cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        return (NULL);
    mat = create_material(type);
    if (!mat)
    {
        free(cylinder);
        return (NULL);
    }
    mat->albedo = color;
    cylinder->mat = mat;
    cylinder->center = center;
    cylinder->axis = vector_normalize(axis); // Ensure the axis is a unit vector
    cylinder->radius = diameter / 2.0;
    cylinder->height = height;
    return (cylinder);
}

t_vec3 vector_min(t_vec3 a, t_vec3 b)
{
    return vec3(fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z));
}

t_vec3 vector_max(t_vec3 a, t_vec3 b)
{
    return vec3(fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z));
}

t_object	*add_cylinder(t_object *head, t_cylinder *cylinder)
{
    t_object	*new_object;

    new_object = malloc(sizeof(t_object));
    if (!new_object)
        return (NULL);
    if (!cylinder)
{
    free(new_object);
    return (NULL);
}
new_object->object = cylinder;
new_object->mat = cylinder->mat;
new_object->hit = hit_cylinder_wrapper; // Assuming you have a hit function for the cylinder
new_object->free = free_cylinder; // Assuming you have a free function for the cylinder

// Normalize the axis vector
t_vec3 normalized_axis = vector_normalize(cylinder->axis);

// Calculate the extent along the axis
t_vec3 half_height_vec = vector_scale(normalized_axis, cylinder->height / 2.0);

// Calculate the radius in the perpendicular plane
t_vec3 radius_vec = vec3(cylinder->radius, cylinder->radius, cylinder->radius);

// Calculate the bounding box
t_point3 min = vector_subtract(vector_subtract(cylinder->center, half_height_vec), radius_vec);
t_point3 max = vector_add(vector_add(cylinder->center, half_height_vec), radius_vec);

// Adjust the bounding box to account for the axis orientation
min = vector_min(min, vector_subtract(vector_add(cylinder->center, half_height_vec), radius_vec));
max = vector_max(max, vector_add(vector_subtract(cylinder->center, half_height_vec), radius_vec));

new_object->box = aabb_points(min, max);
new_object->next = NULL;
return (add_object_end(head, new_object));
}