/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:16:14 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 10:52:18 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EPSILON 1e-4

int invisible_scatter(t_scatter_params *params)
{
    (void)params->mat;
    *params->attenuation = vec3(1, 1, 1); // No attenuation, fully transparent

    // Check the direction of the incoming ray
    if (dot_product(params->r->dir, params->rec->normal) > 0) {
        // Ray is coming from outside the box, reflect it back
        t_vec3 reflected_dir = reflect(params->r->dir, params->rec->normal);
        t_vec3 offset_origin = vector_add(params->rec->p, vector_scale(params->rec->normal, EPSILON));
        ray_init(params->scattered, &offset_origin, &reflected_dir);
    } else {
        // Ray is coming from inside the box, pass it through
        t_vec3 offset_origin = vector_subtract(params->rec->p, vector_scale(params->rec->normal, EPSILON));
        ray_init(params->scattered, &offset_origin, &params->r->dir);
    }

    return 1; // Indicate that scattering occurred
}

int lambertian_scatter(t_scatter_params *params)
{
    t_vec3 direction;

    (void)params->r;
    direction = vector_add(params->rec->normal, random_unit_vector());
    if (near_zero(direction))
        direction = params->rec->normal;
    ray_init(params->scattered, &params->rec->p, &direction);
    *params->attenuation = params->mat->texture(params->mat, params->rec);
    return 1;
}

int light_scatter(t_scatter_params *params)
{
    //void them all and return 0
    (void)params->r;
    (void)params->rec;
    (void)params->attenuation;
    (void)params->scattered;
    (void)params->mat;
    return 0;
}

int metal_scatter(t_scatter_params *params)
{
    t_vec3 reflected;
    t_vec3 fuzzed_direction;

    if (params->mat->fuzz > 1)
        params->mat->fuzz = 1;

    // Reflect the ray direction around the normal
    reflected = reflect(vector_normalize(params->r->dir), params->rec->normal);

    // Apply fuzziness to the reflected direction
    fuzzed_direction = vector_add(reflected, vector_scale(random_unit_vector(), params->mat->fuzz));

    // Initialize the scattered ray
    ray_init(params->scattered, &params->rec->p, &fuzzed_direction);

    // Set the attenuation based on the material's texture
    *params->attenuation = params->mat->texture(params->mat, params->rec);

    // Check if the scattered ray is in the same hemisphere as the normal
    if (dot(params->scattered->dir, params->rec->normal) > 0)
        return 1;
    else
        return 0;
}

double	reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

int glass_scatter(t_scatter_params *params)
{
    double ri;
    t_vec3 unit_direction;
    double sin_theta;
    t_vec3 direction;
    double cos_theta;

    if (params->rec->front_face)
        ri = 1 / params->mat->ref_indx;
    else
        ri = params->mat->ref_indx;
    *params->attenuation = vec3(1, 1, 1);
    unit_direction = vector_normalize(params->r->dir);
    cos_theta = fmin(dot(vector_scale(unit_direction, -1), params->rec->normal), 1.0);
    sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    if (ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double())
        direction = reflect(unit_direction, params->rec->normal);
    else
        direction = refract(&unit_direction, &params->rec->normal, ri);
    ray_init(params->scattered, &params->rec->p, &direction);
    return 1;
}
