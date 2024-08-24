/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:29:30 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/24 17:59:18 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "my_mlx.h"
#include "bvh.h"
#include "aabb.h"
#include "minirt.h"
#include "mlx_int.h"

typedef struct s_material t_material;
typedef struct s_bvh t_bvh;


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
	double u;
	double v;
} t_hitrecord;

typedef enum e_material_type {
    MATTE,
	METAL,
	GLASS,
	BUBBLE,
	CHECKERBOARD,
	GLOBE,
	MOON,
} t_material_type;

typedef struct s_material {
    int (*scatter)(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat);
	t_vec3 (*texture)(t_material *mat, t_hitrecord *rec);
	t_vec3 albedo;
	double	fuzz;
	double	ref_indx;
	t_texture *img;
} t_material;

typedef struct s_object
{
	void *object;
	t_vec3 center;
	double (*hit)(t_ray r, void *object, t_interval ray_t, t_hitrecord *rec);
	void (*free)(t_bvh *node);
	t_material *mat;
	t_aabb box;
	struct s_object *next;
} t_object;

int metal_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat);
int lambertian_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat);
int glass_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat);

double	hit_sphere(t_ray r, t_sphere sphere, t_interval ray_t, t_hitrecord *rec);

t_sphere *create_sphere(t_point3 center, double radius, t_material_type type, t_vec3 color);
t_object *add_sphere(t_object *head, t_sphere *sphere);

t_vec3	solid_color(t_material *mat, t_hitrecord *rec);

t_vec3	checkerboard(t_material *mat, t_hitrecord *rec);
t_vec3 get_texture_color(t_material *mat, t_hitrecord *rec);


void	free_sphere(t_bvh *node);
#endif