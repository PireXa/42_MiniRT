/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	multi_threading(t_data *data)
{
	int			i;
	int			step;
	pthread_t	threads[THREADS];
	t_threads	threads_data[THREADS];

	i = 0;
	step = (int)ceil((double)(WIND_W / THREADS));
	while (i < THREADS)
	{
		threads_data[i].data = data;
		threads_data[i].thread_id = i;
		if (i == 0)
			threads_data[i].x_min = 0;
		else
			threads_data[i].x_min = threads_data[i - 1].x_max;
		threads_data[i].x = threads_data[i].x_min;
		threads_data[i].x_max = threads_data[i].x_min + step;
		pthread_create(&threads[i], NULL, (void *)ray_tracer, &threads_data[i]);
		i++;
	}
	multi_threaded_progress_bar(threads_data);
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
}
