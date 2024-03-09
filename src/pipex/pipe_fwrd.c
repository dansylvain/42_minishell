/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fwrd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:20:41 by seblin            #+#    #+#             */
/*   Updated: 2024/03/09 17:36:13 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_fwrd.h"

void	set_pipe_forward(int pipefd_in[], int pipefd_out[])
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
		pipefd_in[0] = redir->pipe_hd[0];
		pipefd_in[1] = redir->pipe_hd[1];
	}
}

void	switch_pipes(int pipe_io[][2])
{
	close_fds(pipe_io[0]);
	pipe_io[0][0] = pipe_io[1][0];
	pipe_io[0][1] = pipe_io[1][1];
}

void	pipe_to_screen_or_file(t_redir redir)
{
	char	buf;

	if (redir.redir[1])
	{
		while (read(redir.pipe_io[0][0], &buf, 1))
			ft_putchar_fd(buf, redir.fd_file[1]);
	}
	else
	{
		while (read(redir.pipe_io[0][0], &buf, 1))
			ft_putchar_fd(buf, 1);
	}
}

void	init_pipe_io(t_redir *redir)
{
	redir->pipe_io[0][0] = -1;
	redir->pipe_io[0][1] = -1;
	redir->pipe_io[0][0] = -1;
	redir->pipe_io[0][1] = -1;
}
