#include "minirt.h"

bool	parse_and_add_sphere(char *line, t_scene *scene)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (sp == NULL)
			return (false);
	while (!ft_isspace(*line))
		line++;
	if (!parse_point(&line, &sp->center))
	{
		ft_putstr_fd("Error: Sphere's center is invalid\n", 2);
		free(sp);
		return (false);
	}
	if (!parse_length(&line, &sp->diameter))
	{
		ft_putstr_fd("Error: Sphere's diameter is invalid\n", 2);
		ft_putstr_fd("Diameter must be positive numeric value\n", 1);
		free(sp);
		return (false);
	}
	if (!parse_color(&line, &sp->color))
	{
		ft_putstr_fd("Error: Sphere's color is invalid\n", 2);
		ft_putstr_fd("Color must have R, G, B values in range [0-255]\n", 1);
		free(sp);
		return (false);
	}
	while (ft_isspace(*line))
		line++;
	if (*line == '\0')
	{
		printf("Sphere   | Center: %.1f,%.1f,%.1f | Diameter: %.1f | Color: %d,%d,%d\n", sp->center.x, sp->center.y, sp->center.z, sp->diameter, sp->color.r, sp->color.g, sp->color.b);
		sp->radius = sp->diameter / 2;
		add_to_obj_list(sp, scene, SPHERE);
		return (true);
	}
	free(sp);
	ft_putstr_fd("Error: Sphere has noise information\n", 2);
	return (false);
}

bool	parse_length(char **line, double *length)
{
	char    *tmp;
        int             i;
        bool    res;

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
                *length = ft_atof(tmp);
                if (*length < 0.0)
                        res = false;
                else
                        res = true;
        }
        free(tmp);
        *line += i;
        return (res);
}
