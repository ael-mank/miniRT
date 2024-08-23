/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:40:09 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/23 15:36:06 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	solid_color(t_material *mat, t_hitrecord *rec)
{
	(void)rec;
	return (mat->albedo);
}

t_vec3 checkerboard(t_material *mat, t_hitrecord *rec)
{
	t_vec3 white;
	t_vec3 second;
	double scale;
	int uInteger;
	int vInteger;
	int isEven;

	white = vec3(0.8, 0.8, 0.8);
	second = mat->albedo;
	scale = 60;

	// Use u and v to determine the checkerboard pattern
	uInteger = (int)floor(scale * rec->u);
	vInteger = (int)floor(scale * rec->v);

	isEven = (uInteger + vInteger) % 2 == 0;

	if (isEven)
		return (white);
	else
		return (second);
}

#include "mlx_int.h"

t_vec3 get_texture_color(t_material *mat, t_hitrecord *rec) {
    int x, y;
    int color;
    int opp;
    t_vec3 color_vec;
    t_img *img = (t_img *)mat->img->image;

    if (img == NULL || img->data == NULL) {
        fprintf(stderr, "Error: img or img->data is NULL\n");
        return (t_vec3){0, 0, 0};
    }
    opp = img->bpp / 8;
    rec->u = fmod(rec->u, 1.0);
    rec->v = fmod(rec->v, 1.0);
    if (rec->u < 0) rec->u += 1.0;
    if (rec->v < 0) rec->v += 1.0;
    x = (int)(rec->u * img->width);
    y = (int)((1.0 - rec->v) * img->height);
    if (x >= img->width) x = img->width - 1;
    if (y >= img->height) y = img->height - 1;
    // Debug prints
    // printf("Texture coordinates: u = %f, v = %f\n", rec->u, rec->v);
    // printf("Pixel coordinates: x = %d, y = %d\n", x, y);
    // printf("Image dimensions: width = %d, height = %d\n", img->width, img->height);
    // printf("Bytes per pixel: opp = %d\n", opp);
    color = *(int *)(img->data + (y * img->size_line + x * opp));
    color_vec.x = ((color >> 16) & 0xFF) / 255.0;
    color_vec.y = ((color >> 8) & 0xFF) / 255.0;
    color_vec.z = (color & 0xFF) / 255.0;
    // printf("Extracted color: R = %f, G = %f, B = %f\n", color_vec.x, color_vec.y, color_vec.z);
    return color_vec;
}