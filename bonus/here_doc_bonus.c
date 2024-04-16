/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:38:14 by abutet            #+#    #+#             */
/*   Updated: 2024/04/16 12:38:16 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc_checker(char **argv, t_struct *stru)
{
	if (argv[1] && !ft_strncmp("here_doc", argv[1], 8))
	{
		here_doc(argv, stru);
		return (stru->here_doc = 1);
	}
	else
		return (stru->here_doc = 0);
}

void	here_doc_helper(t_struct *stru, char **line)
{
	write(stru->in, *line, ft_strlen(*line));
	free(*line);
	write(1, "heredoc>", 8);
	*line = get_next_line(0);
	if (!*line)
	{
		close(stru->in);
		exit(1);
	}
}

void	here_doc(char **argv, t_struct *stru)
{
	char	*line;

	stru->in = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0700);
	if (stru->in < 0)
		exit_free(stru, "impossible to create here_doc\n", 1);
	write(1, "heredoc>", 8);
	line = get_next_line(0);
	if (!line)
	{
		close(stru->in);
		exit(1);
	}
	while (ft_strncmp(line, argv[2], ft_strlen(argv[2])))
		here_doc_helper(stru, &line);
	free(line);
	get_next_line(-1);
	close(stru->in);
	stru->in = open(".here_doc", O_RDONLY);
	unlink(".here_doc");
	if (stru->in < 0)
		exit_free(stru, "No here_doc file\n", 1);
}
