/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:40:00 by abutet            #+#    #+#             */
/*   Updated: 2024/04/16 12:40:03 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_struct
{
	int		in;
	int		out;
	int		pip[2];
	pid_t	f1;
	pid_t	f2;
	char	*joined;
	char	**arg_spl;
	char	**spl_path;
}			t_struct;

void	init_struct(t_struct *stru);
void	free_struct(t_struct *stru);
void	exit_free(t_struct *stru, char *message, int num);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlen(char *str);

#endif
