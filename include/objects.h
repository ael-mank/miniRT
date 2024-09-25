/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:29:30 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 12:12:06 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "aabb.h"
# include "bvh.h"
# include "minirt.h"
# include "mlx_int.h"
# include "my_mlx.h"

typedef struct s_material	t_material;
typedef struct s_bvh		t_bvh;

typedef enum e_material_type
{
	MATTE,
	METAL,
	GLASS,
	BUBBLE,
	CHECKERBOARD,
	GLOBE,
	LIGHT,
	INVISIBLE
}							t_material_type;

typedef struct s_hitrecord
{
	t_point3				p;
	t_vec3					normal;
	double					t;
	int						front_face;
	t_material				*mat;
	double					u;
	double					v;
}							t_hitrecord;

typedef struct s_scatter_params
{
	t_ray					*r;
	t_hitrecord				*rec;
	t_vec3					*attenuation;
	t_ray					*scattered;
	t_material				*mat;
}							t_scatter_params;

typedef struct s_material
{
	int						(*scatter)(t_scatter_params	*params);
	t_vec3					(*texture)(t_material	*mat, t_hitrecord	*rec);
	t_vec3					(*emission)(t_material	*mat, t_hitrecord	*rec);
	t_vec3					albedo;
	double					fuzz;
	double					ref_indx;
	t_texture				*img;
	t_texture				*normal_map;
}							t_material;

typedef struct s_sphere
{
	double					x;
	double					y;
	double					z;
	double					radius;
	t_vec3					center;
	t_material				*mat;
}							t_sphere;

typedef struct s_quad
{
	t_point3				start;
	t_vec3					u;
	t_vec3					v;
	t_material				*mat;
	t_vec3					normal;
	double					d;
	t_vec3					w;
}							t_quad;

typedef struct s_plane
{
	t_point3				point;
	t_vec3					normal;
	double					d;
	t_material				*mat;
}							t_plane;

typedef struct s_triangle
{
	t_point3				v0;
	t_point3				v1;
	t_point3				v2;
	t_vec3					normal;
	double					d;
	t_material				*mat;
}							t_triangle;

typedef struct s_cylinder
{
	t_point3				center;
	t_vec3					axis;
	double					radius;
	double					height;
	t_material				*mat;
}							t_cylinder;

typedef struct s_object
{
	void					*object;
	double					(*hit)(t_ray r, void *object, t_interval ray_t,
			t_hitrecord *rec);
	void					(*free)(t_bvh *node);
	t_material				*mat;
	t_aabb					box;
	struct s_object			*next;
}							t_object;

int							metal_scatter(t_scatter_params *params);
int							lambertian_scatter(t_scatter_params *params);
int							glass_scatter(t_scatter_params *params);
int							light_scatter(t_scatter_params *params);
int							invisible_scatter(t_scatter_params *params);

double						hit_quad_wrapper(t_ray r, void *object,
								t_interval ray_t, t_hitrecord *rec);
double						hit_sphere_wrapper(t_ray r, void *object,
								t_interval ray_t, t_hitrecord *rec);
double						hit_triangle_wrapper(t_ray r, void *object,
								t_interval ray_t, t_hitrecord *rec);
double						hit_plane_wrapper(t_ray r, void *object,
								t_interval ray_t, t_hitrecord *rec);
double						hit_cylinder_wrapper(t_ray r, void *object,
								t_interval ray_t, t_hitrecord *rec);

t_sphere					*create_sphere(t_point3 center, double radius,
								t_material_type type, t_vec3 color);
t_object					*add_sphere(t_object *head, t_sphere *sphere);

// t_quad						*create_quad(t_point3 start, t_vec3 
//u, t_vec3 v, t_material_type type, t_vec3 color);
// t_object					*add_quad(t_object *head, t_quad *quad);

t_object					*add_triangle(t_object *head, t_triangle *triangle);
t_triangle					*create_triangle(t_tri3 tri, t_material_type type,
								t_vec3 color);

t_plane						*create_plane(t_point3 point, t_vec3 normal,
								t_material_type type, t_vec3 color);
t_object					*add_plane(t_object *head, t_plane *plane);

t_cylinder					*create_cylinder(t_cylinder *cylinder,
								t_material_type type, t_vec3 color);
t_object					*add_cylinder(t_object *head, t_cylinder *cylinder);

t_vec3						solid_color(t_material *mat, t_hitrecord *rec);
t_vec3						show_normal(t_material *mat, t_hitrecord *rec);
t_vec3						checkerboard(t_material *mat, t_hitrecord *rec);
t_vec3						get_texture_color(t_material *mat,
								t_hitrecord *rec);

t_vec3						no_light(t_material *mat, t_hitrecord *rec);
t_vec3						diffuse_light(t_material *mat, t_hitrecord *rec);

void						free_sphere(t_bvh *node);
void						free_quad(t_bvh *node);
void						free_triangle(t_bvh *node);
void						free_plane(t_bvh *node);
void						free_cylinder(t_bvh *node);

#endif