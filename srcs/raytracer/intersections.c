
#include "../../inc/minirt.h"

float	intersect_ray_sphere(t_ray ray, t_sphere sphere)
{
	t_vector oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;
	float radius;

	radius = sphere.diameter / 2;
	oc = vector_from_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - radius * radius;
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

float	intersect_ray_triangle(t_ray ray, t_triangle triangle) //Möller Trumbore Algorithm
{
	float t;
	float denom;
	t_vector p0l0;
	t_vector edge1;
	t_vector edge2;
	t_vector pvec;
	t_vector qvec;
	t_vector tvec;
	float u;
	float v;

	edge1 = vector_from_points(triangle.p1, triangle.p2);
	edge2 = vector_from_points(triangle.p1, triangle.p3);
	pvec = cross_product(ray.direction, edge2);
	denom = dot_product(edge1, pvec);
	if (fabs(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(triangle.p1, ray.origin);
		tvec = cross_product(p0l0, edge1);
		u = dot_product(pvec, p0l0) / denom;
		v = dot_product(tvec, ray.direction) / denom;
		t = dot_product(tvec, edge2) / denom;
		if (t > 0.0001f && u >= 0 && v >= 0 && u + v <= 1)
			return (t);
	}
	return (0);
}

t_hit_obj 	get_closest_intersection(t_data *data, t_ray ray)
{
	int			i;
	float		t;
	t_hit_obj	hit;

	i = -1;
	hit.t_min = 4535320;
	t = 0;
	hit.closest_sphere = -1;
	hit.closest_plane = -1;
	hit.closest_cylinder = -1;
	hit.closest_triangle = -1;
	hit.color = 0;
	hit.normal = (t_vector){0, 0, 0};
	hit.hit_point = (t_vector){0, 0, 0};
	//CHECK SPHERES
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
	//CHECK PLANES
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
	//CHECK CYLINDERS
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
				if (t)
				{
					if (t < hit.t_min)
					{
						hit.t_min = t;
						hit.cylinder_face = 2;
						hit.closest_cylinder = i;
						hit.closest_sphere = -1;
						hit.closest_plane = -1;
					}
				}
				t = intersect_ray_cylinder_bottom(ray, data->scene->cylinders[i]);
				if (t)
				{
					if (t < hit.t_min)
					{
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
	i = -1;
	//CHECK TRIANGLES
	while(++i < data->nb_objs->nb_triangles)
	{
		t = intersect_ray_triangle(ray, data->scene->triangles[i]);
		if (t)
		{
			if (t < hit.t_min)
			{
				hit.t_min = t;
				hit.closest_triangle = i;
				hit.closest_sphere = -1;
				hit.closest_plane = -1;
				hit.closest_cylinder = -1;
			}
		}
	}
	if (hit.t_min < 4535320)
	{
		hit.hit_point = vector_add(ray.origin, vector_scale(ray.direction, hit.t_min));
		if (hit.closest_sphere != -1)
		{
			hit.normal = vector_from_points(data->scene->spheres[hit.closest_sphere].center, hit.hit_point);
			normalize_vector(&hit.normal);
			hit.color = data->scene->spheres[hit.closest_sphere].color;
		}
		else if (hit.closest_plane != -1)
		{
			hit.normal = data->scene->planes[hit.closest_plane].normal;
			hit.color = data->scene->planes[hit.closest_plane].color;
		}
		else if (hit.closest_cylinder != -1)
		{
			if (hit.cylinder_face == 0)
				hit.normal = normal_cylinder(data->scene->cylinders[hit.closest_cylinder], hit.hit_point);
			else if (hit.cylinder_face == 2)
				hit.normal = data->scene->cylinders[hit.closest_cylinder].normal;
			else if (hit.cylinder_face == 1)
				hit.normal = vector_scale(data->scene->cylinders[hit.closest_cylinder].normal, -1);
			hit.color = data->scene->cylinders[hit.closest_cylinder].color;
		}
		else if (hit.closest_triangle != -1)
		{
			hit.normal = normal_triangle(data->scene->triangles[hit.closest_triangle]);
			hit.color = data->scene->triangles[hit.closest_triangle].color;
		}
	}
	return (hit);
}
