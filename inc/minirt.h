#ifndef MINIRT_H
#define MINIRT_H

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
# include "mlx.h"
# include "get_next_line.h"

# define	WIND_W		840.00f/*1920.00f*/
# define	WIND_H		680.00f/*1080.00f*/
# define	GREEN		0x00FF00
# define	BLUE		0x0000FF
# define	RED			0xFF0000
# define	BACKGROUND1	0xF525E0
# define 	BACKGROUND2	0x03CFFC
# define	FOV			70
# define	LUMENS		10000
# define	AMBIENT_LIGHT	0.3f
# define	REFLECTION_DEPTH	25
# define 	WORLD_SIZE	2000
# define 	CAM_X		1000 //(WORLD_SIZE / 2)
# define 	CAM_Y		(-50)
# define 	CAM_Z		1000 //(WORLD_SIZE / 2)

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
	float 		light_absorb_ratio;
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
	int			color;
	float 		light_absorb_ratio;
}				t_plane;

typedef struct s_square
{
	t_vector	center;
	t_vector	normal;
	float		side;
	int			color;
	float 		light_absorb_ratio;
}				t_square;

typedef struct s_cylinder
{
	t_vector	base_center;
	t_vector	normal;
	float		diameter;
	float		height;
	int			color;
	float 		light_absorb_ratio;
}				t_cylinder;

typedef struct s_triangle
{
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;
	int			color;
	float 		light_absorb_ratio;
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

typedef struct s_scene
{
	t_sphere	*spheres;
	t_plane		*planes;
	t_square	*squares;
	t_cylinder	*cylinders;
	t_triangle	*triangles;
	t_light		*lights;
	t_camera	*cameras;
}				t_scene;

typedef struct s_nb_objs {
	int			nb_spheres;
	int			nb_planes;
	int			nb_squares;
	int			nb_cylinders;
	int			nb_triangles;
	int			nb_lights;
	int			nb_cameras;
}				t_nb_objs;

typedef struct	s_animation {
	long int	time;
}				t_animation;

typedef struct s_near_obj {
	float		t_min;
	int			closest_sphere;
	int			closest_plane;
	int			closest_cylinder;
	int			cylinder_face;
	int			closest_triangle;
	t_vector	normal;
	t_vector	hit_point;
	int 		color;
	float 		light_absorb_ratio;
}				t_hit_obj;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_vector	camera;
	t_scene		*scene;
	t_nb_objs	*nb_objs;
	t_light		*light;
	t_fps		fps;
	t_animation	animation;
	long int	start_render_time;
}				t_data;

//GRAPHICS
int			background_color(int y, int color1, int color2);
int			calc_color_intensity(int color, float intensity);
int			check_shadow(t_data *data, t_ray ray, t_vector hit_point, t_light light);
float		define_cylinder_height(t_cylinder  cylinder, t_ray ray, float t);
void		fps(t_data * data);
t_hit_obj	get_closest_intersection(t_data *data, t_ray ray);
float 		intersect_ray_cylinder(t_ray ray, t_cylinder cylinder);
float		intersect_ray_cylinder_bottom(t_ray ray, t_cylinder cylinder);
float		intersect_ray_cylinder_top(t_ray ray, t_cylinder cylinder);
float		intersect_ray_plane(t_ray ray, t_plane plane);
float		intersect_ray_sphere(t_ray ray, t_sphere sphere);
float		light_intens_by_dist(t_light light, t_vector hit_point);
t_vector 	normal_cylinder(t_cylinder cylinder, t_vector hit_point);
t_vector	normal_triangle(t_triangle triangle);
void		put_pxl(t_img *img, int x, int y, int color);
void		ray_tracer(t_data *data);
int			reflection_refraction(t_data *data, t_ray ray, t_hit_obj hit, int depth, float intensity);
int			shading(t_hit_obj hit, t_ray ray, t_data *data);
int 		shading_plane(t_plane plane, t_ray ray, t_vector hit_point, t_data *data);
int			shading_sphere(t_sphere sphere, t_ray, t_vector hit_point, t_data *data);
int			shading_cylinder(t_cylinder cylinder, t_ray ray, t_vector hit_point, t_data *data);
int			shading_cylinder_top(t_cylinder cylinder, t_ray ray, t_vector hit_point, t_data *data);
int			shading_cylinder_bottom(t_cylinder cylinder, t_ray ray, t_vector hit_point, t_data *data);
int			shading_triangle(t_triangle triangle, t_ray ray, t_vector hit_point, t_data *data);

//CONTROLS
void		controls(t_data *data);

//PARSING
int			camera_counter(char *file);
int 		cylinder_counter(char *file);
int			light_counter(char *file);
void		parser(char *file, t_scene *scene);
int			plane_counter(char *file);
int			sphere_counter(char *file);
int			triangle_counter(char *file);

//VECTOR UTILS
void		vector_rand(t_vector *reflect_dir, float randomness);
float		dot_product(t_vector vector1, t_vector vector2);
t_vector	cross_product(t_vector vector1, t_vector vector2);
void		normalize_vector(t_vector *vector);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_from_points(t_vector point1, t_vector point2);
float		vector_length(t_vector v);
t_vector	vector_scale(t_vector v, float scale);
t_vector	vector_sub(t_vector v1, t_vector v2);

//TIME
long int	current_time_millis();

//DATA INITIALIZATION
void		init_data(t_data *data, char *scene_file);
float		**set_camera_to_world_transformation_matrix(t_camera camera, t_vector up);

//RENDER INFORMATION
void		render_progress_bar(int x);

//UTILS
int			ft_atoi(const char *str);
float		ft_atof(char *str);
char		*ft_itoa(int n);
char 		**ft_split(char const *s, char c);
char		**tab_space_split(char const *s);

#endif
