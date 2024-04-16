/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:38:50 by abutet            #+#    #+#             */
/*   Updated: 2024/04/16 12:38:52 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	wpids(t_struct *stru)
{
	int	pid;
	int	err;

	pid = 0;
	while (pid < stru->i)
	{
		if (stru->ch[pid] != -1)
			waitpid(stru->ch[pid], &err, 0);
		pid++;
	}
	if (WEXITSTATUS(err))
		return (WEXITSTATUS(err));
	return (0);
}

static int	command_check_helper(t_struct *stru, int i)
{
	char	*tmp;

	tmp = ft_strjoin(stru->spl_path[i], "/");
	stru->joined = ft_strjoin(tmp, (*stru->arg_spl));
	if (!stru->joined)
		exit_free(stru, "stru->joined allocation fail\n", 1);
	free(tmp);
	if (access(stru->joined, X_OK | F_OK) == 0)
		return (1);
	free(stru->joined);
	return (0);
}

char	*command_check(t_struct *stru, char **envp)
{
	int		i;

	if (access(stru->arg_spl[0], X_OK | F_OK) == 0)
		return (stru->joined = stru->arg_spl[0]);
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		exit_free(stru, "No such file or directory\n", 1);
	stru->spl_path = ft_split(envp[i] + 5, ':');
	if (!stru->spl_path)
		exit_free(stru, "spl_path allocation fail\n", 1);
	i = -1;
	while (stru->spl_path[++i])
		if (command_check_helper(stru, i))
			return (NULL);
	stru->joined = NULL;
	return (exit_free(stru, "Command not found\n", 127), NULL);
}

int	micro_main(char **argv, char **envp, t_struct *stru, int argc)
{
	int	err;

	stru->i = -1;
	stru->ch = (pid_t *)malloc(sizeof(pid_t) * (argc - 3 - stru->here_doc));
	if (!stru->ch)
		exit_close(stru);
	while (++stru->i < (argc - 3 - stru->here_doc))
	{
		if (stru->i == 0)
			child_first(stru, argv, envp);
		else if (stru->i == argc - 4 - stru->here_doc)
			child_last(stru, argv, envp);
		else if (stru->i > 0 && stru->i < argc - 4 - stru->here_doc)
			child_midle(stru, argv, envp);
	}
	err = wpids(stru);
	close(stru->prev);
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	stru;
	int			err;

	stru.i = 0;
	if (argc < 5 + here_doc_checker(argv, &stru))
		return (write(2, "Invalid number of arguments\n", 28), 1);
	init_struct(&stru);
	if (!stru.here_doc)
	{
		stru.in = open(argv[1], O_RDONLY);
		if (stru.in < 0)
			perror(argv[1]);
	}
	stru.out = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (stru.out < 0)
	{
		if (stru.in >= 0)
			close(stru.in);
		return (perror(argv[4]), 1);
	}
	err = micro_main(argv, envp, &stru, argc);
	free_struct(&stru);
	return (err);
}
