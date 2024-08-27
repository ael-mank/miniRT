/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:53:44 by yrigny            #+#    #+#             */
/*   Updated: 2024/08/27 14:22:19 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	light_init()
{
	t_light	l;

	l.org = vec3(0, 10, 10);
	l.ratio = 0.6;
	l.color.r = 255;
	l.color.g = 255;
	l.color.b = 255;
	return (l);
}

t_ambient	ambient_init()
{
	t_ambient	a;

	a.color.r = 50;
	a.color.g = 50;
	a.color.b = 200;
	a.ratio = 0.6;
	return (a);
}

t_cam	cam_init()
{
	t_cam	c;

	c.org = vec3(0, 0, 0);
	c.dir = vec3(0, 0, 1);
	c.fov = 90;
	c.theta_radian = c.fov / 2 * (PI / 180);
	return (c);
}

t_viewport	viewport_init(t_cam cam)
{
	t_viewport	v;

	v.w = F_LENGTH * tan(cam.theta_radian) * 2;
	v.h = v.w / LENGTH * HEIGHT;
	v.u = vec3(v.w, 0, 0);
	v.v = vec3(0, -v.h, 0);
	v.pixel_delta_u = vector_scale(v.u, 1.0 / LENGTH);
	v.pixel_delta_v = vector_scale(v.v, 1.0 / HEIGHT);
	v.upperleft = vector_subtract(vector_add(cam.org, vector_scale(cam.dir, F_LENGTH)), vector_add(vector_scale(v.u, 0.5), vector_scale(v.v, 0.5)));
	v.pixel00 = vector_add(v.upperleft, vector_scale(vector_add(v.pixel_delta_u, v.pixel_delta_v), 0.5));
	return (v);
}

t_sphere	sphere_init()
{
	t_sphere	sp;

	sp.center = vec3(0, 0, 20.6);
	sp.radius = 12.6 / 2;
	sp.color.r = 255;
	sp.color.g = 0;
	sp.color.b = 55;
	return (sp);
}
