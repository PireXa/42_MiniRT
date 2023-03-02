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

void	key_out(int key, t_data *data)
{
	if (key == key_ESC && data->edit_mode == 0)
		free_all(data, 0);
	else if (key == key_ENTER && data->edit_mode == 1)
		data->edit_mode = 0;
	else if (key == key_V && data->edit_mode == 0)
	{
		clean_slate(data);
		if (data->camera_index < data->nb_objs->nb_cameras - 1)
			data->camera_index += 1;
		else
			data->camera_index = 0;
		multi_threading(data);
		put_new_img(data);
	}
	else if (key == key_N && data->edit_mode == 0)
	{
		clean_slate(data);
		if (data->normal_mode == 1)
			data->normal_mode = 0;
		else
			data->normal_mode = 1;
		multi_threading(data);
		put_new_img(data);
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
		put_new_img(data);
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
		put_new_img(data);
	}
}
