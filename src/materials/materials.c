/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:16:14 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/15 00:51:08 by ael-mank         ###   ########.fr       */
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

double reflectance(double cosine, double ref_idx) {
	double r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

int glass_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat) {
    *attenuation = vec3(1, 1, 1);
	double ri = rec->front_face ? (1 / mat->ref_indx) : mat->ref_indx;
	
	t_vec3 unit_direction = vector_normalize(r->dir);
	double cos_theta = fmin(dot(vector_scale(unit_direction, -1), rec->normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	
	int cannot_refract = ri * sin_theta > 1.0;
	t_vec3 direction;

	if (cannot_refract || reflectance(cos_theta, ri) > random_double())
		direction = reflect(unit_direction, rec->normal);
	else
		direction = refract(&unit_direction, &rec->normal, ri);

	
	ray_init(scattered, &rec->p, &direction);
	return (1);
}