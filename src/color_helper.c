/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:16:00 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/25 15:45:05 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	color_scale(t_color base, double scaler)
{
	t_color	res;

	res.r = (int)(base.r * scaler);
	res.g = (int)(base.g * scaler);
	res.b = (int)(base.b * scaler);
	return (res);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	if (res.r > 255)
		res.r = 255;
	if (res.g > 255)
		res.g = 255;
	if (res.b > 255)
		res.b = 255;
	return (res);
}

t_color	color_multiply(t_color a, t_color b)
{
	t_color	res;

	res.r = (int)(((float)a.r / 255.0) * ((float)b.r / 255.0) * 255.0);
	res.g = (int)(((float)a.g / 255.0) * ((float)b.g / 255.0) * 255.0);
	res.b = (int)(((float)a.b / 255.0) * ((float)b.b / 255.0) * 255.0);
	return (res);
}
