
#include "../../inc/minirt.h"

void	ray_tracer(t_data *data)
{
	t_ray ray;
	t_vector	screen;
	int x;
	int y;
	int color;
	int i;
	float t;
	float t_min;
	int 	closest_sphere;
	int 	closest_plane;
	int 	closest_cylinder;

	x = 0;
	y = 0;
	i = -1;
	t_min = 4535320;
	closest_sphere = -1;
	closest_plane = -1;
	closest_cylinder = -1;
	while (x < (int)WIND_W)
	{
		while (y < (int)WIND_H)
		{
			screen.x = (float)x;
			screen.y = (float)y;
			screen.z = 0;
			ray.origin = data->camera;
			ray.direction = vector_from_points(data->camera, screen);
			normalize_vector(&ray.direction);
			while(++i < data->nb_objs->nb_spheres)
			{
				t = intersect_ray_sphere(ray, data->scene->spheres[i]);
				if (t)
				{
					if (t < t_min)
					{
						t_min = t;
						closest_sphere = i;
					}
				}
			}
			i = -1;
			while(++i < data->nb_objs->nb_planes)
			{
				t = intersect_ray_plane(ray, data->scene->planes[i]);
				if (t)
				{
					if (t < t_min)
					{
						t_min = t;
						closest_plane = i;
						closest_sphere = -1;
					}
				}
			}
			i = -1;
			while(++i < data->nb_objs->nb_cylinders)
			{
				t = intersect_ray_cylinder(ray, data->scene->cylinders[i]);
				if (t)
				{
					if (t < t_min)
					{
						t_min = t;
						closest_cylinder = i;
						closest_sphere = -1;
						closest_plane = -1;
					}
				}
			}
			if (closest_sphere != -1)
			{
				color = shading_sphere(data->scene->spheres[closest_sphere], ray, t_min, data->light[0]);
				closest_sphere = -1;
				t_min = 4535320;
			}
			else if (closest_plane != -1)
			{
				if (!check_shadow(data, ray, t_min, data->light[0]))
					color = calc_color_intensity(data->scene->planes[closest_plane].color, light_intens_by_dist(data->light[0], ray, t_min));
				else
					color = calc_color_intensity(data->scene->planes[closest_plane].color, 0.01f);
				closest_plane = -1;
				t_min = 4535320;
			}
			else if (closest_cylinder != -1)
			{
				//color = shading_cylinder(data->scene->cylinders[closest_cylinder], ray, t_min, data->light[0]);
				color = data->scene->cylinders[closest_cylinder].color;
				closest_cylinder = -1;
				t_min = 4535320;
			}
			else
				color = background_color(y, BACKGROUND1, BACKGROUND2);
			i = -1;
			put_pxl(&data->img, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
}
