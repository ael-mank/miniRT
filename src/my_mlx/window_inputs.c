/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:55:32 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 12:08:23 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void	moove_right(t_scene *scene)
{
	// mlx_clear_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	// Move the camera to the right by a fixed amount
	scene->camera.lookfrom.x += 100.0;
	scene->camera.lookat.x += 100.0;
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	render_scene(scene);
}

void	moove_left(t_scene *scene)
{
	// Move the camera to the left by a fixed amount
	mlx_clear_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	scene->camera.lookfrom.x -= 100.0;
	scene->camera.lookat.x -= 100.0;
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	render_scene(scene);
}

void	moove_forward(t_scene *scene)
{
	// Move the camera forward by a fixed amount
	mlx_clear_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	scene->camera.lookfrom.z += 100.0;
	scene->camera.lookat.z += 100.0;
	printf("forward\n");
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	render_scene(scene);
}

void	moove_backwards(t_scene *scene)
{
	// Move the camera backwards by a fixed amount
	mlx_clear_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	scene->camera.lookfrom.z -= 100.0;
	scene->camera.lookat.z -= 100.0;
	printf("backwards\n");
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	render_scene(scene);
}

void	moove_up(t_scene *scene)
{
	// Move the camera up by a fixed amount
	mlx_clear_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	scene->camera.lookfrom.y += 100.0;
	scene->camera.lookat.y += 100.0;
	printf("up\n");
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	render_scene(scene);
}

void	moove_down(t_scene *scene)
{
	// Move the camera down by a fixed amount
	mlx_clear_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	scene->camera.lookfrom.y -= 100.0;
	scene->camera.lookat.y -= 100.0;
	printf("down\n");
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	render_scene(scene);
}

static inline int get_pixel_color(t_data *data, int x, int y) {
    char *pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
    return *(int *)pixel;
}

void save_image(t_scene *scene) {
    char filename[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(filename, sizeof(filename) - 1, "screenshot_%Y-%m-%d_%H-%M-%S.png", t);
    int width = 960;
    int height = 540;
    int channels = 4;
    unsigned char *image_data = (unsigned char *)malloc(width * height * channels);
	int index = 0;
	int y = 0;
	while (y < height) {
		int x = 0;
		while (x < width) {
			int color = get_pixel_color(&scene->mlx.img, x, y);
			image_data[index + 0] = (color >> 16) & 0xFF; 
			image_data[index + 1] = (color >> 8) & 0xFF;  
			image_data[index + 2] = color & 0xFF;         
			image_data[index + 3] = 0xFF;                
			index += channels;
			x++;
		}
		y++;
	}
    stbi_write_png(filename, width, height, channels, image_data, width * channels);
    free(image_data);
    ft_printf("Image saved as %s\n", filename);
}

int keys_handler(int key_code, t_scene *scene)
{
    if (key_code == XK_Escape)
        ft_exit(scene);
    else if (key_code == XK_Right)
        moove_right(scene);
    else if (key_code == XK_Left)
        moove_left(scene);
    else if (key_code == XK_Up)
        moove_forward(scene);
    else if (key_code == XK_Down)
        moove_backwards(scene);
    else if (key_code == XK_space)
        moove_up(scene);
    else if (key_code == XK_Control_L || key_code == XK_Control_R)
        moove_down(scene);
    return (0);
}
