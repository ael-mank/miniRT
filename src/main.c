/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/05 12:37:45 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ray_color(t_ray *r)
{
	t_vec3	unit_direction = vector_normalize(r->dir);
	double t = 0.5 * (unit_direction.y + 1.0);
	return (vector_add(vector_scale(vec3(1.0, 1.0, 1.0), 1.0 - t), vector_scale(vec3(0.5, 0.7, 1.0), t)));
}

void init_mlx(t_mlx *mlx, t_data *img, int win_width, int win_height, int image_width, int image_height) {
    if (!(mlx->mlx_ptr = mlx_init()))
        exit(EXIT_FAILURE);
    if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, win_width, win_height, "MiniRT")))
        exit(EXIT_FAILURE);
    img->img = mlx_new_image(mlx->mlx_ptr, image_width, image_height);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}

void init_camera(double *aspect_ratio, int *image_width, int *image_height, t_vec3 *viewport_u, t_vec3 *viewport_v, t_vec3 *pixel_delta_u, t_vec3 *pixel_delta_v, t_vec3 *viewport_upper_left, t_vec3 *pixel00_loc, double viewport_height) {
    *aspect_ratio = 16.0 / 9.0;
    *image_height = (int)(*image_width / *aspect_ratio);
    *image_height = (*image_height < 1) ? 1 : *image_height;
    double viewport_width = viewport_height * (*image_width / (double)*image_height);
    double focal_length = 1.0;
    t_point3 camera_center = vec3(0, 0, 0);
    *viewport_u = vec3(viewport_width, 0, 0);
    *viewport_v = vec3(0, -viewport_height, 0);
    *pixel_delta_u = vector_divide(*viewport_u, *image_width);
    *pixel_delta_v = vector_divide(*viewport_v, *image_height);
    viewport_upper_left->x = camera_center.x - (viewport_u->x / 2) - (viewport_v->x / 2);
    viewport_upper_left->y = camera_center.y - (viewport_u->y / 2) - (viewport_v->y / 2);
    viewport_upper_left->z = camera_center.z - focal_length - (viewport_u->z / 2) - (viewport_v->z / 2);
    pixel00_loc->x = viewport_upper_left->x + 0.5 * (pixel_delta_u->x + pixel_delta_v->x);
    pixel00_loc->y = viewport_upper_left->y + 0.5 * (pixel_delta_u->y + pixel_delta_v->y);
    pixel00_loc->z = viewport_upper_left->z + 0.5 * (pixel_delta_u->z + pixel_delta_v->z);
}

t_vec3 calculate_pixel_position(int i, int j, t_vec3 pixel00_loc, t_vec3 pixel_delta_u, t_vec3 pixel_delta_v) {
    t_vec3 pixel_center;
    pixel_center.x = pixel00_loc.x + (i * pixel_delta_u.x) + (j * pixel_delta_v.x);
    pixel_center.y = pixel00_loc.y + (i * pixel_delta_u.y) + (j * pixel_delta_v.y);
    pixel_center.z = pixel00_loc.z + (i * pixel_delta_u.z) + (j * pixel_delta_v.z);
    return pixel_center;
}

void render_scene(t_data *img, int image_width, int image_height, t_vec3 pixel00_loc, t_vec3 pixel_delta_u, t_vec3 pixel_delta_v, t_point3 camera_center) {
    t_ray r;
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            t_vec3 pixel_center = calculate_pixel_position(i, j, pixel00_loc, pixel_delta_u, pixel_delta_v);
            t_vec3 ray_dir = vector_subtract(pixel_center, camera_center);
            ray_init(&r, &camera_center, &ray_dir);
            t_vec3 color = ray_color(&r);
            write_colors(img, i, j, color);
        }
    }
}

int main(void) {
    t_mlx mlx;
    t_data img;
    int win_width = 960;
    int win_height = 540;
    double aspect_ratio;
    int image_width = 860;
    int image_height;
    double viewport_height = 2.0;
    t_vec3 viewport_u, viewport_v, pixel_delta_u, pixel_delta_v, viewport_upper_left, pixel00_loc;

    init_camera(&aspect_ratio, &image_width, &image_height, &viewport_u, &viewport_v, &pixel_delta_u, &pixel_delta_v, &viewport_upper_left, &pixel00_loc, viewport_height);
    init_mlx(&mlx, &img, win_width, win_height, image_width, image_height);
    render_scene(&img, image_width, image_height, pixel00_loc, pixel_delta_u, pixel_delta_v, vec3(0, 0, 0));

    int x = (win_width - image_width) / 2;
    int y = (win_height - image_height) / 2;
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img, x, y);
    mlx_key_hook(mlx.win_ptr, keys_handler, &mlx);
    mlx_hook(mlx.win_ptr, 17, 0, ft_exit, &mlx);
    mlx_loop(mlx.mlx_ptr);
}