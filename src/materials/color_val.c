/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:40:09 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/22 14:00:13 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	solid_color(t_material *mat, t_hitrecord *rec)
{
	(void)rec;
	return (mat->albedo);
}

t_vec3	checkerboard(t_material *mat, t_hitrecord *rec)
{
	t_vec3 white;
	t_vec3 second;
	double inv_scale;
	int xInteger;
	int yInteger;
	int zInteger;
	int isEven;

	white = vec3(0.8, 0.8, 0.8);
	second = mat->albedo;
	inv_scale = 1;
	xInteger = (int)floor(inv_scale * rec->p.x);
	yInteger = (int)floor(inv_scale * rec->p.y);
	zInteger = (int)floor(inv_scale * rec->p.z);

	isEven = (xInteger + yInteger + zInteger) % 2 == 0;

	if (isEven)
		return (white);
	else
		return (second);
}