/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:40:11 by ael-mank          #+#    #+#             */
/*   Updated: 2024/07/29 13:40:28 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>

typedef struct		s_coord
{
	double			x;
	double			y;
	double			z;
}					t_coord;

t_coord				gen_coord(double x, double y, double z);
double				v_len_sqr(t_coord v);
double				v_len(t_coord v);
t_coord				v_norm(t_coord v);

t_coord				v_add(t_coord v, t_coord u);
t_coord				v_sub(t_coord v, t_coord u);
t_coord				v_scale(t_coord v, double f);
t_coord				v_cross(t_coord v, t_coord u);
double				v_dot(t_coord v, t_coord u);

#endif