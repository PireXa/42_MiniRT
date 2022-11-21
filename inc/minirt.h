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

# define	WIND_W		1920.00f
# define	WIND_H		1080.00f
# define	GREEN		0x00FF00
# define	BLUE		0x0000FF
# define	RED			0xFF0000
# define	BACKGROUND1	0xF525E0
# define 	BACKGROUND2	0x03CFFC
# define	FOV			60

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

//Raytracing by Copilot

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
	float		radius;
	int			color;
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
	int			color;
}				t_plane;

typedef struct s_square
{
	t_vector	center;
	t_vector	normal;
	float		side;
	int			color;
}				t_square;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	float		diameter;
	float		height;
	int			color;
}				t_cylinder;

typedef struct s_triangle
{
	t_vector	point1;
	t_vector	point2;
	t_vector	point3;
	int			color;
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

typedef struct	s_animation {
	long int	time;
}				t_animation;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	t_vector	camera;
	t_sphere	*sphere;
	int 		num_spheres;
	t_light		*light;
	t_fps		fps;
	t_animation	animation;
}				t_data;

//GRAPHICS
void		put_pxl(t_img *img, int x, int y, int color);
void		fps(t_data * data);
int			shading(t_sphere sphere, t_ray ray, float t, t_light light);
int			background_color(int y, int color1, int color2);

//CONTROLS
void		controls(t_data *data);

//PARSING
int			sphere_counter(char *file);
void		parser(char *file, t_sphere *sphere);

//VECTOR UTILS
float		dot_product(t_vector vector1, t_vector vector2);
t_vector	vector_from_points(t_vector point1, t_vector point2);
void		normalize_vector(t_vector *vector);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_scale(t_vector v, float scale);

//UTILS
int			ft_atoi(const char *str);
char 		**ft_split(char const *s, char c);
//char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_itoa(int n);

#endif
