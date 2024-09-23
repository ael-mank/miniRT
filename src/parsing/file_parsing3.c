/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:05:41 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/23 09:58:55 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_double(double *value, char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line) && **line != '-' && **line != '+')
		return (0);
	*value = ft_atof(*line);
	if (**line == '-' || **line == '+')
		(*line)++;
	while (ft_isdigit(**line) || **line == '.')
		(*line)++;
	return (1);
}

int	parse_light(t_scene *scene, char *line)
{
	t_vec3	position;
	double	ambient_value;
	int		r;
	int		g;
	int		b;

	line++;
	while (ft_isspace(*line))
		line++;
	if (!parse_vector(&position, &line))
	{
		return (0);
	}
	while (ft_isspace(*line))
		line++;
	ambient_value = ft_atof(line);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	while (ft_isspace(*line))
		line++;
	if (!get_color(&r, &g, &b, line))
		return (0);
	add_light(scene, position, vec3(r / 255.0, g / 255.0, b / 255.0),
		ambient_value);
	return (1);
}

void	get_string(char *line, char **str)
{
	int		i;
	char	*start;

	i = 0;
	start = line;
	while (*line && !ft_isspace(*line))
	{
		line++;
		i++;
	}
	*str = malloc(sizeof(char) * (i + 1));
	if (!*str)
		return ;
	line = start;
	i = 0;
	while (*line && !ft_isspace(*line))
	{
		(*str)[i] = *line;
		i++;
		line++;
	}
	(*str)[i] = '\0';
}

t_material_type	get_type(char *line)
{
	if (!ft_strncmp(line, "matte", 5))
		return (MATTE);
	else if (!ft_strncmp(line, "metal", 5))
		return (METAL);
	else if (!ft_strncmp(line, "glass", 5))
		return (GLASS);
	else if (!ft_strncmp(line, "globe", 6))
		return (GLOBE);
	else if (!ft_strncmp(line, "light", 5))
		return (LIGHT);
	else if (!ft_strncmp(line, "checkerboard", 13))
		return (CHECKERBOARD);
	else
	{
		if (line[0] != '\0')
		{
			ft_printf("\e[1;31mError :");
			ft_printf("\t%s\n\033[0m", "Unrecognized material type replaced by matte");
		}
		return (MATTE);
	}
}

int	parse_sphere(t_scene *scene, char *line)
{
	t_vec3		position;
	double		radius;
	t_sphere	*sphere;
	char		*type;

	int			r, g, b;
	if (!parse_position(&position, &line))
		return (0);
	radius = parse_radius(&line);
	radius /= 2;
	if (!parse_color(&r, &g, &b, &line))
		return (0);
	get_string(line, &type);
	sphere = create_sphere(position, radius, get_type(type), (t_vec3){r / 255.0,
			g / 255.0, b / 255.0});
	free(type);
	scene->objects = add_sphere(scene->objects, sphere);
	return (1);
}
