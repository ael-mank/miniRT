/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:51:58 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:58:51 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static inline t_vec3	initialize_final_color(void)
{
	return (vec3(0, 0, 0));
}

static inline t_vec3	get_material_color(t_hitrecord *rec)
{
	return (rec->mat->texture(rec->mat, rec));
}

static inline t_vec3	calculate_diffuse(t_vec3 material_color,
		t_point_light *light, double diff)
{
	return (vector_scale(vector_multiply(material_color, light->color), diff
			* light->intensity));
}

static inline int	is_shadowed(t_scene *scene, t_ray shadow_ray,
		double light_distance)
{
	t_hitrecord	shadow_rec;

	ft_bzero(&shadow_rec, sizeof(t_hitrecord));
	return (bvh_hit(scene->bvh, shadow_ray, (t_interval){0.001, light_distance},
		&shadow_rec));
}

t_vec3	calculate_lighting(t_hitrecord *rec, t_scene *scene)
{
	t_vec3			vecs[4];
	double			doubles[2];
	t_point_light	*light;
	t_ray			shadow_ray;

	vecs[0] = initialize_final_color();
	light = scene->lights;
	vecs[1] = get_material_color(rec);
	while (light != NULL)
	{
		vecs[2] = vector_subtract(light->position, rec->p);
		doubles[0] = vector_length(vecs[2]);
		vecs[2] = vector_normalize(vecs[2]);
		shadow_ray = (t_ray){rec->p, vecs[2]};
		if (is_shadowed(scene, shadow_ray, doubles[0]))
		{
			light = light->next;
			continue ;
		}
		doubles[1] = fmax(0.0, dot(rec->normal, vecs[2]));
		vecs[3] = calculate_diffuse(vecs[1], light, doubles[1]);
		vecs[0] = vector_add(vecs[0], vecs[3]);
		light = light->next;
	}
	return (vector_scale(vecs[0], 1.5));
}
