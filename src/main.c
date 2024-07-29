/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/07/29 14:14:58 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//gen coord

t_coord ray_color(const ray* r) {
    // Assuming color is a struct that can be initialized like this
    t_coord c = {0, 0, 0};
    return c;
}

int main(void)
{
	t_mlx	mlx;
	t_data  img;
     double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

	//cam
	double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)image_width / image_height);
    t_coord camera_center = {0, 0, 0};

	t_coord viewport_u = {viewport_width, 0, 0};
    t_coord viewport_v = {0, -viewport_height, 0};

    t_coord pixel_delta_u = v_scale(viewport_u, 1.0 / image_width);
    t_coord pixel_delta_v = v_scale(viewport_v, 1.0 / image_height);

    t_coord viewport_upper_left = v_sub(v_sub(v_sub(camera_center, (t_coord){0, 0, focal_length}), v_scale(viewport_u, 0.5)), v_scale(viewport_v, 0.5));
    t_coord pixel00_loc = v_add(viewport_upper_left, v_scale(v_add(pixel_delta_u, pixel_delta_v), 0.5));

	
	if (!(mlx.mlx_ptr = mlx_init()))
		exit(EXIT_FAILURE);
	if (!(mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 960, 540, "MiniRT")))
		exit(EXIT_FAILURE);

	img.img = mlx_new_image(mlx.mlx_ptr, image_width, image_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	printf("P3\n%d %d\n255\n", image_width, image_height);
	for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            int r = (double)i / (image_width - 1) * 255;
            int g = (double)j / (image_height - 1) * 255;
            write_colors(&img, i, j, r, g, 0);
        }
    }


	 for (int j = 0; j < image_height; j++) {
        fprintf(stderr, "\rScanlines remaining: %d ", image_height - j);
        for (int i = 0; i < image_width; i++) {
            t_coord pixel_center = v_add(v_add(pixel00_loc, v_scale(pixel_delta_u, i)), v_scale(pixel_delta_v, j));
            t_coord ray_direction = v_sub(pixel_center, camera_center);

            ray r;
            ray_init(&r, &camera_center, &ray_direction);

            t_coord pixel_color = ray_color(&r);
            write_color(&img, i, j, pixel_color);
        }
    }
		
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img, 0, 0);
	mlx_key_hook(mlx.win_ptr, keys_handler, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, ft_exit, &mlx);
	mlx_loop(mlx.mlx_ptr);
}