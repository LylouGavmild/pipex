/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:39:42 by abutet            #+#    #+#             */
/*   Updated: 2024/04/16 12:39:43 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sb;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	if (start < ft_strlen(s))
		while (j < len && s[start + j] != '\0')
			j++;
	sb = (char *)malloc(sizeof(char) * j + 1);
	if (!sb)
		return (0);
	while (i < j)
	{
		sb[i] = s[start + i];
		i++;
	}
	sb[i] = '\0';
	return (sb);
}

static size_t	strlenmal(char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**sn;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	i = 0;
	sn = malloc(sizeof(char *) * (strlenmal(s, c) + 1));
	if (!sn)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (*s && *s != c && ++j)
				s++;
			sn[i++] = ft_substr(s - j, 0, j);
		}
		else
			s++;
	}
	sn[i] = 0;
	return (sn);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (!s1)
		return (0);
	while (n > 0 && (*s1 && *s2) != '\0')
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
