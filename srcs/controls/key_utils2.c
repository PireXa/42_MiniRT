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

void	key_rotation(t_data *data, int key, char *code, int n)
{
	if (data->edit_mode == 1)
	{
		if (key == key_X)
			transform(data, (char [3]){code[0], '3', '1'}, n, 0.5f);
		else if (key == key_Y)
			transform(data, (char [3]){code[0], '3', '2'}, n, 0.5f);
		else if (key == key_Z)
			transform(data, (char [3]){code[0], '3', '3'}, n, 0.5f);
		else if (key == key_H)
			transform(data, (char [3]){code[0], '3', '4'}, n, 0.5f);
		else if (key == key_J)
			transform(data, (char [3]){code[0], '3', '5'}, n, 0.5f);
		else if (key == key_K)
			transform(data, (char [3]){code[0], '3', '6'}, n, 0.5f);
		clean_slate(data);
		multi_threading(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
}

void	key_height(t_data *data, int key, char *code, int n)
{
	if (data->edit_mode == 1)
	{
		if (key == key_E)
			transform(data, (char [3]){code[0], '4', '1'}, n, 0.5f);
		else if (key == key_R)
			transform(data, (char [3]){code[0], '4', '2'}, n, 0.5f);
		clean_slate(data);
		multi_threading(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
}
