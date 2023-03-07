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

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <ctype.h>
# include <time.h>
# include <sys/time.h>
# include <stdint.h>
# include <pthread.h>
# include "mlx.h"
# include "get_next_line.h"

/*# define WIND_W 100.00f
# define WIND_H 50.00f*/
# define WIND_W 840.00f
# define WIND_H 680.00f
/*# define WIND_W 1920.00f
# define WIND_H 1080.00f*/
# define BACKGROUND1 0xF525E0
# define BACKGROUND2 0x03CFFC
# define LUMENS 10000
# define REFLECTION_DEPTH 25
# ifndef THREADS
#  define THREADS 4
# endif

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bi_per_pxl;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_fps {
	int			fps;
	int			frame_ctr;
	long int	frame_time;
}				t_fps;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct s_2nd_equation
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t;
}				t_2nd_equation;

typedef struct s_ref_cap
{
	int		depth;
	float	light_int;
}			t_ref_cap;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_cyl_height
{
	int			i;
	float		t;
}				t_cy_h;

typedef struct s_sphere
{
	t_vector	center;
	float		diameter;
	int			color;
	float		light_absorb_ratio;
	float		refraction_index;
	float		light_absorb_distance;
	float		ks;
	float		kd;
	float		roughness;
	int			texture;
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
	int			color;
	float		light_absorb_ratio;
	float		refraction_index;
	float		light_absorb_distance;
	float		ks;
	float		kd;
	float		roughness;
	int			texture;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	base_center;
	t_vector	normal;
	float		diameter;
	float		height;
	int			color;
	float		light_absorb_ratio;
	float		refraction_index;
	float		light_absorb_distance;
	float		ks;
	float		kd;
	float		roughness;
}				t_cylinder;

typedef struct s_triangle
{
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;
	int			color;
	float		light_absorb_ratio;
	float		refraction_index;
	float		light_absorb_distance;
	float		ks;
	float		kd;
	float		roughness;
}				t_triangle;

typedef struct s_light
{
	t_vector	origin;
	float		intensity;
	int			color;
}				t_light;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	normal;
	float		**view_matrix;
	float		fov;
}				t_camera;

typedef struct s_ambience
{
	float	intensity;
	int		color;
}				t_ambience;

typedef struct s_scene
{
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	t_triangle	*triangles;
	t_light		*lights;
	t_camera	*cameras;
	t_ambience	*amb_light;
}				t_scene;

typedef struct s_nb_objs {
	int			nb_spheres;
	int			nb_planes;
	int			nb_cylinders;
	int			nb_triangles;
	int			nb_lights;
	int			nb_cameras;
}				t_nb_objs;

typedef struct s_near_obj {
	float		t_min;
	int			closest_sphere;
	int			closest_plane;
	int			closest_cylinder;
	int			cylinder_face;
	int			closest_triangle;
	t_vector	normal;
	t_vector	hit_point;
	int			color;
	float		light_absorb_ratio;
	float		refraction_index;
	float		light_absorb_distance;
	float		ks;
	float		kd;
	float		roughness;
}				t_hit_obj;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_scene		*scene;
	t_nb_objs	*nb_objs;
	t_fps		fps;
	long int	start_render_time;
	int			camera_index;
	int			edit_mode;
	int			normal_mode;
	char		*line;
	char		**params;
	int			fd;
}				t_data;

typedef struct s_thread_data {
	t_data	*data;
	int		thread_id;
	int		x_min;
	int		x;
	int		x_max;
}			t_threads;

//GRAPHICS
int			background_color(int y, int color1, int color2);
int			calc_color_intensity(int color, float intensity);
t_vector	calc_reflected_ray(t_vector ray, t_vector normal);
t_vector	calc_refracted_ray(float n1, float n2, t_vector ray, t_vector n);
int			checkerboard_plane(t_vector hit_point, t_plane plane);
int			checkerboard_sphere(t_vector hit_point, t_sphere sphere);
void		check_hit_spheres(t_data *data, t_ray ray, t_hit_obj *hit);
void		check_hit_planes(t_data *data, t_ray ray, t_hit_obj *hit);
void		check_hit_cylinders(t_data *data, t_ray ray, t_hit_obj *hit);
void		check_cylinder_b(t_cylinder cyl, t_ray ray,
				t_hit_obj *hit, t_cy_h c_h);
void		check_cylinder_t(t_cylinder cyl, t_ray ray,
				t_hit_obj *hit, t_cy_h c_h);
void		check_cylinder_h(t_cylinder cyl, t_ray ray,
				t_hit_obj *hit, t_cy_h c_h);
void		check_hit_triangles(t_data *data, t_ray ray, t_hit_obj *hit);
int			check_shadow(t_data *data, t_ray ray, t_vector hit_pnt, t_light l);
float		define_cylinder_height(t_cylinder cylinder, t_ray ray, float t);
float		fresnel(float n2, t_vector i_dir, t_vector nor, float l_rflct);
t_hit_obj	get_closest_intersection(t_data *data, t_ray ray);
t_hit_obj	get_reflect_color(t_data *d, t_ray rflct_ray,
				t_hit_obj h, float *f);
t_hit_obj	get_refract_color(t_data *d, t_ray rfrct_ray,
				t_hit_obj h, float *b);
float		intersect_ray_cylinder(t_ray ray, t_cylinder cylinder);
float		intersect_ray_cylinder_bottom(t_ray ray, t_cylinder cylinder);
float		intersect_ray_cylinder_top(t_ray ray, t_cylinder cylinder);
float		intersect_ray_plane(t_ray ray, t_plane plane);
float		intersect_ray_sphere(t_ray ray, t_sphere sphere);
float		intersect_ray_triangle(t_ray ray, t_triangle triangle);
float		light_intens_by_dist(t_light l, t_vector hit_pnt);
t_vector	normal_cylinder(t_cylinder cylinder, t_vector hit_point);
t_vector	normal_triangle(t_triangle triangle);
t_hit_obj	no_hit_default_values(void);
void		put_pxl(t_img *img, int x, int y, int color);
void		ray_tracer(t_threads *tdata);
int			reflection_refraction(t_data *dt, t_ray r,
				t_hit_obj h, t_ref_cap cap);
int			shading(t_hit_obj hit, t_ray ray, t_data *data);

//CONTROLS
void		controls(t_data *data);

//PARSING
void		ambience_parser(char **p, t_data *data);
int			ambience_counter(char *file);
int			camera_counter(char *file);
int			camera_parser(char **params, t_data *d, int m, int lcnt);
int			cylinder_counter(char *file);
int			cylinder_parser(char **params, t_data *data, int i, int line_count);
float		get_material_data(char *mat_ref, int data);
int			light_counter(char *file);
int			light_parser(char **params, t_data *data, int n, int line_count);
void		parser(char *file, t_data *data);
int			plane_counter(char *file);
int			plane_parser(char **params, t_data *data, int i, int lcnt);
int			sphere_counter(char *file);
int			sphere_parser(char **params, t_data *data, int i, int line_count);
int			triangle_counter(char *file);
int			triangle_parser(char **params, t_data *d, int l, int line_count);

//VECTOR UTILS
t_vector	cross_product(t_vector vector1, t_vector vector2);
float		dot_product(t_vector v1, t_vector v2);
void		normalize_vector(t_vector *v);
t_vector	transform_vector(t_vector v, float **matrix);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_from_points(t_vector point1, t_vector point2);
float		vector_length(t_vector v);
void		vector_rand(t_vector *vector, float randomness);
t_vector	vector_scale(t_vector v, float scale);
t_vector	vector_sub(t_vector v1, t_vector v2);
void		vector_rand(t_vector *reflect_dir, float randomness);

//TIME
long int	current_time_millis(void);

//DATA INITIALIZATION
void		init_data(t_data *data, char *scene_file);
float		**set_cam_wrld_mtrx(t_camera camera, t_vector up);

//RENDER INFORMATION
void		multi_threaded_progress_bar(t_threads *treads_data);

//UTILS
int			blend_colors(int c1, int c2, float rt);
int			double_array_len(char **array);
int			ft_atoi(const char *str);
float		ft_atof(char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
int			ft_strncmp(char *s1, char *s2, int n);
char		**tab_space_split(char const *s);
int			free_all(t_data *data, int exit_code);
void		free_double_array(char **array);
void		ft_bzero(void *s, size_t n);
int			rgb_to_int(int r, int g, int b);
void		reach_eof(int fd, t_data *data);

// THREADS

void		multi_threading(t_data *data);

// ANIMATION

char		checkcode(char *line);
void		clean_slate(t_data *g);
void		put_new_img(t_data *data);
t_vector	rotater(t_vector v, char e, float sign);
void		transform_sphere(t_data *data, char code[3], int n, float value);
void		transform_plane(t_data *data, char code[3], int n, float value);
void		transform_lights(t_data *data, char code[3], int n, float value);
void		transform_cylinders1(t_data *data, char code[3], int n, float val);
void		transform_cylinders2(t_data *data, char code[3], int n);
void		transform_cylinders(t_data *data, char code[3], int n, float val);
void		transform_cameras1(t_data *data, char code[3], int n, float value);
char		*print_message(char *cmd);
void		free_editor(char **obj_code, char *cmd, t_data *data);
void		transform(t_data *data, char code[3], int n, float value);
void		key_out(int key, t_data *data);
void		key_translations(t_data *data, int key, char *code, int n);
void		key_resize(t_data *data, int key, char *code, int n);
void		key_rotation(t_data *data, int key, char *code, int n);
void		key_height(t_data *data, int key, char *code, int n);
void		re_render(t_data *data);

// KEYS

enum e_keys{
	key_ESC = 65307,
	key_TAB = 65289,
	key_ENTER = 65293,
	key_D = 100,
	key_F = 102,
	key_LEFT = 65361,
	key_RIGHT = 65363,
	key_UP = 65362,
	key_DOWN = 65364,
	key_SPACE = 32,
	key_C = 99,
	key_X = 120,
	key_Y = 121,
	key_Z = 122,
	key_H = 104,
	key_J = 106,
	key_K = 107,
	key_E = 101,
	key_R = 114,
	key_V = 118,
	key_N = 110,
};

#endif
