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

#include "../../inc/minirt.h"

int	key_converter1(int key)
{
	if (key == 65289)
		return (key_TAB);
	else if (key == 65307)
		return (key_ESC);
	else if (key == 65293)
		return (key_ENTER);
	else if (key == 100)
		return (key_D);
	else if (key == 102)
		return (key_F);
	else if (key == 65361)
		return (key_LEFT);
	else if (key == 65363)
		return (key_RIGHT);
	else if (key == 65362)
		return (key_UP);
	else if (key == 65364)
		return (key_DOWN);
	else if (key == 32)
		return (key_SPACE);
	else if (key == 99)
		return (key_C);
	else
		return (key);
}

int	key_converter2(int key)
{
	if (key == 120)
		return (key_X);
	else if (key == 121)
		return (key_Y);
	else if (key == 122)
		return (key_Z);
	else if (key == 104)
		return (key_H);
	else if (key == 106)
		return (key_J);
	else if (key == 107)
		return (key_K);
	else if (key == 101)
		return (key_E);
	else if (key == 114)
		return (key_R);
	else if (key == 118)
		return (key_V);
	else
		return (key);
}

void	key_out(int key, t_data *data)
{
	if (key == key_ESC && data->edit_mode == 0)
	{
		free_all(data);
	}
	else if (key == key_ENTER && data->edit_mode == 1)
	{
		data->edit_mode = 0;
	}
	else if (key == key_V && data->edit_mode == 0)
	{
		clean_slate(data);
		if (data->camera_index < data->nb_objs->nb_cameras - 1)
			data->camera_index += 1;
		else
			data->camera_index = 0;
		multi_threading(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
}

void	key_translations(t_data *data, int key, char *code, int n)
{
	if (data->edit_mode == 1)
	{
		if (key == key_LEFT)
			transform(data, (char [3]){code[0], '2', '1'}, n, 0.5f);
		else if (key == key_RIGHT)
			transform(data, (char [3]){code[0], '2', '2'}, n, 0.5f);
		else if (key == key_UP)
			transform(data, (char [3]){code[0], '2', '3'}, n, 0.5f);
		else if (key == key_DOWN)
			transform(data, (char [3]){code[0], '2', '4'}, n, 0.5f);
		else if (key == key_SPACE)
			transform(data, (char [3]){code[0], '2', '5'}, n, 0.5f);
		else if (key == key_C)
			transform(data, (char [3]){code[0], '2', '6'}, n, 0.5f);
		clean_slate(data);
		multi_threading(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
}

void	key_resize(t_data *data, int key, char *code, int n)
{
	if (data->edit_mode == 1)
	{
		if (key == key_D)
			transform(data, (char [3]){code[0], '1', '1'}, n, 0.5f);
		else if (key == key_F)
			transform(data, (char [3]){code[0], '1', '2'}, n, 0.5f);
		clean_slate(data);
		multi_threading(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
}
