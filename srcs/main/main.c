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

long int	current_time_millis(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	loop(t_data *data)
{
	multi_threading(data);
	data->mlx_win = mlx_new_window(data->mlx, WIND_W, WIND_H, "miniRT");
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	controls(data);
	printf("Render time: %ld ms\n",
		current_time_millis() - data->start_render_time);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (argc != 2)
		return (printf("\033[31mError\nCorrect: ./miniRT scenes/(file.rt)\n"));
	if (open(argv[1], O_RDONLY) == -1)
		return (printf("\033[31mError\nFile not found\n"));
	if (open(argv[1], __O_DIRECTORY) != -1)
		return (printf("\033[31mError\nIncorrect file type\n"));
	if (ft_strncmp(".rt", argv[1] + ft_strlen(argv[1]) - 3, 3))
		return (printf("\033[31mError\nFile extension must be .rt\n"));
	data = (t_data *)malloc(sizeof(t_data));
	init_data(data, argv[1]);
	if (data->nb_objs->nb_cameras == 0)
		return (printf("\033[31mError\nNo cameras found in scene\n"));
	printf("Parsing scene...\n");
	parser(argv[1], data);
	printf("Rendering...\n");
	loop(data);
}
