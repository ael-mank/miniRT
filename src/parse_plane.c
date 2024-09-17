#include "minirt.h"

bool	parse_and_add_plane(char *line, t_list **objs)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
        if (pl == NULL)
                return (false);
	while (!ft_isspace(*line))
		line++;
        if (!parse_point(&line, &pl->point))
        {
                ft_putstr_fd("Error: The point in the plane is invalid\n", 2);
                free(pl);
                return (false);
        }
        if (!parse_direction(&line, &pl->normal))
        {
                ft_putstr_fd("Error: The normal vector of the plane is invalid\n", 2);
                ft_putstr_fd("Normal vector must have x, y, z axis in range [-1,1]\n", 1);
                free(pl);
                return (false);
        }
	if (!parse_color(&line, &pl->color))
        {
                ft_putstr_fd("Error: Plane's color is invalid\n", 2);
                ft_putstr_fd("Color must have R, G, B values in range [0-255]\n", 1);
                free(pl);
                return (false);
        }
	while (ft_isspace(*line))
                line++;
        if (*line == '\0')
        {
                printf("Plane | Point: %.1f,%.1f,%.1f | Normal: %.1f,%.1f,%.1f | Color: %d,%d,%d\n", pl->point.x, pl->point.y, pl->point.z, pl->normal.x, pl->normal.y, pl->normal.z, pl->color.r, pl->color.g, pl->color.b);
		add_to_obj_list(pl, objs);
                return (true);
        }
        free(pl);
        ft_putstr_fd("Error: Plane has noise information\n", 2);
        return (false);
}

void	add_to_obj_list(void *obj, t_list **objs)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->content = obj;
	new->next = NULL;
	ft_lstadd_back(objs, new);
}
