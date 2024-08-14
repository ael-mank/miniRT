/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:16:14 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/14 16:16:36 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int lambertian_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat)
{
	(void)r;
    t_vec3 direction;

    direction = vector_add(rec->normal, random_unit_vector());
	
	if (near_zero(direction))
		direction = rec->normal;
    ray_init(scattered, &rec->p, &direction);
    *attenuation = mat->albedo;
    return (1);
}

int metal_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat)
{
    t_vec3 direction;

    if (mat->fuzz > 1)
		mat->fuzz = 1;
	direction = reflect(vector_normalize(r->dir), rec->normal);
	direction = vector_add(unit_vector(direction),vector_scale(random_unit_vector(), mat->fuzz));
    ray_init(scattered, &rec->p, &direction);
    *attenuation = mat->albedo;
    if (dot(scattered->dir, rec->normal) > 0)
        return (1);
    else
        return (0);
}

int glass_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat)
{
    t_vec3 direction;

    
	direction = reflect(vector_normalize(r->dir), rec->normal);
	direction = vector_add(unit_vector(direction),vector_scale(random_unit_vector(), mat->fuzz));
    ray_init(scattered, &rec->p, &direction);
    *attenuation = mat->albedo;
    if (dot(scattered->dir, rec->normal) > 0)
        return (1);
    else
        return (0);
}