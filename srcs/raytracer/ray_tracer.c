
#include "../../inc/minirt.h"

t_vector	transform_vector(t_vector v, float **matrix)
{
	t_vector	result;

	result.x = v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2] + matrix[0][3];
	result.y = v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2] + matrix[1][3];
	result.z = v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2] + matrix[2][3];
	return (result);
}

float	deg_to_rad(float degrees)
{
	return (degrees * M_PI / 180);
}

t_ray	get_ray(t_data *data, int x, int y)
{
	float		aspect_ratio;
	t_vector	camera;
	t_ray		ray;

	aspect_ratio = WIND_W / WIND_H;
	camera.x = (2 * (x + 0.5) / WIND_W - 1) * aspect_ratio * tan(deg_to_rad(FOV) / 2);
	camera.y = (1 - 2 * (y + 0.5) / WIND_H) * tan(deg_to_rad(FOV) / 2);
	camera.z = -1;
	ray.origin = data->scene->cameras[0].origin;
	ray.direction = transform_vector(camera, data->scene->cameras[0].view_matrix);
//	ray.direction = camera;
	normalize_vector(&ray.direction);
	return (ray);
}

void	ray_tracer(t_data *data)
{
	t_ray ray;
	int x;
	int y;
	int color;
	int i;
	int left_i;
	t_near_obj	hit;

	x = 0;
	y = 0;
	i = 0;
	while (x < (int)WIND_W)
	{
		printf("Progress: %d%% | ", (int)((float)x / WIND_W * 100));
		i = (int)((float)x / WIND_W * 50);
		left_i = 50 - i - 1;
		while (i--)
			printf("#");
		while (left_i--)
			printf("-");
		printf("\r");
		while (y < (int)WIND_H)
		{
			ray = get_ray(data, x, y);
			hit = get_closest_intersection(data, ray);
			if (hit.closest_sphere != -1)
			{
				if (!check_shadow(data, ray, hit.t_min, data->scene->lights[0]))
					color = shading_sphere(data->scene->spheres[hit.closest_sphere], ray, hit.t_min, data->scene->lights[0]);
				else
					color = calc_color_intensity(data->scene->spheres[hit.closest_sphere].color, 0.1f);
			}
			else if (hit.closest_plane != -1)
			{
				if (!check_shadow(data, ray, hit.t_min, data->scene->lights[0]))
					color = shading_plane(data->scene->planes[hit.closest_plane], ray, hit.t_min, data->scene->lights[0]);
				else
					color = calc_color_intensity(data->scene->planes[hit.closest_plane].color, 0.1f);
			}
			else if (hit.closest_cylinder != -1)
			{
				if (hit.cylinder_face == 0)
				{
					if (!check_shadow(data, ray, hit.t_min, data->scene->lights[0]))
						color = shading_cylinder(data->scene->cylinders[hit.closest_cylinder], ray, hit.t_min, data->scene->lights[0]);
					else
						color = calc_color_intensity(data->scene->cylinders[hit.closest_cylinder].color, 0.1f);
				}
				else if (hit.cylinder_face == 2)
				{
					if (!check_shadow(data, ray, hit.t_min, data->scene->lights[0]))
						color = shading_cylinder_top(data->scene->cylinders[hit.closest_cylinder], ray, hit.t_min, data->scene->lights[0]);
					else
						color = calc_color_intensity(data->scene->cylinders[hit.closest_cylinder].color, 0.1f);
				}
				else if (hit.cylinder_face == 1)
				{
					if (!check_shadow(data, ray, hit.t_min, data->scene->lights[0]))
						color = shading_cylinder_bottom(data->scene->cylinders[hit.closest_cylinder], ray, hit.t_min, data->scene->lights[0]);
					else
						color = calc_color_intensity(data->scene->cylinders[hit.closest_cylinder].color, 0.1f);
				}
			}
			else if (hit.closest_triangle != -1)
			{
				color = shading_triangle(data->scene->triangles[hit.closest_triangle], ray, hit.t_min, data->scene->lights[0]);
			}
			else
				color = background_color(y, BACKGROUND1, BACKGROUND2);
			put_pxl(&data->img, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
	printf("\rRendering: 100%%\n");
}
