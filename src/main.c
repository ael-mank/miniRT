/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/07 12:16:25 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(t_vec3 center, double radius, t_ray r)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;

	oc = vector_subtract(center, r.org);
	a = vector_length_squared(r.dir);
	h = dot(r.dir, oc);
	c = vector_length_squared(oc) - radius * radius;
	discriminant = h*h - a * c;
	if (discriminant < 0)
	{
		return (-1.0);
	}
	else
	{
		return (h - sqrt(discriminant)) / a;
	}
}

t_vec3 ray_color(t_ray *r)
{
    t_vec3 unit_direction;
    double a;
    double t;

    t = hit_sphere(vec3(0, -100.5, -1), 100, *r);
    if (t > 0.0)
    {
        t_vec3 n;
        n = vector_normalize(vector_subtract(ray_at(r, t), vec3(0, 0, -1)));
        return vector_scale(vec3(n.x + 1, n.y + 1, n.z + 1), 0.5);
    }
    unit_direction = vector_normalize(r->dir);
    a = 0.5 * (unit_direction.y + 1.0);
    return vector_add(vector_scale(vec3(1.0, 1.0, 1.0), 1.0 - a),
                      vector_scale(vec3(0.5, 0.7, 1.0), a));
}

void	init_mlx(t_scene *scene, int win_width, int win_height)
{
	t_mlx	*mlx;
	t_data	*img;

	mlx = &scene->mlx;
	img = &mlx->img;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit(EXIT_FAILURE);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, win_width, win_height,
			"MiniRT");
	if (!mlx->win_ptr)
		exit(EXIT_FAILURE);
	img->img = mlx_new_image(mlx->mlx_ptr, scene->render.image_width,
			scene->render.image_height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	init_camera(t_camera *camera)
{
	camera->focal_length = 1.0;
	camera->camera_center = vec3(0, 0, 0);
	camera->viewport_upper_left.x = camera->camera_center.x
		- (camera->viewport_u.x / 2) - (camera->viewport_v.x / 2);
	camera->viewport_upper_left.y = camera->camera_center.y
		- (camera->viewport_u.y / 2) - (camera->viewport_v.y / 2);
	camera->viewport_upper_left.z = camera->camera_center.z
		- camera->focal_length - (camera->viewport_u.z / 2)
		- (camera->viewport_v.z / 2);
	camera->pixel00_loc.x = camera->viewport_upper_left.x + 0.5
		* (camera->pixel_delta_u.x + camera->pixel_delta_v.x);
	camera->pixel00_loc.y = camera->viewport_upper_left.y + 0.5
		* (camera->pixel_delta_u.y + camera->pixel_delta_v.y);
	camera->pixel00_loc.z = camera->viewport_upper_left.z + 0.5
		* (camera->pixel_delta_u.z + camera->pixel_delta_v.z);
}

void	init_viewport(t_camera *camera, t_render *render)
{
	camera->viewport_height = 2.0;
	camera->viewport_width = camera->viewport_height * (render->image_width
			/ (double)render->image_height);
	camera->viewport_u = vec3(camera->viewport_width, 0, 0);
	camera->viewport_v = vec3(0, -camera->viewport_height, 0);
	camera->pixel_delta_u = vector_divide(camera->viewport_u,
			render->image_width);
	camera->pixel_delta_v = vector_divide(camera->viewport_v,
			render->image_height);
}

void	init_render(t_render *render)
{
	render->aspect_ratio = 16.0 / 9.0;
	render->image_width = 860;
	render->image_height = (int)(render->image_width / render->aspect_ratio);
	if (render->image_height < 1)
		render->image_height = 1;
}

void	init_scene(t_scene *scene)
{
	init_render(&scene->render);
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
}

t_vec3	calculate_pixel_position(int i, int j, t_camera *camera)
{
	t_vec3	pixel_center;

	pixel_center.x = camera->pixel00_loc.x + (i * camera->pixel_delta_u.x) + (j
			* camera->pixel_delta_v.x);
	pixel_center.y = camera->pixel00_loc.y + (i * camera->pixel_delta_u.y) + (j
			* camera->pixel_delta_v.y);
	pixel_center.z = camera->pixel00_loc.z + (i * camera->pixel_delta_u.z) + (j
			* camera->pixel_delta_v.z);
	return (pixel_center);
}

void	render_scene(t_scene *scene)
{
	t_vec3	pixel_center;
	t_vec3	ray_dir;
	t_vec3	color;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < scene->render.image_height)
	{
		while (i < scene->render.image_width)
		{
			pixel_center = calculate_pixel_position(i, j, &scene->camera);
			ray_dir = vector_subtract(pixel_center,
					scene->camera.camera_center);
			ray_init(&scene->r, &scene->camera.camera_center, &ray_dir);
			color = ray_color(&scene->r);
			write_colors(&scene->mlx.img, i, j, color);
			i++;
		}
		mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
			scene->mlx.img.img, 50, 28);
		i = 0;
		j++;
	}
}

int	main(void)
{
	t_scene	scene;
	int		win_width;
	int		win_height;
	int		x;
	int		y;

	ft_bzero(&scene, sizeof(t_scene));
	win_width = 960;
	win_height = 540;
	init_scene(&scene);
	init_mlx(&scene, win_width, win_height);
	render_scene(&scene);
	x = (win_width - scene.render.image_width) / 2;
	y = (win_height - scene.render.image_height) / 2;
	printf("x: %d, y: %d\n", x, y);
	mlx_key_hook(scene.mlx.win_ptr, keys_handler, &scene.mlx);
	mlx_hook(scene.mlx.win_ptr, 17, 0, ft_exit, &scene.mlx);
	mlx_loop(scene.mlx.mlx_ptr);
}
