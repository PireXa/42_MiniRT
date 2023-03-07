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

void	light_parser1(char **params, t_data *data, int n, int line_count)
{
	char	**sub_params;

	sub_params = ft_split(params[1], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d : light origin "
				"not valid\033[0m\n", line_count));
	}
	data->scene->lights[n].origin.x = ft_atof(sub_params[0]);
	data->scene->lights[n].origin.y = ft_atof(sub_params[1]);
	data->scene->lights[n].origin.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
}

int	light_parser(char **params, t_data *data, int n, int line_count)
{
	char	**sub_params;

	if (params[0][0] == 'L' && !params[0][1])
	{
		light_parser1(params, data, n, line_count);
		data->scene->lights[n].intensity = ft_atof(params[2]);
		sub_params = ft_split(params[3], ',');
		if (double_array_len(sub_params) != 3)
		{
			free_double_array(sub_params);
			free_all(data, printf("\033[31mError\nLine %d : light "
					"color not valid\033[0m\n", line_count));
		}
		data->scene->lights[n].color = rgb_to_int(ft_atoi(sub_params[0]),
				ft_atoi(sub_params[1]),
				ft_atoi(sub_params[2]));
		free_double_array(sub_params);
		return (1);
	}
	return (0);
}

int	ambience_counter(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

void	ambience_parser(char **p, t_data *data)
{
	char	**sub_params;

	if (p[0][0] == 'A' && !p[0][1])
	{
		if (p[1] == NULL || p[2] == NULL)
			free_all(data, (printf("\033[31mError\n"
						"Ambience not valid\033[0m\n")));
		data->scene->amb_light[0].intensity = ft_atof(p[1]);
		sub_params = ft_split(p[2], ',');
		data->scene->amb_light[0].color = rgb_to_int(ft_atoi(sub_params[0]),
				ft_atoi(sub_params[1]),
				ft_atoi(sub_params[2]));
		free_double_array(sub_params);
	}
	else if ((p[0][0] == 'A' && p[0][1]) || (p[0][0] == 'A' && !p[1][0]))
		free_all(data, (printf("\033[31mError\nAmbience not valid\033[0m\n")));
}
