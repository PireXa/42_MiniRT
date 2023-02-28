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

# define WIND_W 840.00f
# define WIND_H 680.00f
# define BACKGROUND1 0xF525E0
# define BACKGROUND2 0x03CFFC
# define LUMENS 10000
# define REFLECTION_DEPTH 25
# ifndef THREADS
#	define	THREADS		4
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

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

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
}				t_data;

typedef struct s_thread_data {
	t_data		*data;
	int 		thread_id;
	int 		x_min;
	int			x;
	int			x_max;
}				t_threads;

//GRAPHICS
int			background_color(int y, int color1, int color2);
int			calc_color_intensity(int color, float intensity);
int			check_shadow(t_data *data, t_ray ray, t_vector hit_pnt, t_light l);
float		define_cylinder_height(t_cylinder cylinder, t_ray ray, float t);
t_hit_obj	get_closest_intersection(t_data *data, t_ray ray);
float		intersect_ray_cylinder(t_ray ray, t_cylinder cylinder);
float		intersect_ray_cylinder_bottom(t_ray ray, t_cylinder cylinder);
float		intersect_ray_cylinder_top(t_ray ray, t_cylinder cylinder);
float		intersect_ray_plane(t_ray ray, t_plane plane);
float		intersect_ray_sphere(t_ray ray, t_sphere sphere);
float		light_intens_by_dist(t_light l, t_vector hit_pnt);
t_vector	normal_cylinder(t_cylinder cylinder, t_vector hit_point);
t_vector	normal_triangle(t_triangle triangle);
void		put_pxl(t_img *img, int x, int y, int color);
void		ray_tracer(t_threads *tdata);
int			reflection_refraction(t_data *dt, t_ray r, t_hit_obj h, int depth, float intensity, float ref_index);
int			shading(t_hit_obj hit, t_ray ray, t_data *data);

//CONTROLS
void		controls(t_data *data);

//PARSING
int			camera_counter(char *file);
int			cylinder_counter(char *file);
int			light_counter(char *file);
void		parser(char *file, t_scene *scene);
int			plane_counter(char *file);
int			sphere_counter(char *file);
int			triangle_counter(char *file);

//VECTOR UTILS
void		vector_rand(t_vector *vector, float randomness);
float		dot_product(t_vector v1, t_vector v2);
t_vector	cross_product(t_vector vector1, t_vector vector2);
void		normalize_vector(t_vector *v);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_from_points(t_vector point1, t_vector point2);
float		vector_length(t_vector v);
t_vector	vector_scale(t_vector v, float scale);
t_vector	vector_sub(t_vector v1, t_vector v2);
void		vector_rand(t_vector *reflect_dir, float randomness);

//TIME
long int	current_time_millis(void);

//DATA INITIALIZATION
void		init_data(t_data *data, char *scene_file);
float		**set_camera_to_world_transformation_matrix(t_camera camera, t_vector up);

//RENDER INFORMATION
void		multi_threaded_progress_bar(t_threads *treads_data);

//UTILS
int			blend_colors(int color1, int color2, float ratio);
int			ft_atoi(const char *str);
float		ft_atof(char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
int			ft_strncmp(char *s1, char *s2, int n);
char		**tab_space_split(char const *s);
int			free_all(t_data *data);
void		ft_bzero(void *s, size_t n);

// THREADS

void		multi_threading(t_data *data);

// ANIMATION

int			checkcode(char *line, t_data *data);
void		clean_slate(t_data *g);
void		init_graphics(t_data *data);
t_vector	rotater(t_vector v, char e, float sign);
void		transform_sphere(t_data *data, char code[3], int n, float value);
void		transform_plane(t_data *data, char code[3], int n, float valute);
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

// KEYS

int			key_converter1(int key);
int			key_converter2(int key);
enum e_keys{
	key_TAB = -1,
	key_ESC = -2,
	key_ENTER = -3,
	key_D = -4,
	key_F = -5,
	key_LEFT = -6,
	key_RIGHT = -7,
	key_UP = -8,
	key_DOWN = -9,
	key_SPACE = -10,
	key_C = -11,
	key_X = -12,
	key_Y = -13,
	key_Z = -14,
	key_H = -15,
	key_J = -16,
	key_K = -17,
	key_E = -18,
	key_R = -19,
	key_V = -20,
};
#endif
