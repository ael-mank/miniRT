#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "minirt.h"

#define EPSILON 1e-4
#define NUM_THREADS 18
#define TILE_SIZE 64

typedef struct s_tile {
    int x_start, x_end, y_start, y_end;
} t_tile;

typedef struct s_render_params {
    t_scene *scene;
    t_tile *tiles;
    int tile_count;
    int *next_tile;
} t_render_params;

t_vec3 calculate_lighting(t_hitrecord *rec, t_scene *scene) {
    t_vec3 final_color = vec3(0, 0, 0);
    t_point_light *light = scene->lights;
    t_vec3 light_dir, diffuse, material_color = rec->mat->texture(rec->mat, rec);
    double light_distance, diff;
    t_ray shadow_ray;
    t_hitrecord shadow_rec;

    ft_bzero(&shadow_rec, sizeof(t_hitrecord));
    while (light != NULL) {
        light_dir = vector_subtract(light->position, rec->p);
        light_distance = vector_length(light_dir);
        light_dir = vector_normalize(light_dir);
        shadow_ray = (t_ray){rec->p, light_dir};
        if (bvh_hit(scene->bvh, shadow_ray, (t_interval){0.001, light_distance}, &shadow_rec)) {
            light = light->next;
            continue;
        }
        diff = fmax(0.0, dot(rec->normal, light_dir));
        diffuse = vector_scale(vector_multiply(material_color, light->color), diff * light->intensity);
        final_color = vector_add(final_color, diffuse);
        light = light->next;
    }
    return vector_scale(final_color, 1.5);
}

t_vec3 ray_color(t_ray *r, int depth, t_bvh *bvh, t_scene *scene) {
    t_hitrecord rec;
    t_vec3 attenuation, color_from_scatter, emission;
    t_ray scattered;
    t_scatter_params params;

    ft_bzero(&rec, sizeof(t_hitrecord));
    if (depth <= 0)
        return vec3(0, 0, 0);
    if (!bvh_hit(bvh, *r, universe_interval(), &rec))
        return scene->bg_color;

    params.r = r;
    params.rec = &rec;
    params.attenuation = &attenuation;
    params.scattered = &scattered;
    params.mat = rec.mat;

    if (!rec.mat->scatter(&params))
        return rec.mat->emission(rec.mat, &rec);

    color_from_scatter = vector_multiply(attenuation, ray_color(&scattered, depth - 1, bvh, scene));
    emission = rec.mat->emission(rec.mat, &rec);
    return vector_add(vector_add(color_from_scatter, emission), calculate_lighting(&rec, scene));
}

static inline t_vec3 defocus_disk_sample(t_camera *camera) {
    t_vec3 offset = random_in_unit_disk();
    return vector_add(camera->camera_center,
                      vector_add(vector_scale(camera->defocus_disk_u, offset.x),
                                 vector_scale(camera->defocus_disk_v, offset.y)));
}

static inline t_ray get_ray(int i, int j, t_camera *camera) {
    t_vec3 offset = sample_square();
    t_point3 pixel_sample = vector_add(camera->pixel00_loc,
                                       vector_add(vector_scale(camera->pixel_delta_u, i + offset.x),
                                                  vector_scale(camera->pixel_delta_v, j + offset.y)));
    t_vec3 ray_origin = (camera->defocus_angle <= 0) ? camera->camera_center : defocus_disk_sample(camera);
    t_vec3 ray_dir = vector_subtract(pixel_sample, ray_origin);
    t_ray r;
    ray_init(&r, &ray_origin, &ray_dir);
    return r;
}

void *render_tile(void *arg) {
    t_render_params *params = (t_render_params *)arg;
    t_scene *scene = params->scene;
    int tile_index;

    while (1) {
        tile_index = __sync_fetch_and_add(params->next_tile, 1);
        if (tile_index >= params->tile_count) break;

        t_tile tile = params->tiles[tile_index];
        for (int j = tile.y_start; j < tile.y_end; j++) {
            for (int i = tile.x_start; i < tile.x_end; i++) {
                t_vec3 color = vec3(0, 0, 0);
                for (int sample = 0; sample < scene->camera.samples_per_pixel; sample++) {
                    t_ray r = get_ray(i, j, &scene->camera);
                    color = vector_add(color, ray_color(&r, scene->camera.max_depth, scene->bvh, scene));
                }
                write_colors(&scene->mlx.img, i, j, color);
            }
        }
    }
    return NULL;
}

void create_tiles(t_tile **tiles, int *tile_count, int width, int height, int tile_size) {
    int num_x_tiles = (width + tile_size - 1) / tile_size;
    int num_y_tiles = (height + tile_size - 1) / tile_size;
    *tile_count = num_x_tiles * num_y_tiles;
    *tiles = malloc(*tile_count * sizeof(t_tile));

    for (int y = 0; y < num_y_tiles; y++) {
        for (int x = 0; x < num_x_tiles; x++) {
            int index = y * num_x_tiles + x;
            (*tiles)[index].x_start = x * tile_size;
            (*tiles)[index].x_end = (x + 1) * tile_size > width ? width : (x + 1) * tile_size;
            (*tiles)[index].y_start = y * tile_size;
            (*tiles)[index].y_end = (y + 1) * tile_size > height ? height : (y + 1) * tile_size;
        }
    }
}

void render_scene(t_scene *scene) {
    struct timeval start_time, end_time;
    pthread_t threads[NUM_THREADS];
    t_render_params params[NUM_THREADS];
    t_tile *tiles;
    int tile_count;
    int next_tile = 0;

    create_tiles(&tiles, &tile_count, scene->render.image_width, scene->render.image_height, TILE_SIZE);

    gettimeofday(&start_time, NULL);

    for (int t = 0; t < NUM_THREADS; t++) {
        params[t].scene = scene;
        params[t].tiles = tiles;
        params[t].tile_count = tile_count;
        params[t].next_tile = &next_tile;
        pthread_create(&threads[t], NULL, render_tile, &params[t]);
    }

    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;
    printf("Time to render: %.2f seconds\n", elapsed_time);

    free(tiles);

    mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr, scene->mlx.img.img, 0, 0);
}