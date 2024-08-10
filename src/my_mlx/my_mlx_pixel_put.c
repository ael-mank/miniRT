/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:38:55 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/10 16:04:46 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"
#include "vectors.h"
#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//create trgb

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

//write colors

void write_colors(t_data *img, int x, int y, t_vec3 color, int samples_per_pixel) {
    int r, g, b, res;
    t_interval intensity;
    intensity.min = 0.000;
    intensity.max = 0.999;

    // Average the color values
    double scale = 1.0 / samples_per_pixel;
    color.x *= scale;
    color.y *= scale;
    color.z *= scale;

    // Clamp and scale the color values
    r = (int)(256 * clamp(color.x, intensity.min, intensity.max));
    g = (int)(256 * clamp(color.y, intensity.min, intensity.max));
    b = (int)(256 * clamp(color.z, intensity.min, intensity.max));

    // Create the color value and write the pixel
    res = create_trgb(0, r, g, b);
    my_mlx_pixel_put(img, x, y, res);
	//fprintf(out, "%d %d %d\n", r, g, b);
}


// void	old_write_colors(t_data *img, int x, int y, t_vec3 color)
// {
// 	int	r;
// 	int	g;
// 	int	b;
// 	int	res;

// 	r = (int)(255.999 * color.x);
// 	g = (int)(255.999 * color.y);
// 	b = (int)(255.999 * color.z);
// 	res = create_trgb(0, r, g, b);
// 	my_mlx_pixel_put(img, x, y, res);
// }