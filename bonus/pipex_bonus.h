/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:38:56 by abutet            #+#    #+#             */
/*   Updated: 2024/04/16 12:38:58 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

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
	int		i;
	int		in;
	int		out;
	int		prev;
	int		here_doc;
	pid_t	*ch;
	char	*joined;
	char	**arg_spl;
	char	**spl_path;
}			t_struct;

void	exit_close(t_struct *stru);
void	init_struct(t_struct *stru);
void	free_struct(t_struct *stru);
void	here_doc(char **argv, t_struct *stru);
void	exit_free(t_struct *stru, char *message, int num);
void	child_last(t_struct *stru, char **argv, char **envp);
void	childminder(t_struct *stru, char **argv, char **envp);
void	child_first(t_struct *stru, char **argv, char **envp);
void	child_midle(t_struct *stru, char **argv, char **envp);
char	*get_next_line(int fd);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*command_check(t_struct *stru, char **envp);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		here_doc_checker(char **argv, t_struct *stru);
size_t	ft_strlen(char *str);

#endif
