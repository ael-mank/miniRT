/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:37:46 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/23 11:35:43 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H

# include <vectors.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		samples_per_pixel;
}				t_data;

typedef struct s_texture
{
	void    *image;
    char    *data;
    int     width;
    int     height;
    int     size_line;
    int     bpp;
    int     type;
	int    endian;
}			t_texture;
typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_data			img;
}					t_mlx;



void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	write_colors(t_data *img, int x, int y, t_vec3 color);

#endif