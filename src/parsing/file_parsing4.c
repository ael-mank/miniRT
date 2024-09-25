/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:35:01 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 10:58:19 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int 	parse_position(t_vec3 *position, char **line)
{
    *line += 2;
    while (ft_isspace(**line))
        (*line)++;
    if (!parse_vector(position, line))
        return (0);
    while (ft_isspace(**line))
        (*line)++;
    return (1);
}

double parse_radius(char **line)
{
    double radius = ft_atof(*line);
    while (ft_isdigit(**line) || **line == '.')
        (*line)++;
    while (ft_isspace(**line))
        (*line)++;
    return radius;
}

int parse_color(int *r, int *g, int *b, char **line)
{
    if (!get_color(r, g, b, *line))
        return (0);
    while (ft_isdigit(**line) || **line == ',')
        (*line)++;
    while (ft_isspace(**line))
        (*line)++;
    return (1);
}

t_vec3 *get_u_v(t_vec3 Q, t_vec3 diagonal) {
    t_vec3 *u_v = malloc(sizeof(t_vec3) * 2);
    if (!u_v) return NULL;

    // Calculate the length of the diagonal
    double diagonal_length = vector_length(diagonal);
    
    // Calculate the side length of the square
    double side_length = diagonal_length / sqrt(2);
    
    // Create a unit vector in the direction of the diagonal
    t_vec3 d_unit = vector_normalize(diagonal);
    
    // Create a perpendicular vector using cross product
    t_vec3 ref = vec3(0, 0, 1);
    if (fabs(d_unit.x) < 1e-6 && fabs(d_unit.y) < 1e-6 && fabs(fabs(d_unit.z) - 1) < 1e-6) {
        ref = vec3(1, 0, 0);
    }
    (void)Q;
    t_vec3 perp = cross_product(d_unit, ref);
    t_vec3 perp_unit = vector_normalize(perp);
    
    // Calculate u and v vectors
    t_vec3 u_dir = vector_add(d_unit, perp_unit);
    t_vec3 v_dir = vector_subtract(d_unit, perp_unit);
    
    t_vec3 u = vector_scale(u_dir, side_length / sqrt(2));
    t_vec3 v = vector_scale(v_dir, side_length / sqrt(2));
    
    u_v[0] = u;
    u_v[1] = v;

    return u_v;
}

int	parse_square(t_scene *scene, char *line)
{
	t_vec3		position;
	t_vec3		normale;
	t_quad		*plane;
	char		*type;

	int			r, g, b;
	if (!parse_position(&position, &line))
		return (0);
	if (!parse_vector(&normale, &line))
		return (0);
	if (!parse_color(&r, &g, &b, &line))
		return (0);
	get_string(line, &type);
	// t_vec3 u = vec3(0, 0, 20);
	// t_vec3 v = vec3(20, 0, 0);
	//plane =create_quad((t_point3){268,268,268}, (t_vec3){555, 0, 0}, (t_vec3){0, -555, 0}, MATTE, (t_vec3){0.73, 0, 0});
	free(type);
	scene->objects = add_quad(scene->objects, plane);
	return (1);
}

int	parse_plane(t_scene *scene, char *line)
{
	t_vec3		position;
	t_vec3		normale;
	t_plane		*plane;
	char		*type;

	int			r, g, b;
	if (!parse_position(&position, &line))
		return (0);
	if (!parse_vector(&normale, &line))
		return (0);
	if (!parse_color(&r, &g, &b, &line))
		return (0);
	while (ft_isdigit(*line) || *line == ',' || ft_isspace(*line))
		line++;
	get_string(line, &type);
	plane = create_plane(position, normale, get_type(type), vec3(r/255.0, g/255.0, b/255.0));
	free(type);
	scene->objects = add_plane(scene->objects, plane);
	return (1);
}
