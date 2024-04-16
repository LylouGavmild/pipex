/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:39:52 by abutet            #+#    #+#             */
/*   Updated: 2024/04/16 12:39:54 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

char	*command_check(t_struct *stru, char **envp)
{
	char	*tmp;
	int		i;

	if (access(stru->arg_spl[0], X_OK | F_OK) == 0)
		return (stru->joined = stru->arg_spl[0]);
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		exit_free(stru, "No such file or directory\n", 1);
	stru->spl_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (stru->spl_path[++i])
	{
		tmp = ft_strjoin(stru->spl_path[i], "/");
		stru->joined = ft_strjoin(tmp, (*stru->arg_spl));
		free(tmp);
		if (access(stru->joined, X_OK | F_OK) == 0)
			return (NULL);
		free(stru->joined);
	}
	stru->joined = NULL;
	return (exit_free(stru, "Command not found\n", 127), NULL);
}

void	child0(t_struct *stru, char **argv, char **envp)
{
	dup2(stru->pip[1], 1);
	close(stru->pip[0]);
	if (stru->in == -1)
	{
		close(stru->pip[1]);
		close(stru->out);
		exit(1);
	}
	dup2(stru->in, 0);
	close(stru->pip[1]);
	close(stru->in);
	close(stru->out);
	stru->arg_spl = ft_split(argv[2], ' ');
	command_check(stru, envp);
	execve(stru->joined, stru->arg_spl, envp);
	free_struct(stru);
	exit(127);
}

void	child1(t_struct *stru, char **argv, char **envp)
{
	dup2(stru->pip[0], 0);
	close(stru->pip[1]);
	dup2(stru->out, 1);
	close(stru->pip[0]);
	if (stru->in != -1)
		close(stru->in);
	close(stru->out);
	stru->arg_spl = ft_split(argv[3], ' ');
	command_check(stru, envp);
	execve(stru->joined, stru->arg_spl, envp);
	free_struct(stru);
	exit(127);
}

int	micro_main(char **argv, char **envp, t_struct *stru)
{
	int	pid_res;
	int	pid_res1;

	stru->f1 = fork();
	if (stru->f1 == 0)
		child0(stru, argv, envp);
	stru->f2 = fork();
	if (stru->f2 == 0)
		child1(stru, argv, envp);
	close(stru->pip[0]);
	close(stru->pip[1]);
	waitpid(stru->f1, &pid_res, 0);
	waitpid(stru->f2, &pid_res1, 0);
	if (stru->in != -1)
		close(stru->in);
	close(stru->out);
	if (WEXITSTATUS(pid_res1))
		return (WEXITSTATUS(pid_res1));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	stru;
	int			err;

	if (argc != 5)
		return (write(2, "Invalid number of arguments\n", 28), 1);
	init_struct(&stru);
	stru.in = open(argv[1], O_RDONLY);
	if (stru.in < 0)
		perror(argv[1]);
	stru.out = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (stru.out < 0)
	{
		if (stru.in >= 0)
			close(stru.in);
		return (perror(argv[4]), 1);
	}
	if (pipe(stru.pip) < 0)
		return (write(2, "No such file or directory\n", 26), 1);
	err = micro_main(argv, envp, &stru);
	free_struct(&stru);
	return (err);
}
