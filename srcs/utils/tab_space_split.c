
#include "../../inc/minirt.h"

int    nb_words(char const *s)
{
	int    i;
	int    count;

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

int    word_len(char const *s, int i)
{
	int    len;

	len = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		len++;
		i++;
	}
	return (len);
}

char   **tab_space_split(char const *s)
{
	char   **arr;
	int       i;
	int       j;
	int       k;

	i = 0;
	j = 0;
	if (!s || !(arr = (char **)malloc(sizeof(char *) * (nb_words(s) + 1))))
		return (NULL);
	while (s[i])
	{
		k = 0;
		if (s[i] != ' ' && s[i] != '\t')
		{
			if (!(arr[j] = (char *)malloc(sizeof(char) * (word_len(s, i) + 1))))
				return (NULL);
			while (s[i] && s[i] != ' ' && s[i] != '\t')
				arr[j][k++] = s[i++];
			arr[j++][k] = '\0';
		}
		else
			i++;
	}
	arr[j] = NULL;
	return (arr);
}
