
#include "../../inc/minirt.h"

void	ray_tracer(t_data *data)
{
	t_ray ray;
	t_vector	screen;
	int x;
	int y;
	int color;
	t_near_obj	hit;

	x = 0;
	y = 0;
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
			hit = get_closest_intersection(data, ray);
			if (hit.closest_sphere != -1)
			{
				color = shading_sphere(data->scene->spheres[hit.closest_sphere], ray, hit.t_min, data->light[0]);
			}
			else if (hit.closest_plane != -1)
			{
				if (!check_shadow(data, ray, hit.t_min, data->light[0]))
					color = calc_color_intensity(data->scene->planes[hit.closest_plane].color, light_intens_by_dist(data->light[0], ray, hit.t_min));
				else
					color = calc_color_intensity(data->scene->planes[hit.closest_plane].color, 0.1f);
			}
			else if (hit.closest_cylinder != -1)
			{
				if (hit.cylinder_face == 0)
					color = shading_cylinder(data->scene->cylinders[hit.closest_cylinder], ray, hit.t_min, data->light[0]);
				else if (hit.cylinder_face == 2)
					//color = 0xFFFFFF;
					color = shading_cylinder_top(data->scene->cylinders[hit.closest_cylinder], ray, hit.t_min, data->light[0]);
				else if (hit.cylinder_face == 1)
					//color = 0x0000FF;
					color = shading_cylinder_bottom(data->scene->cylinders[hit.closest_cylinder], ray, hit.t_min, data->light[0]);
			}
			else if (hit.closest_triangle != -1)
			{
				color = shading_triangle(data->scene->triangles[hit.closest_triangle], ray, hit.t_min, data->light[0]);
			}
			else
				color = background_color(y, BACKGROUND1, BACKGROUND2);
			put_pxl(&data->img, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
}
