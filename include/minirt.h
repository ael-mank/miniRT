/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:36 by ael-mank          #+#    #+#             */
/*   Updated: 2024/07/29 17:41:02 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define LENGTH 800
# define HEIGHT 600
# define F_LENGTH 1.0
# include "libft.h"
# include "mlx.h"
# include "struct.h"
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_win
{
	void			*mlx;
	void			*mlx_win;
	t_img			img;
	int				render;
}	t_win;

// event
int	win_close(t_win *e);
int	key_event(int key, t_win *e);

// raytracing
int	calculate_image(t_win *e);




#endif