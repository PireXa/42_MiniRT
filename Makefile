SRCS		=	main/main.c main/initializers.c \
				utils/put_pxl.c utils/vector.c utils/ft_split.c utils/ft_atoi.c utils/ft_itoa.c\
				utils/fps.c utils/ft_atof.c utils/render_progress_bar.c utils/tab_space_split.c \
				utils/ft_strncmp.c \
				controls/controls.c \
				parsing/parsing.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c \
				raytracer/ray_tracer.c raytracer/shading.c raytracer/background.c \
				raytracer/intersections.c raytracer/cylinder.c raytracer/reflection_refraction.c \

OBJS		=	$(addprefix objs/,$(SRCS:.c=.o))

CFLAGS		= 	-g #-ffast-math

RM		=	rm -f

NAME		=	minirt

all:		$(NAME)

objs/%.o: srcs/%.c
			@mkdir -p objs
			@mkdir -p objs/main
			@mkdir -p objs/utils
			@mkdir -p objs/controls
			@mkdir -p objs/parsing
			@mkdir -p objs/gnl
			@mkdir -p objs/raytracer
			$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): 	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:		fclean all
