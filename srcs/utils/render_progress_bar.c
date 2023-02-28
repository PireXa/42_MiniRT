#include "../../inc/minirt.h"

void	render_progress_bar(int x, int x_max)
{
	int i;
	int left_i;
	int progress_len;

	progress_len = 50;
	printf("Progress: %d%% | ", (int) ((float) x / x_max * 100));
	i = (int) ((float) x / WIND_W * (float)progress_len);
	left_i = progress_len - i - 1;
	while (i--)
		printf("#");
	while ( left_i > 0 && left_i--)
		printf("-");
	printf("\r");
}

int check_progress(t_threads *threads_data)
{
	int i;
	int x;
	int x_max;
	int done;

	i = 0;
	x = 0;
	done = 0;
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

void	render_progress_bar2(int x, int x_max)
{
	int i;
	int left_i;
	int progress_len;

	progress_len = 50;
	printf("Progress: %d%% | ", (int) ((float) x / (float)x_max * 100));
	i = (int) ((float) x / (float)x_max * (float)progress_len);
	left_i = progress_len - i;
	while (i--)
		printf("#");
	while (left_i > 0 && left_i--)
		printf("-");
	printf("\n");
}

void	estimated_time(t_threads *threads_data, int progress)
{
	long int	elapsed_time_seconds;
	long int	elapsed_time_minutes;
	long int	estimated_time_minutes;
	long int	estimated_time_seconds;

	elapsed_time_seconds = (long int)(current_time_millis() - threads_data[0].data->start_render_time) / 1000;
	elapsed_time_minutes = elapsed_time_seconds / 60;
	printf("Elapsed time: %ld min %ld sec\n", elapsed_time_seconds / 60, elapsed_time_seconds % 60);
	estimated_time_minutes = (long int)((float)elapsed_time_seconds / (float)progress * 100 - elapsed_time_seconds) / 60;
	if (estimated_time_minutes < 0)
		estimated_time_minutes = 0;
	estimated_time_seconds = (long int)((float)elapsed_time_seconds / (float)progress * 100 - elapsed_time_seconds) % 60;
	if (estimated_time_seconds < 0)
		estimated_time_seconds = 0;
	printf("Estimated time: %ld min %ld sec\n", estimated_time_minutes, estimated_time_seconds);
//	estimated_time_minutes = (long int)((float)elapsed_time / (float)progress * 100 - elapsed_time) / 1000 / 60;
//	if (estimated_time_minutes < 0)
//		estimated_time_minutes = 0;
//	estimated_time_seconds = (long int)((float)elapsed_time / (float)progress * 100 - elapsed_time) / 1000 % 60;
//	if (estimated_time_seconds < 0)
//		estimated_time_seconds = 0;
//	printf("Estimated time: %ld min %ld sec\n", estimated_time_minutes, estimated_time_seconds);
}

void	multi_threaded_progress_bar(t_threads *threads_data)
{
	int	e;
	int	x;
	int done;
	int progress;

	done = 0;
	while (!done)
	{
		while (e < THREADS)
		{
			x = threads_data[e].x - threads_data[e].x_min;
			render_progress_bar2(x , threads_data[e].x_max - threads_data[e].x_min);
			e++;
		}
		if ((progress = check_progress(threads_data)) == -88)
			done = 1;
		estimated_time(threads_data, progress);
		if (!done)
			printf("\033[%dF", THREADS + 2);
		usleep(10000);
		e = 0;
	}
	printf("Finished Rendering\n");
}

//SINGLE PROGRESS BAR FOR ALL THREADS
/*
int	e;
int	x;
int done;

done = 0;
while (!done)
{
x = 0;
while (e < THREADS)
{
x += threads_data[e].x - threads_data[e].x_min;
e++;
}
if (x == (int)WIND_W)
done = 1;
//		if (!done)
//			printf("\033[%dF", THREADS + 1);
render_progress_bar2(x, WIND_W);
usleep(100);
e = 0;
}
printf("\rProgress: 100%% | \n");*/
