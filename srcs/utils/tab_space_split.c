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

int	nb_words(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i] != ' ' && s[i] != '\t')
		{
			count++;
			while (s[i] && s[i] != ' ' && s[i] != '\t')
				i++;
		}
		else
			i++;
	}
	return (count);
}

int	wrdl(char const *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		len++;
		i++;
	}
	return (len);
}

char	**tab_space_split(char const *s)
{
	char	**arr;
	int		*ijk;
	int		k;

	ijk = (int [2]){0, 0};
	arr = (char **)malloc(sizeof(char *) * (nb_words(s) + 1));
	if (!s || !(arr))
		return (NULL);
	while (s[ijk[0]])
	{
		k = 0;
		if (s[ijk[0]] != ' ' && s[ijk[0]] != '\t')
		{
			arr[ijk[1]] = (char *)malloc(sizeof(char) * (wrdl(s, ijk[0]) + 1));
			if (!(arr[ijk[1]]))
				return (NULL);
			while (s[ijk[0]] && s[ijk[0]] != ' ' && s[ijk[0]] != '\t')
				arr[ijk[1]][k++] = s[ijk[0]++];
			arr[ijk[1]++][k] = '\0';
		}
		else
			ijk[0]++;
	}
	arr[ijk[1]] = NULL;
	return (arr);
}
