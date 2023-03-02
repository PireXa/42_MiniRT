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

int	check_progress(t_threads *threads_data)
{
	int	i;
	int	x;
	int	x_max;
	int	done;

	i = 0;
	x = 0;
	x_max = 0;
	while (i < THREADS)
	{
		x_max += threads_data[i].x_max - threads_data[i].x_min;
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		x += threads_data[i].x - threads_data[i].x_min;
		i++;
	}
	if (x == x_max)
		done = -88;
	else
		done = x * 100 / x_max;
	return (done);
}

void	progress_bar(int x, int x_max, int color)
{
	int	i;
	int	left_i;
	int	progress_len;
	int	progress_percent;
	int	tmp;

	progress_len = 50;
	progress_percent = (int)((float) x / (float)x_max * 100);
	printf("\033[%dmProgress:   ", color);
	tmp = progress_percent;
	while (tmp > 9)
	{
		printf("\b");
		tmp /= 10;
	}
	printf("%d%% | ", progress_percent);
	i = (int)((float) x / (float)x_max * (float)progress_len);
	left_i = progress_len - i;
	while (i--)
		printf("#");
	while (left_i > 0 && left_i--)
		printf("-");
	printf("\n\033[0m");
}

void	estimated_time(t_threads *threads_data, int progress)
{
	long int	elapsed_time_seconds;
	long int	elapsed_time_minutes;
	long int	estimated_time_minutes;
	long int	estimated_time_seconds;

	elapsed_time_seconds = (long int)(current_time_millis()
			- threads_data[0].data->start_render_time) / 1000;
	elapsed_time_minutes = elapsed_time_seconds / 60;
	printf("Elapsed time: %ld min %ld sec\n", elapsed_time_minutes,
		elapsed_time_seconds % 60);
	estimated_time_minutes = (long int)((float)elapsed_time_seconds
			/ (float)progress * 100 - elapsed_time_seconds) / 60;
	if (estimated_time_minutes < 0)
		estimated_time_minutes = 0;
	estimated_time_seconds = (long int)((float)elapsed_time_seconds
			/ (float)progress * 100 - elapsed_time_seconds) % 60;
	if (estimated_time_seconds < 0)
		estimated_time_seconds = 0;
	printf("Estimated time: %ld min %ld sec\n", estimated_time_minutes,
		estimated_time_seconds);
}

typedef struct s_progress_bar
{
	int	e;
	int	x;
	int	done;
	int	progress;
}		t_progress_bar;

t_progress_bar	init_progress_bar(void)
{
	t_progress_bar	pb;

	pb.e = 0;
	pb.x = 0;
	pb.done = 0;
	pb.progress = 0;
	return (pb);
}

void	multi_threaded_progress_bar(t_threads *tdata)
{
	t_progress_bar	pb;

	pb = init_progress_bar();
	while (!pb.done)
	{
		while (pb.e < THREADS)
		{
			pb.x = tdata[pb.e].x - tdata[pb.e].x_min;
			if (pb.e % 2 == 0)
				progress_bar(pb.x, tdata[pb.e].x_max - tdata[pb.e].x_min, 34);
			else
				progress_bar(pb.x, tdata[pb.e].x_max - tdata[pb.e].x_min, 32);
			pb.e++;
		}
		pb.progress = check_progress(tdata);
		if (pb.progress == -88)
			pb.done = 1;
		estimated_time(tdata, pb.progress);
		if (!pb.done)
			printf("\033[%dF", THREADS + 2);
		usleep(1000);
		pb.e = 0;
	}
	printf("Finished Rendering\n");
}
