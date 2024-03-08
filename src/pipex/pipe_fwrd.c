/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fwrd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:20:41 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 12:19:19 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_fwrd.h"

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
		pipefd_in[0] = redir->file_fd[0];
	else if (redir->redir[0] == 2)
	{
		pipefd_in[0] = redir->hd_pipe[0];
		pipefd_in[1] = redir->hd_pipe[1];
	}
}

void	switch_pipes(int *pipefd[])
{
	close_fds(pipefd[0]);
	pipefd[0][0] = pipefd[1][0];
	pipefd[0][1] = pipefd[1][1];
}

void	pipe_to_screen_or_file(int pipe, t_redir redir)
{
	char	buf;

	if (redir.redir[1])
	{
		while (read(pipe, &buf, 1))
			ft_putchar_fd(buf, redir.file_fd[1]);
	}
	else
	{
		while (read(pipe, &buf, 1))
			ft_putchar_fd(buf, 1);
	}
}

void	init_pipes_io(int pipefd_in[2], int pipefd_out[2])
{
	pipefd_in[0] = -1;
	pipefd_in[1] = -1;
	pipefd_out[0] = -1;
	pipefd_out[1] = -1;
}
