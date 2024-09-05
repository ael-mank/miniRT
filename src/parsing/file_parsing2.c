/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:20:49 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/05 13:48:43 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int get_val(int *color, char **line)
{
    while (ft_isspace(**line))
        (*line)++;
    if (!ft_isdigit(**line))
        return (0);
    *color = ft_atoi(*line);
    if (*color < 0 || *color > 255)
        return (0);
    while (ft_isdigit(**line))
        (*line)++;
    return (1);
}

int get_color(int *r, int *g, int *b, char *line)
{
    if (!get_val(r, &line))
        return (0);
    if (*line != ',')
        return (0);
    line++;
    if (!get_val(g, &line))
        return (0);
    if (*line != ',')
        return (0);
    line++;
    if (!get_val(b, &line))
        return (0);
    while (ft_isspace(*line))
        line++;
    if (*line != '\0')
        return (0);
    return (1);
}

int parse_ambient(t_scene *scene, char *line)
{
    char *start;
    double ambient_value;
	int r;
	int g;
	int b;

    line++;
    while (ft_isspace(*line))
        line++;
    start = line;
    ambient_value = ft_atof(start);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	while (ft_isspace(*line))
		line++;
	if(!get_color(&r, &g, &b, line))
		return (0);
	scene->bg_color = vec3(r / 255.0, g / 255.0, b / 255.0);
	scene->bg_color = vector_scale(scene->bg_color, ambient_value);
    return (1);
}
