/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:35:01 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/07 15:42:47 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_position(t_vec3 *position, char **line)
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

t_vec3 *get_u_v(t_vec3 diagonal, t_vec3 start) {
    t_vec3 *u_v = malloc(sizeof(t_vec3) * 2);
    if (!u_v)
        return NULL;

    // Calculate the u and v vectors from the diagonal vector
    t_vec3 arbitrary = (fabs(diagonal.x) > 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
    u_v[0] = cross_product(diagonal, arbitrary);
    u_v[1] = cross_product(diagonal, u_v[0]);

    // Normalize u and v vectors
    u_v[0] = vector_normalize(u_v[0]);
    u_v[1] = vector_normalize(u_v[1]);

    // Scale u and v to match the diagonal's length
    double diagonal_length = sqrt(diagonal.x * diagonal.x + diagonal.y * diagonal.y + diagonal.z * diagonal.z);
    u_v[0] = vec3(u_v[0].x * diagonal_length, u_v[0].y * diagonal_length, u_v[0].z * diagonal_length);
    u_v[1] = vec3(u_v[1].x * diagonal_length, u_v[1].y * diagonal_length, u_v[1].z * diagonal_length);

    // Adjust u and v vectors to start from the start point
    u_v[0] = vec3(start.x + u_v[0].x, start.y + u_v[0].y, start.z + u_v[0].z);
    u_v[1] = vec3(start.x + u_v[1].x, start.y + u_v[1].y, start.z + u_v[1].z);

    printf("u %f %f %f\n", u_v[0].x, u_v[0].y, u_v[0].z);
    printf("v %f %f %f\n", u_v[1].x, u_v[1].y, u_v[1].z);

    return u_v;
}

int	parse_plane(t_scene *scene, char *line)
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
	plane = create_quad(position, normale, get_type(type), vec3(r / 255.0, g / 255.0, b / 255.0));
	free(type);
	scene->objects = add_quad(scene->objects, plane);
	return (1);
}