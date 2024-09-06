/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:05:41 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/07 00:58:59 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	*str = malloc(sizeof(char) * (i + 1)); // Allocate memory for the string,
		including the null terminator
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

int	parse_sphere(t_scene *scene, char *line)
{
	t_vec3		position;
	double		radius;
	int			r;
	int			g;
	int			b;
	t_sphere	*sphere;
	char		*type;

	line += 2;
	while (ft_isspace(*line))
		line++;
	if (!parse_vector(&position, &line))
	{
		printf("vec issue");
		return (0);
	}
	while (ft_isspace(*line))
		line++;
	radius = ft_atof(line);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	while (ft_isspace(*line))
		line++;
	if (!get_color(&r, &g, &b, line))
	{
		printf("I FAILED");
		return (0);
	}
	while (ft_isdigit(*line) || *line == ',')
		line++;
	printf("current  char %c\n", *line);
	while (ft_isspace(*line))
		line++;
	get_string(line, &type);
	//TODO FUNCTION THAT RETURN THE TYPE IF WE KNOW IT...
	//IF WE DONT JUST RETURN MATTE
	free(type);
	sphere = create_sphere(position, radius, LIGHT, (t_vec3){r, g, b});
	scene->objects = add_sphere(scene->objects, sphere);
	return (1);
}
