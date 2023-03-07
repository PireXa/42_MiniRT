/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MINIRT                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

typedef struct s_parser_vars
{
	int	fd;
	int	i;
	int	j;
	int	k;
	int	l;
	int	m;
	int	n;
	int	line_count;
}		t_parser_vars;

t_parser_vars	init_parser_vars(char *file)
{
	t_parser_vars	vars;

	vars.fd = open(file, O_RDONLY);
	if (vars.fd < 0)
		printf("\033[31mError\nFile not found\033[0m\n");
	vars.i = 0;
	vars.j = 0;
	vars.k = 0;
	vars.l = 0;
	vars.m = 0;
	vars.n = 0;
	vars.line_count = 1;
	return (vars);
}

void	validate_obj(char *param, t_data *data, int lcount, char *line)
{
	if (line[0] == ' ' || line[0] == '\t')
	{
		free_all(data, printf("\033[31mError\nInvalid "
				"object at line %d\033[0m\n", lcount));
	}
	if (ft_strncmp(param, "C", 2) && ft_strncmp(param, "A", 2)
		&& ft_strncmp(param, "L", 2) && ft_strncmp(param, "sp", 3)
		&& ft_strncmp(param, "pl", 3) && ft_strncmp(param, "cy", 3)
		&& ft_strncmp(param, "tr", 3) && ft_strncmp(param, "\n", 2)
		&& ft_strncmp(param, "#", 1))
	{
		free_all(data, printf("\033[31mError\nInvalid "
				"object at line %d\033[0m\n", lcount));
	}
}

void	parser(char *file, t_data *data)
{
	t_parser_vars	vars;

	vars = init_parser_vars(file);
	data->line = get_next_line(vars.fd);
	data->fd = vars.fd;
	while (data->line)
	{
		data->params = tab_space_split(data->line);
		validate_obj(data->params[0], data, vars.line_count, data->line);
		vars.i += sphere_parser(data->params, data, vars.i, vars.line_count);
		vars.j += plane_parser(data->params, data, vars.j, vars.line_count);
		vars.k += cylinder_parser(data->params, data, vars.k, vars.line_count);
		vars.l += triangle_parser(data->params, data, vars.l, vars.line_count);
		vars.m += camera_parser(data->params, data, vars.m, vars.line_count);
		vars.n += light_parser(data->params, data, vars.n, vars.line_count);
		ambience_parser(data->params, data);
		free_double_array(data->params);
		data->params = NULL;
		free(data->line);
		vars.line_count++;
		data->line = get_next_line(vars.fd);
	}
	if (data->scene->amb_light[0].intensity == -1)
		free_all(data, printf("\033[31mError\nNo ambience light\033[0m\n"));
	free(data->line);
}
