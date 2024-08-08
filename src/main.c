/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/08 13:42:19 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double hit_sphere(t_vec3 center, double radius, t_ray r) {
    t_vec3 oc = vector_subtract(center, r.org);
    double a = vector_length_squared(r.dir);
    double h = dot(r.dir, oc);
    double c = vector_length_squared(oc) - radius * radius;
    double discriminant = h * h - a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - sqrt(discriminant)) / a;
    }
}

t_vec3 ray_color(t_ray *r, t_object *objects) {
    t_object *current = objects;

    while (current) {
        t_sphere *sphere = (t_sphere *)current->object;
        t_vec3 center = vec3(sphere->x, sphere->y, sphere->z);
        double t = hit_sphere(center, sphere->radius, *r);
		//printf(" t val = %f", t);
        if (t > 0.0) {
			//printf("I hit\n");
            t_vec3 hit_point = ray_at(r, t);
            t_vec3 normal = vector_normalize(vector_subtract(hit_point, center));
            return vector_scale(vector_add(normal, vec3(1, 1, 1)), 0.5);
        }
        current = current->next;
    }

    // Background gradient
    t_vec3 unit_direction = vector_normalize(r->dir);
    double t = 0.5 * (unit_direction.y + 1.0);
    return vector_add(vector_scale(vec3(1.0, 1.0, 1.0), 1.0 - t), vector_scale(vec3(0.5, 0.7, 1.0), t));
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

t_object *init_objects() {
    t_object *head = malloc(sizeof(t_object));
    t_object *second = malloc(sizeof(t_object));
    t_object *third = malloc(sizeof(t_object));
    t_sphere *sphere1 = malloc(sizeof(t_sphere));
    t_sphere *sphere2 = malloc(sizeof(t_sphere));
    t_sphere *sphere3 = malloc(sizeof(t_sphere));

    if (!head || !second || !third || !sphere1 || !sphere2 || !sphere3) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }

    // Initialize the first sphere
    sphere1->x = 0.0;
    sphere1->y = 0.0;
    sphere1->z = -1.0;
    sphere1->radius = 0.5;

    // Initialize the second sphere
    sphere2->x = 1.0;
    sphere2->y = 0.0;
    sphere2->z = -1.0;
    sphere2->radius = 0.5;

    // Initialize the third sphere
    sphere3->x = -1.0;
    sphere3->y = 0.0;
    sphere3->z = -1.0;
    sphere3->radius = 0.5;

    // Set up the first object
    head->object = sphere1;
    head->hit = hit_sphere;
    head->next = second;

    // Set up the second object
    second->object = sphere2;
    second->hit = hit_sphere;
    second->next = third;

    // Set up the third object
    third->object = sphere3;
    third->hit = hit_sphere;
    third->next = NULL;

    return head;
}

void	init_scene(t_scene *scene)
{
	init_render(&scene->render);
	init_viewport(&scene->camera, &scene->render);
	init_camera(&scene->camera);
	scene->objects = init_objects();
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

void render_scene(t_scene *scene) {
    t_vec3 pixel_center;
    t_vec3 ray_dir;
    t_vec3 color;
    int i, j;

    for (j = 0; j < scene->render.image_height; ++j) {
        for (i = 0; i < scene->render.image_width; ++i) {
            pixel_center = calculate_pixel_position(i, j, &scene->camera);
            ray_dir = vector_subtract(pixel_center, scene->camera.camera_center);
            ray_init(&scene->r, &scene->camera.camera_center, &ray_dir);
            color = ray_color(&scene->r, scene->objects);
            write_colors(&scene->mlx.img, i, j, color);
        }
    }
    mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr, scene->mlx.img.img, 50, 28);
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
