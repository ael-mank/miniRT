/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:12:56 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/20 17:01:33 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//create trgb
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

//linear to gamma
double	linear_to_gamma(double linear)
{
	if (linear > 0)
		return (sqrt(linear));
	return (0);
}

//write colors
void	scale_and_correct_color(t_vec3 *color, int samples_per_pixel)
{
	double	scale;

	scale = 1.0 / samples_per_pixel;
	color->x *= scale;
	color->y *= scale;
	color->z *= scale;
	color->x = linear_to_gamma(color->x);
	color->y = linear_to_gamma(color->y);
	color->z = linear_to_gamma(color->z);
}

void	set_pixel_color(t_data *img, int x, int y, t_vec3 color)
{
	t_interval	intensity;
	int			r;
	int			g;
	int			b;
	int			res;

	intensity = (t_interval){0.000, 0.999};
	r = (int)(256 * clamp(color.x, intensity.min, intensity.max));
	g = (int)(256 * clamp(color.y, intensity.min, intensity.max));
	b = (int)(256 * clamp(color.z, intensity.min, intensity.max));
	res = create_trgb(0, r, g, b);
	my_mlx_pixel_put(img, x, y, res);
	//fprintf(out, "%d %d %d\n", r, g, b);
}

void	write_colors(t_data *img, int x, int y, t_vec3 color)
{
	scale_and_correct_color(&color, img->samples_per_pixel);
	set_pixel_color(img, x, y, color);
}
