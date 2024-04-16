/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:37:52 by abutet            #+#    #+#             */
/*   Updated: 2024/04/16 12:37:52 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_true_strjoin(char *s1, char *s2)
{
	char	*sj;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	if (!s1 || !s2)
		return (NULL);
	sj = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!sj)
		return (NULL);
	while (s1[++i])
		sj[i] = s1[i];
	while (s2[j])
		sj[i++] = s2[j++];
	sj[i] = '\0';
	return (free(s1), sj);
}

static int	ft_is_new_line(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

static char	*ft_get_line(char *str)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	buff = malloc(sizeof(char) * (i + 2));
	if (!buff)
		return (0);
	while (j <= i)
	{
		buff[j] = str[j];
		j++;
	}
	buff[j] = '\0';
	return (buff);
}

static char	*ft_next(char *str)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	buff = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!buff)
		return (free(str), NULL);
	j = i + 1;
	i = 0;
	while (str[j])
		buff[i++] = str[j++];
	buff[i] = '\0';
	return (free(str), buff);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buff;
	char		*res;
	int			nbytes;

	nbytes = 1;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (free(line), NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (nbytes && !ft_is_new_line(line))
	{
		nbytes = read(fd, buff, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(buff), NULL);
		buff[nbytes] = '\0';
		line = ft_true_strjoin(line, buff);
		if (!line)
			return (free(buff), NULL);
	}
	res = ft_get_line(line);
	line = ft_next(line);
	return (free(buff), res);
}
