#include "minirt.h"

bool	parse_and_add_light(char *line, t_scene *scene)
{
	t_light	*l;

	if (scene->l != NULL)
	{
		ft_putstr_fd("Error: Light can only be declared once.\n", 2);
		return (false);
	}
	l = malloc(sizeof(t_light));
	if (l == NULL)
		return (false);
	if (!parse_point(&line, &l->org))
	{
		ft_putstr_fd("Error: Light point is invalid\n", 2);
		free(l);
		return (false);
	}
	if (!parse_ratio(&line, &l->ratio))
        {
                ft_putstr_fd("Error: Light's ratio is invalid\n", 2);
                ft_putstr_fd("Light must have a ratio in range [0.0,1.0]\n", 1);
                free(l);
                return (false);
        }
        if (!parse_color(&line, &l->color))
        {
                ft_putstr_fd("Error: Ambient lightning's color is invalid\n", 2);
                ft_putstr_fd("Light must have R, G, B colors in range [0-255]\n", 1);
                free(l);
                return (false);
        }
	while (ft_isspace(*line))
		line++;
	if (*line == '\0')
	{
		printf("Light    | Point: %.1f,%.1f,%.1f | Ratio: %.1f | Color: %d,%d,%d\n", l->org.x, l->org.y, l->org.z, l->ratio, l->color.r, l->color.g, l->color.b);
		scene->l = l;
		return (true);
	}
	free(l);
	ft_putstr_fd("Error: Light has noise information\n", 2);
	return (false);

}
