/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:25:46 by wasmar            #+#    #+#             */
/*   Updated: 2024/08/18 12:26:30 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
static	size_t	wordt_count(const char *str, char c)
{
	size_t	i;
	size_t	t_count;

	i = 0;
	t_count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			t_count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (t_count);
}

static size_t	returnres(const char *str, char c, size_t k)
{
	size_t	t_count;

	t_count = 0;
	while (str[k] == c)
		(k)++;
	while (str[k] != '\0' && str[k] != c)
	{
		t_count++;
		k++;
	}
	return (t_count);
}

static	void	fillwords(const char *str, char **res, char c, size_t *k)
{
	size_t	i;

	i = 0;
	while (str[*k] == c)
		(*k)++;
	while (str[*k] != '\0' && str[*k] != c)
	{
		(*res)[i] = str[*k];
		i++;
		(*k)++;
	}
	(*res)[i] = '\0';
	while (str[*k] == c)
		(*k)++;
}

void	freeres(char ***res, int i)
{
	while (i > 0)
	{
		free(*(res[i - 1]));
		i--;
	}
	free(*res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	res = (char **)malloc(sizeof(char *) * (wordt_count(s, c) + 1));
	if (!res)
		return (NULL);
	while (i < (wordt_count(s, c)))
	{
		res[i] = (char *)malloc(sizeof(char) * (returnres(s, c, k) + 1));
		if (!res[i])
		{
			freeres(&res, i);
		}
		fillwords(s, &(res[i]), c, &k);
		i++;
	}
	res[i] = NULL;
	return (res);
}