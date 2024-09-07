/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:29:30 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/07 16:02:38 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "my_mlx.h"
#include "bvh.h"
#include "aabb.h"
#include "minirt.h"
#include "mlx_int.h"

// Forward declarations
typedef struct s_material t_material;
typedef struct s_bvh t_bvh;

// Material types enumeration
typedef enum e_material_type {
    MATTE,
    METAL,
    GLASS,
    BUBBLE,
    CHECKERBOARD,
    GLOBE,
	LIGHT,
	INVISIBLE,
} t_material_type;

// Hit record structure
typedef struct s_hitrecord {
    t_point3 p;
    t_vec3 normal;
    double t;
    int front_face;
    t_material *mat;
    double u;
    double v;
} t_hitrecord;

// Material structure
typedef struct s_material {
    int (*scatter)(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat);
    t_vec3 (*texture)(t_material *mat, t_hitrecord *rec);
	t_vec3 (*emission)(t_material *mat, t_hitrecord *rec);
    t_vec3 albedo;
    double fuzz;
    double ref_indx;
    t_texture *img;
} t_material;

// Sphere structure
typedef struct s_sphere {
    double x, y, z;
    double radius;
    t_vec3 center;
    t_material *mat;
} t_sphere;

// Quad structure
typedef struct s_quad {
    t_point3 start;
    t_vec3 u;
    t_vec3 v;
    t_material *mat;
	t_vec3 normal;
	double d;
	t_vec3 w;
} t_quad;

typedef struct s_triangle {
    t_point3 v0;        // First vertex of the triangle
    t_point3 v1;        // Second vertex of the triangle
    t_point3 v2;        // Third vertex of the triangle
    t_vec3 normal;      // Normal vector of the triangle
    double d;           // Plane constant for the triangle's plane equation
    t_material *mat;    // Material of the triangle
} t_triangle;

// Object structure
typedef struct s_object {
    void *object;
    double (*hit)(t_ray r, void *object, t_interval ray_t, t_hitrecord *rec);
    void (*free)(t_bvh *node);
    t_material *mat;
    t_aabb box;
    struct s_object *next;
} t_object;

// Scatter functions for different materials
int metal_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat);
int lambertian_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat);
int glass_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation, t_ray *scattered, t_material *mat);
int light_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation,
		t_ray *scattered, t_material *mat);
int	invisible_scatter(t_ray *r, t_hitrecord *rec, t_vec3 *attenuation,
		t_ray *scattered, t_material *mat);

// Hit functions for different objects
double	hit_quad_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec);
double	hit_sphere_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec);
double hit_triangle_wrapper(t_ray r, void *object, t_interval ray_t, t_hitrecord *rec);

// Creation functions for objects
t_sphere *create_sphere(t_point3 center, double radius, t_material_type type, t_vec3 color);
t_object *add_sphere(t_object *head, t_sphere *sphere);

t_quad *create_quad(t_point3 start, t_vec3 normal, t_material_type type, t_vec3 color);
t_object	*add_quad(t_object *head, t_quad *quad);

t_object *add_triangle(t_object *head, t_triangle *triangle);
t_triangle *create_triangle(t_point3 v0, t_point3 v1, t_point3 v2, t_material_type type, t_vec3 color);

// Texture functions
t_vec3 solid_color(t_material *mat, t_hitrecord *rec);
t_vec3 checkerboard(t_material *mat, t_hitrecord *rec);
t_vec3 get_texture_color(t_material *mat, t_hitrecord *rec);

// Emission functions
t_vec3 no_light(t_material *mat, t_hitrecord *rec);

t_vec3 diffuse_light(t_material *mat, t_hitrecord *rec);

// Free functions for objects
void free_sphere(t_bvh *node);
void free_quad(t_bvh *node);
void free_triangle(t_bvh *node);

#endif