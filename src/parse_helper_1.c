/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:05:04 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/16 20:04:25 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define INTEGER 1
#define FLOAT 2

bool	parse_ratio(char **line, double *ratio)
{
	char	*tmp;
	int		i;
	bool	res;

	while (ft_isspace(**line))
		(*line)++;
	tmp = *line;
	if (*tmp == '\0')
		return (false);
	i = 0;
	while (!ft_isspace(tmp[i]))
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, *line, i + 1);
	if (!is_float_format(tmp))
		res = false;
	else
	{
		*ratio = ft_atof(tmp);
		if (*ratio < 0.0 || *ratio > 1.0)
			res = false;
		else
			res = true;
	}
	free(tmp);
	*line += i;
	return (res);
}

bool	parse_color(char **line, t_color *color)
{
	char	*tmp;
	int		i;
	bool	res;

	while (ft_isspace(**line))
		(*line)++;
	tmp = *line;
	if (*tmp == '\0')
		return (false);
	i = 0;
	while (!ft_isspace(tmp[i]))
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, *line, i + 1);
	if (!is_vec3_format(tmp, INTEGER))
		res = false;
	else
	{
		*color = ft_atorgb(tmp);
		res = true;
		if (!(color->r >= 0 && color->r <= 255 && color->g >= 0 && color->g <= 255
			&& color->b >= 0 && color->b <= 255))
			res = false;
	}
	free(tmp);
	*line += i;
	return (res);
}

bool	is_vec3_format(char *s, int type)
{
	int		nb_parts;
	char	**parts;
	bool	res;

	nb_parts = count_parts(s, ',');
	parts = NULL;
	if (nb_parts != 3)
		res = false;
	else
	{
		parts = ft_split(s, ',');
		if (type == INTEGER &&
			str_is_int(parts[0]) && str_is_int(parts[1]) && str_is_int(parts[2]))
			res = true;
		else if (type == FLOAT && is_float_format(parts[0]) && is_float_format(parts[1])
			&& is_float_format(parts[2]))
			res = true;
		else
			res = false;
		free(parts[0]);
		free(parts[1]);
		free(parts[2]);
		free(parts);
	}
	return (res);
}

t_color	ft_atorgb(char *s)
{
	char	**parts;
	t_color	color;

	parts = ft_split(s, ',');
	// printf("%s %s %s\n", parts[0], parts[1], parts[2]);
	color.r = ft_atoi(parts[0]);
	color.g = ft_atoi(parts[1]);
	color.b = ft_atoi(parts[2]);
	// printf("%d %d %d\n", color.r, color.g, color.b);
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (color);
}

t_vec3	ft_atovec3(char *s)
{
	char	**parts;
	t_vec3	vec;

	parts = ft_split(s, ',');
	vec.x = ft_atof(parts[0]);
	vec.y = ft_atof(parts[1]);
	vec.z = ft_atof(parts[2]);
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (vec);
}
