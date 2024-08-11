/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:29:30 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/11 14:15:08 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "minirt.h"

typedef struct s_material t_material;
typedef struct s_sphere{
    double x, y, z;
    double radius;
	t_vec3 center;
	t_material *mat;
} t_sphere;

typedef struct s_hitrecord {
    t_point3 p;
    t_vec3 normal;
    double t;
    int front_face;
	t_material *mat;
} t_hitrecord;

typedef enum e_material_type {
    MATTE,
	METAL,
} t_material_type;

typedef struct s_material {
    int (*scatter)(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_vec3 albedo);
	t_vec3 albedo;
} t_material;

typedef struct s_object
{
	void *object;
	t_vec3 center;
	double (*hit)(t_ray r, void *object, t_interval ray_t, t_hitrecord *rec);
	t_material *mat;
	struct s_object *next;
} t_object;

int metal_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_vec3 albedo);
int lambertian_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_vec3 albedo);

double	hit_sphere(t_ray r, t_sphere sphere, t_interval ray_t, t_hitrecord *rec);


#endif