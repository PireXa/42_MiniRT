
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
	camera.x = -(2 * (x + 0.5) / WIND_W - 1) * aspect_ratio * tan(deg_to_rad(FOV) / 2);
	camera.y = (1 - 2 * (y + 0.5) / WIND_H) * tan(deg_to_rad(FOV) / 2);
	camera.z = 1;
	normalize_vector(&camera);
	ray.origin = data->scene->cameras[0].origin;
	ray.direction = transform_vector(camera, data->scene->cameras[0].view_matrix);
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

void	ray_tracer(t_data *data)
{
	t_ray ray;
	int x;
	int y;
	int color;
	t_hit_obj	hit;

	x = 0;
	y = 0;
	while (x < (int)WIND_W)
	{
		render_progress_bar(x);
		while (y < (int)WIND_H)
		{
			ray = get_ray(data, x, y);
			hit = get_closest_intersection(data, ray);
			if (hit.t_min < 4535320)
			{
//				color = get_normal_color(hit);
				hit.color = reflection_refraction(data, ray, hit, REFLECTION_DEPTH, 1.0f, 1.0f);
				color = shading(hit, ray, data);
//				color = blend_colors(color, hit.color, hit.light_absorb_ratio);
				color = blend_colors(color, hit.color, hit.light_absorb_distance);
//				color = blend_colors(color, hit.color, 0.5f);
//				color = hit.color;
			}
			else
			{
//				color = background_color(y, 0x282828, 0xc13800);
				color = background_color(y, BACKGROUND1, BACKGROUND2);
			}
			put_pxl(&data->img, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
	printf("\rProgress: 100%% | \n");
}
