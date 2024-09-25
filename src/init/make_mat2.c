/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_mat2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:29:33 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 12:34:40 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	make_checkerboard(void)
{
	t_material	mat;

	mat.scatter = lambertian_scatter;
	mat.texture = checkerboard;
	mat.emission = no_light;
	mat.fuzz = 0;
	mat.ref_indx = 0;
	mat.img = NULL;
	mat.normal_map = NULL;
	return (mat);
}

//code load img
t_texture	*load_img(char *path)
{
	t_texture	*img;

	img = malloc(sizeof(t_texture));
	if (!img)
		return (NULL);
	ft_bzero(img, sizeof(t_texture));
	img->image = mlx_xpm_file_to_image(get_mlx_ptr(), path, &img->width,
			&img->height);
	if (!img->image)
	{
		free(img);
		return (NULL);
	}
	img->data = mlx_get_data_addr(img->image, &img->bpp, &img->size_line,
			&img->endian);
	return (img);
}

t_material	make_globe(void)
{
	t_material	mat;
	t_texture	*texture;
	t_texture	*normal;

	mat.scatter = lambertian_scatter;
	mat.texture = get_texture_color;
	mat.emission = no_light;
	texture = load_img("earthmap.xpm");
	if (!texture)
	{
		ft_printf("Error loading texture\n");
		exit(EXIT_FAILURE);
	}
	normal = load_img("earthnormal.xpm");
	if (!normal)
	{
		ft_printf("Error loading normal map\n");
		exit(EXIT_FAILURE);
	}
	mat.img = texture;
	mat.normal_map = normal;
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
	else if (type == INVISIBLE)
		*mat = make_invisible();
	else if (type == MATTE)
		*mat = make_matte();
	else if (type == LIGHT)
		*mat = make_light();
	else if (type == CHECKERBOARD)
		*mat = make_checkerboard();
	else if (type == GLOBE)
		*mat = make_globe();
	else if (type == METAL)
		*mat = make_metal();
	else if (type == GLASS)
		*mat = make_glass(1.5);
	return (mat);
}
