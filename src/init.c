/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:53:44 by yrigny            #+#    #+#             */
/*   Updated: 2024/08/29 18:05:30 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	light_init()
{
	t_light	l;

	// l.org = vec3(-40, 0, 30);
	l.org = vec3(0, 10, 0);
	l.ratio = 0.7;
	l.color = color(255, 255, 255);
	return (l);
}

t_ambient	ambient_init()
{
	t_ambient	a;

	a.color = color(50, 50, 200);
	// a.color = color(255, 255, 255);
	a.ratio = 0.2;
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

	sp.center = vec3(0, 0, 20);
	sp.radius = 10 / 2;
	sp.color = color(255, 0, 55);
	return (sp);
}

t_plane		plane_init()
{
	t_plane	pl;

	pl.point_instance = vec3(0, -10, 0);
	pl.normal = vec3(0, 1, 0);
	pl.color = color(200, 200, 200);
	return (pl);
}

t_cylinder	cylinder_init()
{
	t_cylinder	cy;

	cy.center = vec3(0, -1, 20);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 20.0 / 2;
	cy.height = 0.5;
	cy.radial_len = sqrt(pow(cy.radius, 2) + pow(cy.height / 2.0, 2));
	cy.color = color(80, 0, 180);
	return (cy);
}
