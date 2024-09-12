/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 09:40:04 by wasmar            #+#    #+#             */
/*   Updated: 2024/08/18 13:42:50 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
*/
char	*ft_strnstr(char const *haystack, char const *needle, size_t n)
{
	size_t	j;

	if (!haystack && !n)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && n--)
	{
		j = 0;
		while (*(haystack + j) == *(needle + j)
			&& *(needle + j) && j <= n)
		{
			if (!*(needle + j + 1))
				return ((char *)haystack);
			j++;
		}
		haystack++;
	}
	return (NULL);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	a = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!a)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		a[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		a[i + j] = s2[j];
		j++;
	}
	a[i + j] = '\0';
	return (a);
}
void free_array(char **array)
{
    int i;
    i = 0;
    while(array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
void error(void)
{
	write(1,"ERROR",5);
	_exit(0);
}

