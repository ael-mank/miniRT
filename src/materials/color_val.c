/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:40:09 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/17 13:47:08 by ael-mank         ###   ########.fr       */
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
	double	scale;
	int		uinteger;
	int		vinteger;
	int		iseven;

	scale = 15;
	uinteger = (int)floor(scale * rec->u);
	vinteger = (int)floor(scale * rec->v);
	iseven = (uinteger + vinteger) % 2 == 0;
	if (iseven)
		return (vec3(0, 0, 0));
	else
		return (mat->albedo);
}

t_vec3	get_texture_color(t_material *mat, t_hitrecord *rec)
{
	int		x;
	int		y;
	int		color;
	t_vec3	color_vec;
	t_img	*img;

	img = (t_img *)mat->img->image;
	if (img == NULL || img->data == NULL)
		return ((t_vec3){0, 0, 0});
	rec->u = fmod(rec->u, 1.0);
	rec->v = fmod(rec->v, 1.0);
	if (rec->u < 0)
		rec->u += 1.0;
	if (rec->v < 0)
		rec->v += 1.0;
	x = (int)(rec->u * img->width);
	y = (int)((1.0 - rec->v) * img->height);
	if (x >= img->width)
		x = img->width - 1;
	if (y >= img->height)
		y = img->height - 1;
	color = *(int *)(img->data + (y * img->size_line + x * img->bpp / 8));
	color_vec.x = ((color >> 16) & 0xFF) / 255.0;
	color_vec.y = ((color >> 8) & 0xFF) / 255.0;
	color_vec.z = (color & 0xFF) / 255.0;
	return (color_vec);
}
