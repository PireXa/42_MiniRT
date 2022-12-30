
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

void	ray_tracer(t_data *data)
{
	t_ray ray;
	t_vector hit_point;
	int x;
	int y;
	int color;
	t_near_obj	hit;

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
				hit_point = vector_add(ray.origin, vector_scale(ray.direction, hit.t_min));
			if (hit.closest_sphere != -1)
			{
					color = shading_sphere(data->scene->spheres[hit.closest_sphere], ray, hit_point, data);
			}
			else if (hit.closest_plane != -1)
			{
					color = shading_plane(data->scene->planes[hit.closest_plane], ray, hit_point, data);
			}
			else if (hit.closest_cylinder != -1)
			{
				if (hit.cylinder_face == 0)
				{
						color = shading_cylinder(data->scene->cylinders[hit.closest_cylinder], ray, hit_point, data);
				}
				else if (hit.cylinder_face == 2)
				{
						color = shading_cylinder_top(data->scene->cylinders[hit.closest_cylinder], ray, hit_point, data);
				}
				else if (hit.cylinder_face == 1)
				{
						color = shading_cylinder_bottom(data->scene->cylinders[hit.closest_cylinder], ray, hit_point, data);
				}
			}
			else if (hit.closest_triangle != -1)
			{
				color = shading_triangle(data->scene->triangles[hit.closest_triangle], ray, hit_point, data);
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
