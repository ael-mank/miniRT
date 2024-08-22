/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 08:34:56 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/22 13:06:31 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	make_matte(void)
{
	t_material	mat;

	mat.scatter = lambertian_scatter;
	mat.texture = solid_color;
	mat.fuzz = 0;
	mat.ref_indx = 0;
	return (mat);
}

t_material	make_metal(void)
{
	t_material	mat;

	mat.scatter = metal_scatter;
	mat.texture = solid_color;
	mat.fuzz = 0;
	mat.ref_indx = 0;
	return (mat);
}

t_material	make_glass(double ref_indx)
{
	t_material	mat;

	mat.scatter = glass_scatter;
	mat.texture = solid_color;
	mat.fuzz = 0;
	mat.ref_indx = ref_indx;
	return (mat);
}

t_material	make_checkerboard(void)
{
	t_material	mat;

	mat.scatter = lambertian_scatter;
	mat.texture = checkerboard;
	mat.fuzz = 0;
	mat.ref_indx = 0;
	return (mat);
}

t_material	*create_material(t_material_type type)
{
	t_material	*mat;

	mat = malloc(sizeof(t_material));
	if (!mat)
		return (NULL);
	else if (type == MATTE)
		*mat = make_matte();
	else if (type == CHECKERBOARD)
		*mat = make_checkerboard();
	else if (type == METAL)
		*mat = make_metal();
	else if (type == GLASS)
		*mat = make_glass(1.5);
	else if (type == BUBBLE)
		*mat = make_glass(1.0 / 1.5);
	else
	{
		write(1, "Invalid material type\n", 22);
		free(mat);
		return (NULL);
	}
	return (mat);
}
