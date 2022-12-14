
#include "../../inc/minirt.h"

float	intersect_ray_sphere(t_ray ray, t_sphere sphere)
{
	t_vector oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	oc = vector_from_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0.0001f)
		return (t);
	t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t > 0.0001f)
		return (t);
	return (0);
}

float intersect_ray_plane(t_ray ray, t_plane plane)
{
	float t;
	float denom;
	t_vector p0l0;

	denom = dot_product(plane.normal, ray.direction);
	if (fabs(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(ray.origin, plane.point);
		t = dot_product(p0l0, plane.normal) / denom;
		if (t > 0.0001f)
			return (t);
	}
	return (0);
}

t_near_obj 	get_closest_intersection(t_data *data, t_ray ray)
{
	int			i;
	float		t;
	t_near_obj	hit;

	i = -1;
	hit.t_min = 4535320;
	t = 0;
	hit.closest_sphere = -1;
	hit.closest_plane = -1;
	hit.closest_cylinder = -1;
	while(++i < data->nb_objs->nb_spheres)
	{
		t = intersect_ray_sphere(ray, data->scene->spheres[i]);
		if (t)
		{
			if (t < hit.t_min)
			{
				hit.t_min = t;
				hit.closest_sphere = i;
			}
		}
	}
	i = -1;
	while(++i < data->nb_objs->nb_planes)
	{
		t = intersect_ray_plane(ray, data->scene->planes[i]);
		if (t)
		{
			if (t < hit.t_min)
			{
				hit.t_min = t;
				hit.closest_plane = i;
				hit.closest_sphere = -1;
			}
		}
	}
	i = -1;
	while(++i < data->nb_objs->nb_cylinders)
	{
		t = intersect_ray_cylinder(ray, data->scene->cylinders[i]);
		if (t)
		{
			t = define_cylinder_height(data->scene->cylinders[i], ray, t);
			if (t && t < hit.t_min)
			{
				hit.t_min = t;
				hit.cylinder_face = 0;
				hit.closest_cylinder = i;
				hit.closest_sphere = -1;
				hit.closest_plane = -1;
			}
			else
			{
				t = intersect_ray_cylinder_top(ray, data->scene->cylinders[i]);
				if (t) {
					if (t < hit.t_min) {
						hit.t_min = t;
						hit.cylinder_face = 2;
						hit.closest_cylinder = i;
						hit.closest_sphere = -1;
						hit.closest_plane = -1;
					}
				}
				t = intersect_ray_cylinder_bottom(ray, data->scene->cylinders[i]);
				if (t) {
					if (t < hit.t_min) {
						hit.t_min = t;
						hit.cylinder_face = 1;
						hit.closest_cylinder = i;
						hit.closest_sphere = -1;
						hit.closest_plane = -1;
					}
				}
			}
		}
	}
	return (hit);
}
