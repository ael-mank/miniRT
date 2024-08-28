#include "minirt.h"

void set_face_normal_triangle(t_hitrecord *rec, t_ray *r, t_triangle triangle)
{
    rec->normal = triangle.normal;
    rec->front_face = dot_product(r->dir, rec->normal) < 0;
    if (!rec->front_face)
    {
        rec->normal = vector_scale(rec->normal, -1);
    }
}

static inline int is_interior_triangle(double u, double v, double w, t_hitrecord *rec)
{
    // Given the hit point in barycentric coordinates, return false if it is outside the
    // primitive, otherwise set the hit record UV coordinates and return true.
    if (u < 0 || v < 0 || w < 0)
    {
        return 0;
    }
    rec->u = u;
    rec->v = v;
    return 1;
}

static inline double hit_triangle(t_ray r, t_triangle triangle, t_interval ray_t, t_hitrecord *rec)
{
    double denom;
    double t;
    t_point3 p;
    double u, v, w;

    denom = dot_product(triangle.normal, r.dir);
    // No hit if the ray is parallel to the plane.
    if (fabs(denom) < 1e-6)
    {
        return 0;
    }
    t = (triangle.d - dot_product(triangle.normal, r.org)) / denom;
    if (!contains(ray_t, t))
        return 0;
    p = ray_at(&r, t);

    // Compute barycentric coordinates
    t_vec3 v0v1 = vector_subtract(triangle.v1, triangle.v0);
    t_vec3 v0v2 = vector_subtract(triangle.v2, triangle.v0);
    t_vec3 pvec = cross_product(r.dir, v0v2);
    double det = dot_product(v0v1, pvec);

    if (fabs(det) < 1e-6)
        return 0;

    double invDet = 1 / det;

    t_vec3 tvec = vector_subtract(r.org, triangle.v0);
    u = dot_product(tvec, pvec) * invDet;
    if (u < 0 || u > 1)
        return 0;

    t_vec3 qvec = cross_product(tvec, v0v1);
    v = dot_product(r.dir, qvec) * invDet;
    if (v < 0 || u + v > 1)
        return 0;

    w = 1 - u - v;

    if (!is_interior_triangle(u, v, w, rec))
        return 0;

    // Both conditions are satisfied, proceed with the hit
    rec->t = t;
    rec->p = p;
    rec->mat = triangle.mat;
    set_face_normal_triangle(rec, &r, triangle);
    return 1;
}

double hit_triangle_wrapper(t_ray r, void *object, t_interval ray_t, t_hitrecord *rec)
{
    return hit_triangle(r, *(t_triangle *)object, ray_t, rec);
}