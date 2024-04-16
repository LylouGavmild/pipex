/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:37:38 by abutet            #+#    #+#             */
/*   Updated: 2024/04/16 12:37:39 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	childminder(t_struct *stru, char **argv, char **envp)
{
	stru->arg_spl = ft_split(argv[stru->i + 2 + stru->here_doc], ' ');
	if (!stru->arg_spl)
		exit_free(stru, "arg_spl allocation fail while spliting\n", 1);
	command_check(stru, envp);
	execve(stru->joined, stru->arg_spl, envp);
	free_struct(stru);
	exit(127);
}

void	child_first(t_struct *stru, char **argv, char **envp)
{
	int	pip[2];

	if (pipe(pip) == -1)
	{
		perror("pipe");
		exit_close(stru);
	}
	stru->ch[stru->i] = fork();
	if (stru->ch[stru->i] == 0)
	{
		dup2(pip[1], 1);
		close(pip[0]);
		close(pip[1]);
		if (stru->in == -1)
			exit (1);
		dup2(stru->in, 0);
		close(stru->in);
		childminder(stru, argv, envp);
	}
	close(pip[1]);
	if (stru->in != -1)
		close(stru->in);
	stru->prev = pip[0];
}

void	child_last(t_struct *stru, char **argv, char **envp)
{
	stru->ch[stru->i] = fork();
	if (stru->ch[stru->i] == 0)
	{
		dup2(stru->prev, 0);
		dup2(stru->out, 1);
		close (stru->prev);
		close (stru->out);
		childminder(stru, argv, envp);
	}
	close(stru->out);
	close(stru->prev);
}

void	child_midle(t_struct *stru, char **argv, char **envp)
{
	int	pip[2];

	if (pipe(pip) == -1)
	{
		perror("pipe");
		exit_close(stru);
	}
	stru->ch[stru->i] = fork();
	if (stru->ch[stru->i] == 0)
	{
		close(pip[0]);
		dup2(stru->prev, 0);
		dup2(pip[1], 1);
		close(stru->prev);
		close(pip[1]);
		childminder(stru, argv, envp);
	}
	close(pip[1]);
	close(stru->prev);
	stru->prev = pip[0];
}
