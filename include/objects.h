/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:29:30 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/10 13:07:09 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "minirt.h"

typedef struct s_sphere{
    double x, y, z;
    double radius;
	t_vec3 center;
} t_sphere;

typedef struct s_hitrecord {
    t_vec3 p;
    t_vec3 normal;
    double t;
    int front_face;
} t_hitrecord;

typedef struct s_object
{
	void *object;
	t_vec3 center;
	double (*hit)(t_ray r, void *object, t_interval ray_t, t_hitrecord *rec);
	struct s_object *next;
} t_object;

double	hit_sphere(t_ray r, t_sphere sphere, t_interval ray_t, t_hitrecord *rec);


#endif