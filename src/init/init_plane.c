#include "minirt.h"

// Define a more reasonable large interval based on scene scale
#define VIEW_DISTANCE 33

#define large_interval (t_interval){-VIEW_DISTANCE, VIEW_DISTANCE}



t_plane *create_plane(t_point3 point, t_vec3 normal, t_material_type type, t_vec3 color) {
    t_plane *plane;
    t_material *mat;

    plane = malloc(sizeof(t_plane));
    if (!plane)
        return (NULL);
    mat = create_material(type);
    if (!mat) {
        free(plane);
        return (NULL);
    }
    mat->albedo = color;
    plane->mat = mat;
    plane->point = point;
    plane->normal = unit_vector(normal); // Ensure the normal is normalized
    plane->d = dot_product(plane->normal, point);
    return (plane);
}

t_object *add_plane(t_object *head, t_plane *plane) {
    t_object *new_object;
    t_aabb box;
    t_interval *plane_interval_ptr = get_plane_interval();

    new_object = malloc(sizeof(t_object));
    if (!new_object)
        return (NULL);
    if (!plane) {
        free(new_object);
        return (NULL);
    }
    new_object->object = plane;
    new_object->mat = plane->mat;
    new_object->hit = hit_plane_wrapper;
    new_object->free = free_plane;
    t_interval x = (plane->normal.x == 0) ? *plane_interval_ptr : interval(plane->point.x, plane->point.x);
    t_interval y = (plane->normal.y == 0) ? *plane_interval_ptr : interval(plane->point.y, plane->point.y);
    t_interval z = (plane->normal.z == 0) ? *plane_interval_ptr : interval(plane->point.z, plane->point.z);
    box = aabb(x, y, z);
    new_object->box = box;
    new_object->next = NULL;
    return (add_object_end(head, new_object));
}