/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fwrd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:20:41 by seblin            #+#    #+#             */
/*   Updated: 2024/02/28 13:56:24 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex_setup.h"
#include "libft.h"

void	close_fds(int fd[]);
void	close_fd(int fd);

void	set_pipe_forward(int pipefd_in[], int pipefd_out[], t_redir redir)
{
	dup2(pipefd_in[0], STDIN_FILENO);
	close_fds(pipefd_in);
	dup2(pipefd_out[1], STDOUT_FILENO);
	close_fds(pipefd_out);
}

void	set_pipefd_in(int pipefd_in[], t_redir *redir)
{
	if (!redir->redir[0])
		pipefd_in[0] = 0;
	else if (redir->redir[0] == 1)
		pipefd_in[0] = redir->fd_file[0];
	else if (redir->redir[0] == 2)
	{
		pipefd_in[0] = redir->pipe[0];
		pipefd_in[1] = redir->pipe[1];
	}
}

void	switch_pipes(int *pipefd[])
{
	close_fds(pipefd[0]);
	pipefd[0][0] = pipefd[1][0];
	pipefd[0][1] = pipefd[1][1];
}

void	pipe_to_screen(int pipe, t_redir redir)
{
	char	buf;

	if (redir.redir[1])
	{
		while (read(pipe, &buf, 1))
			ft_putchar_fd(buf, redir.fd_file[1]);
	}
	else
	{
		while (read(pipe, &buf, 1))
			ft_putchar_fd(buf, 1);
	}
}
