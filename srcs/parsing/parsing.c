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
		printf("\033[31mError\nFile not found\n");
	vars.i = 0;
	vars.j = 0;
	vars.k = 0;
	vars.l = 0;
	vars.m = 0;
	vars.n = 0;
	vars.line_count = 1;
	return (vars);
}

void	parser(char *file, t_data *data)
{
	char			*line;
	char			**params;
	t_parser_vars	vars;

	vars = init_parser_vars(file);
	line = get_next_line(vars.fd);
	while (line)
	{
		params = tab_space_split(line);
		vars.i += sphere_parser(params, data, vars.i, vars.line_count);
		vars.j += plane_parser(params, data, vars.j, vars.line_count);
		vars.k += cylinder_parser(params, data, vars.k, vars.line_count);
		vars.l += triangle_parser(params, data, vars.l, vars.line_count);
		vars.m += camera_parser(params, data, vars.m, vars.line_count);
		vars.n += light_parser(params, data, vars.n, vars.line_count);
		ambience_parser(params, data);
		free_double_array(params);
		free(line);
		vars.line_count++;
		line = get_next_line(vars.fd);
	}
	free(line);
	close(vars.fd);
}
