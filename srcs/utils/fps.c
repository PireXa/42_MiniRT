#include "../../inc/minirt.h"

void	fps(t_data * data)
{
	char	*fps;
	char	*fps_str;

	if (data->fps.frame_time < time(NULL))
	{
		data->fps.fps = data->fps.frame_ctr;
		data->fps.frame_ctr = 0;
		data->fps.frame_time = time(NULL);
	}
	fps = ft_itoa(data->fps.fps);
	fps_str = ft_strjoin("FPS: ", fps);
	mlx_string_put(data->mlx, data->mlx_win, 10, 100, 0x000000, fps_str);
	free(fps);
	free(fps_str);
	data->fps.frame_ctr++;
}
