
#include "../../inc/minirt.h"

t_vector	transform_vector(t_vector v, float **matrix)
{
	t_vector	result;

	result.x = v.x * matrix[0][0] + v.y * matrix[1][0] + v.z * matrix[2][0];
	result.y = v.x * matrix[0][1] + v.y * matrix[1][1] + v.z * matrix[2][1];
	result.z = v.x * matrix[0][2] + v.y * matrix[1][2] + v.z * matrix[2][2];
	return (result);
}

float	deg_to_rad(float degrees)
{
	return (degrees * M_PI / 180.00f);
}

t_ray	get_ray(t_data *data, int x, int y)
{
	float		aspect_ratio;
	t_vector	camera;
	t_ray		ray;

	aspect_ratio = WIND_W / WIND_H;
	camera.x = -(2 * (x + 0.5) / WIND_W - 1) * aspect_ratio * tan(deg_to_rad(data->scene->cameras[data->camera_index].fov) / 2);
	camera.y = (1 - 2 * (y + 0.5) / WIND_H) * tan(deg_to_rad(data->scene->cameras[data->camera_index].fov) / 2);
	camera.z = 1;
	normalize_vector(&camera);
	ray.origin = data->scene->cameras[0].origin;
	ray.direction = transform_vector(camera, data->scene->cameras[data->camera_index].view_matrix);
	normalize_vector(&ray.direction);
	return (ray);
}

int	get_normal_color(t_hit_obj hit)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((hit.normal.x + 1) / 2)* 255);
	g = (int)(((hit.normal.y + 1) / 2)* 255);
	b = (int)(((hit.normal.z + 1) / 2)* 255);
	return ((r << 16) | (g << 8) | b);
}

void	render_estimated_time(long int start_time, int x, int x_max)
{
	long int	elapsed_time;
	long int	estimated_time_minutes;
	int			percent;

	elapsed_time = current_time_millis() - start_time;
	percent = (int)((float)x / (float)x_max * 100);
	estimated_time_minutes = (long int)((float)elapsed_time / (float)percent * (100 - percent) / 1000 / 60);
	printf("\rEstimated time: %ld minutes", estimated_time_minutes);
}

void	ray_tracer(t_threads *tdata)
{
	t_ray ray;
	int x;
	int y;
	int color;
	t_hit_obj	hit;

	x = tdata->x_min;
	y = 0;
	while (x < tdata->x_max)
	{
//		render_progress_bar(x, tdata->x_max);
		while (y < (int)WIND_H)
		{
			ray = get_ray(tdata->data, x, y);
			hit = get_closest_intersection(tdata->data, ray);
			if (hit.t_min < 4535320)
			{
//				color = get_normal_color(hit);
				hit.color = reflection_refraction(tdata->data, ray, hit, REFLECTION_DEPTH, 1.0f, 1.0f);
				color = shading(hit, ray, tdata->data);
				color = blend_colors(color, hit.color, hit.light_absorb_distance);
			}
			else
			{
//				color = background_color(y, 0x282828, 0xc13800);
				color = background_color(y, BACKGROUND1, BACKGROUND2);
			}
			put_pxl(&tdata->data->img, x, y, color);
			y++;
		}
		y = 0;
		tdata->x++;
		x++;
	}
//	printf("\rProgress: 100%% | \n");
}

void	multi_threading(t_data *data)
{
	pthread_t	threads[THREADS];
	t_threads 	threads_data[THREADS];
	int			i;
	int 		step;

	i = 0;
	step = (int)ceil((double)(WIND_W / THREADS));
	printf("Rendering on %d threads\n", THREADS);
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
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}