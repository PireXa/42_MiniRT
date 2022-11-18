#include "../../inc/minirt.h"

int	key_press(int key, t_data *data)
{
	//printf("key: %d\n", key);
	if (key == 65307)
		exit(0);
	/*else if (key == 119)
		data->xy_angle_off += 0.1;
	else if (key == 115)
		data->xy_angle_off -= 0.1;
	else if (key == 97)
		data->yz_angle_off += 0.1;
	else if (key == 100)
		data->yz_angle_off -= 0.1;*/
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}

void	controls(t_data *data)
{
	mlx_hook(data->mlx_win, 2, 1L<<0, key_press, data);
	//mlx_hook(data->mlx_win, 3, 1L<<1, key_release, data);
	mlx_hook(data->mlx_win, 17, 1L<<17, close_window, data);
}
