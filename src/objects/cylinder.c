typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	double		radius;
	double		height;
	t_color		color;
}	t_cylinder;

t_cylinder	cylinder_init()
{
	t_cylinder	cy;

	cy.center = vec3(0, -1, 20);
	cy.axis = vec3(-0.2, 1, 0.2);
	cy.radius = 20.0 / 2;
	cy.height = 0.5;
	cy.color = color(80, 0, 180);
	return (cy);
}

void	intersect_cylinder_front(t_ray *ray, t_cam cam, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	t_vec3	temp[3];
	double	root;

	temp[0] = vector_subtract(cam.org, cy->center);
	temp[1] = cross_product(ray->dir, cy->axis);
	temp[2] = cross_product(temp[0], cy->axis);
	a = dot_product(temp[1], temp[1]);
	b = 2 * dot_product(temp[1], temp[2]);
	c = dot_product(temp[2], temp[2]) - pow(cy->radius * vector_length(cy->axis), 2);
	if (b * b - 4 * a * c >= 0)
	{
		root = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (root > 1 && (!ray->hit_object || (ray->hit_object && root < ray->hit_distance)) && in_cylinder_limit(root, cam, ray, cy))
		{
			ray->hit_object = true;
			ray->object_type = CYLINDER;
			ray->object = cy;
			ray->hit_distance = root;
			ray->intersect = vector_add(cam.org, vector_scale(ray->dir, root));
		}
	}
}

void	intersect_cylinder_back(t_ray *ray, t_cam cam, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	t_vec3	temp[3];
	double	root;

	temp[0] = vector_subtract(cam.org, cy->center);
	temp[1] = cross_product(ray->dir, cy->axis);
	temp[2] = cross_product(temp[0], cy->axis);
	a = dot_product(temp[1], temp[1]);
	b = 2 * dot_product(temp[1], temp[2]);
	c = dot_product(temp[2], temp[2]) - pow(cy->radius * vector_length(cy->axis), 2);
	if (b * b - 4 * a * c >= 0)
	{
		root = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		if (root > 1 && (!ray->hit_object || (ray->hit_object && root < ray->hit_distance)) && in_cylinder_limit(root, cam, ray, cy))
		{
			ray->hit_object = true;
			ray->object_type = CYLINDER;
			ray->object = cy;
			ray->hit_distance = root;
			ray->intersect = vector_add(cam.org, vector_scale(ray->dir, root));
		}
	}
}

bool	in_cylinder_limit(double root, t_cam c, t_ray *ray, t_cylinder *cy)
{
	t_point3	intersect_p;
	t_vec3		p_center;

	intersect_p = vector_add(c.org, vector_scale(ray->dir, root));
	p_center = vector_subtract(cy->center, intersect_p);
	if (pow(dot_product(p_center, cy->axis), 2) <= pow(cy->height / 2.0, 2))
		return (true);
	return (false);
}
