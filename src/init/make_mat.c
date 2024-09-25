/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 08:34:56 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 12:29:53 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	make_matte(void)
{
	t_material	mat;

	mat.scatter = lambertian_scatter;
	mat.texture = solid_color;
	mat.emission = no_light;
	mat.fuzz = 0;
	mat.ref_indx = 0;
	mat.img = NULL;
	mat.normal_map = NULL;
	return (mat);
}

t_material	make_invisible(void)
{
	t_material	mat;

	mat.scatter = invisible_scatter;
	mat.texture = solid_color;
	mat.emission = no_light;
	mat.fuzz = 0;
	mat.ref_indx = 0;
	mat.img = NULL;
	mat.normal_map = NULL;
	return (mat);
}

t_material	make_light(void)
{
	t_material	mat;

	mat.scatter = light_scatter;
	mat.texture = solid_color;
	mat.emission = diffuse_light;
	mat.fuzz = 0;
	mat.ref_indx = 0;
	mat.img = NULL;
	mat.normal_map = NULL;
	return (mat);
}

t_material	make_metal(void)
{
	t_material	mat;

	mat.scatter = metal_scatter;
	mat.texture = solid_color;
	mat.emission = no_light;
	mat.fuzz = 0;
	mat.ref_indx = 0;
	mat.img = NULL;
	mat.normal_map = NULL;
	return (mat);
}

t_material	make_glass(double ref_indx)
{
	t_material	mat;

	mat.scatter = glass_scatter;
	mat.texture = solid_color;
	mat.emission = no_light;
	mat.fuzz = 0;
	mat.ref_indx = ref_indx;
	mat.img = NULL;
	mat.normal_map = NULL;
	return (mat);
}
