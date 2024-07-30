/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:53:44 by yrigny            #+#    #+#             */
/*   Updated: 2024/07/30 17:38:09 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	light_init()
{
	t_light	l;

	l.org = vec3(-40.0, 50.0, 0.0);
	l.ratio = 0.6;
	l.color.r = 10;
	l.color.g = 0;
	l.color.b = 255;
	return (l);
}

t_cam	cam_init()
{
	t_cam	c;

	c.org = vec3(0.0, 0.0, 0.0);
	c.dir = vec3(0.0, 0.0, 1.0);
	c.fov = 70;
	return (c);
}

t_viewport	viewport_init(t_cam cam)
{
	t_viewport	v;

	v.l = F_LENGTH * tan(cam.fov / 2) * 2;
	v.h = v.l / LENGTH * HEIGHT;
	// v.u = 
	// v.v = 
	return (v);
}

t_sphere	sphere_init()
{
	t_sphere	sp;

	sp.center = vec3(0.0, 0.0, 20.6);
	sp.radius = 12.6 / 2;
	sp.color.r = 10;
	sp.color.g = 0;
	sp.color.b = 255;
	return (sp);
}