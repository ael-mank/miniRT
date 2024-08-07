/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:40:11 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/07 12:02:08 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>

typedef	struct s_vec3	t_point3;
typedef	struct s_vec3	t_vec3;
typedef struct s_ray	t_ray;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ray
{
	t_point3	org;
	t_vec3		dir;
}	t_ray;

t_vec3	vec3(double x, double y, double z);

t_vec3	vector_add(t_vec3 a, t_vec3 b);

t_vec3	vector_subtract(t_vec3 a, t_vec3 b);

t_vec3	vector_scale(t_vec3 v, double scalar);
t_vec3 vector_divide(t_vec3 v, double scalar);
double	dot_product(t_vec3 a, t_vec3 b);
double dot(t_vec3 a, t_vec3 b);
t_vec3	cross_product(t_vec3 a, t_vec3 b);

double	vector_length(t_vec3 v);
double vector_length_squared(t_vec3 v);
t_vec3	vector_normalize(t_vec3 v);

void	ray_init(t_ray *r, const t_point3 *origin, const t_point3 *direction);
t_point3	ray_at(t_ray *r, double t);

#endif