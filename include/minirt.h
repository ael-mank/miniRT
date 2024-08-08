/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:36 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/08 13:22:52 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include "my_mlx.h"
# include "vectors.h"
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "objects.h"
// structs
typedef struct s_render
{
	double		aspect_ratio;
	int			image_width;
	int			image_height;
}				t_render;

typedef struct s_camera
{
	double		focal_length;
	double		viewport_height;
	double		viewport_width;
	t_point3	camera_center;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;
	t_point3	viewport_upper_left;
	t_point3	pixel00_loc;
}				t_camera;

typedef struct s_scene
{
	t_mlx		mlx;
	t_camera	camera;
	t_render	render;
	t_ray		r;
	t_object	*objects;
}				t_scene;

// Memory management
int				ft_exit(t_mlx *mlx);

// Window, mlx stuff
int				keys_handler(int key_code, t_mlx *mlx);

#endif