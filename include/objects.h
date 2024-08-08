/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:29:30 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/08 13:33:20 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "minirt.h"

typedef struct s_sphere{
    double x, y, z;
    double radius;
} t_sphere;

typedef struct s_object
{
	void *object;
	double (*hit)(t_vec3 center, double radius, t_ray r);
	struct s_object *next;
} t_object;

double hit_sphere(t_vec3 center, double radius, t_ray r);


#endif