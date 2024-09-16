/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:16:14 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/16 16:11:28 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EPSILON 1e-4

int invisible_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat)
{
    (void)mat;
    *attenuation = vec3(1, 1, 1); // No attenuation, fully transparent

    // Check the direction of the incoming ray
    if (dot_product(r->dir, rec->normal) > 0) {
        // Ray is coming from outside the box, reflect it back
        t_vec3 reflected_dir = reflect(r->dir, rec->normal);
        t_vec3 offset_origin = vector_add(rec->p, vector_scale(rec->normal, EPSILON));
        ray_init(scattered, &offset_origin, &reflected_dir);
    } else {
        // Ray is coming from inside the box, pass it through
        t_vec3 offset_origin = vector_subtract(rec->p, vector_scale(rec->normal, EPSILON));
        ray_init(scattered, &offset_origin, &r->dir);
    }

    return 1; // Indicate that scattering occurred
}

int	lambertian_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation,
		t_ray *scattered, t_material *mat)
{
	t_vec3	direction;

	(void)r;
	direction = vector_add(rec->normal, random_unit_vector());
	if (near_zero(direction))
		direction = rec->normal;
	ray_init(scattered, &rec->p, &direction);
	*attenuation = mat->texture(mat, rec);
	return (1);
}

int light_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation,
		t_ray *scattered, t_material *mat)
{
	//void them all and return 0
	(void)r;
	(void)rec;
	(void)attenuation;
	(void)scattered;
	(void)mat;
	return (0);
}

int	metal_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation,
		t_ray *scattered, t_material *mat)
{
	t_vec3	direction;

	if (mat->fuzz > 1)
		mat->fuzz = 1;
	direction = reflect(vector_normalize(r->dir), rec->normal);
	direction = vector_add(unit_vector(direction),
			vector_scale(random_unit_vector(), mat->fuzz));
	ray_init(scattered, &rec->p, &direction);
	*attenuation = mat->texture(mat, rec);
	if (dot(scattered->dir, rec->normal) > 0)
		return (1);
	else
		return (0);
}

double	reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

int	glass_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation,
		t_ray *scattered, t_material *mat)
{
	double	ri;
	t_vec3	unit_direction;
	double	sin_theta;
	t_vec3	direction;
	double	cos_theta;

	if (rec->front_face)
		ri = 1 / mat->ref_indx;
	else
		ri = mat->ref_indx;
	*attenuation = vec3(1, 1, 1);
	unit_direction = vector_normalize(r->dir);
	cos_theta = fmin(dot(vector_scale(unit_direction, -1), rec->normal),
			1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	if (ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double())
		direction = reflect(unit_direction, rec->normal);
	else
		direction = refract(&unit_direction, &rec->normal, ri);
	ray_init(scattered, &rec->p, &direction);
	return (1);
}
