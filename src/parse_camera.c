#include "minirt.h"

bool	parse_and_add_camera(char *line, t_cam *c)
{
	if (c != NULL)
	{
		ft_putstr_fd("Error: Camera can only be declared once.\n", 2);
		return (false);
	}
	c = malloc(sizeof(t_cam));
	if (c == NULL)
		return (false);
	if (!parse_point(&line, &c->org))
	{
		ft_putstr_fd("Error: Camera's view point is invalid\n", 2);
		free(c);
		return (false);
	}
	if (!parse_direction(&line, &c->dir))
	{
		ft_putstr_fd("Error: Camera's orientation is invalid\n", 2);
		ft_putstr_fd("Orientation must have x, y, z axis in range [-1,1]\n", 1);
		free(c);
		return (false);
	}
	if (!parse_fov(&line, &c->fov))
	{
		
		ft_putstr_fd("Error: Camera's field of view is invalid\n", 2);
		ft_putstr_fd("Field of view must be in range [0,180]\n", 1);
		free(c);
		return (false);
	}	
	while (ft_isspace(*line))
		line++;
	if (*line == '\0')
	{
		printf("Camera | View point: %.1f,%.1f,%.1f | Orientation: %.1f,%.1f,%.1f | FOV: %.0f\n", c->org.x, c->org.y, c->org.z, c->dir.x, c->dir.y, c->dir.z, c->fov);
		return (true);
	}
	free(c);
	ft_putstr_fd("Error: Camera has noise information\n", 2);
	return (false);
}

bool	parse_point(char **line, t_vec3 *point)
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
	if (!is_vec3_format(tmp, FLOAT))
		res = false;
	else
	{
		*point = ft_atovec3(tmp);
		res = true;
	}
	free(tmp);
	*line += i;
	return (res);
}

bool	parse_direction(char **line, t_vec3 *vec)
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
	if (!is_vec3_format(tmp, FLOAT))
		res = false;
	else
	{
		*vec = ft_atovec3(tmp);
		res = true;
		if (!(vec->x >= -1 && vec->x <= 1 && vec->y >= -1 && vec->y <= 1
			&& vec->z >= -1 && vec->z <= 1))
			res = false;
	
	}
	free(tmp);
	*line += i;
	return (res);

}

bool	parse_fov(char **line, double *fov)
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
		*fov = ft_atof(tmp);
		if (*fov < 0 || *fov > 180)
			res = false;
		else
			res = true;
	}
	free(tmp);
	*line += i;
	return (res);

}
