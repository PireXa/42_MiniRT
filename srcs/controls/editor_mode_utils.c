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

char	*print_message(char *cmd)
{
	printf("EDITOR MODE\n");
	printf("Press enter on the window to exit editor mode or\n");
	printf("Enter the object code and the object number:\n");
	cmd = get_next_line(0);
	return (cmd);
}

void	free_editor(char **obj_code, char *cmd, t_data *data)
{
	free(obj_code[0]);
	free(obj_code[1]);
	free(obj_code);
	free(cmd);
	data->edit_mode = 1;
}
