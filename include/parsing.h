/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:30:51 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:35:37 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"
# include "vectors.h"

typedef struct s_scene	t_scene;

/* file_operations.c */
int						open_map(t_scene *scene, char *path);
void					parse_file(t_scene *scene, char **argv);

/* list_operations.c */
int						fill_lst(t_scene *scene);
int						parse_lst(t_scene *scene);

/* parsing_helpers.c */
int						get_val(int *color, char **line);
int						get_color(int *r, int *g, int *b, char *line);
int						parse_vector(t_vec3 *vec, char **line);
int						parse_double(double *value, char **line);

/* parsing_ambient.c */
int						parse_ambient(t_scene *scene, char *line);
int						parse_camera(t_scene *scene, char *line);
int						check_char(t_scene *scene, char *line);

/* parsing_objects.c */
int						parse_light(t_scene *scene, char *line);
int						parse_sphere(t_scene *scene, char *line);
int						parse_plane(t_scene *scene, char *line);
int						parse_cylinder(t_scene *scene, char *line);

/* get_type.c */
void					get_string(char *line, char **str);
t_material_type			get_type(char *line);

#endif