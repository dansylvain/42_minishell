/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdio.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:45:59 by svidot            #+#    #+#             */
/*   Updated: 2024/03/08 12:25:26 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdio.h"

void	close_fd(int fd)
{
	if (fd > 2)
	{
		close(fd);
		fd = -1;
	}
}

void	close_fds(int fd[])
{
	close_fd(fd[0]);
	close_fd(fd[1]);
}

static char	*create_strerror(char *error_str, char *filepath)
{
	char	*tmp;

	tmp = ft_strjoin_up(filepath, ": ", 0, 0);
	tmp = ft_strjoin_up(tmp, strerror(errno), 1, 0);
	tmp = ft_strjoin_up(tmp, "\n", 1, 0);
	if (*error_str)
		error_str = ft_strjoin_up(error_str, tmp, 1, 1);
	else
		error_str = ft_strjoin_up(error_str, tmp, 0, 1);
	return (error_str);
}

int	get_fd_in(t_redir *redir)
{
	char	*error_str;

	error_str = "";
	redir->fd_file[0] = -1;
	if (redir->redir[0] == 1)
	{
		redir->fd_file[0] = open(redir->filepath[0], O_RDONLY);
		if (redir->fd_file[0] < 0)
			error_str = create_strerror(error_str, redir->filepath[0]);
	}
	if (*error_str)
		return (ft_putstr_fd(error_str, STDERR_FILENO), free(error_str), 1);
	return (0);
}

int	get_fd_out(t_redir *redir)
{
	char	*error_str;

	error_str = "";
	redir->fd_file[1] = -1;
	if (redir->redir[1] == 1)
	{
		redir->fd_file[1] = open(redir->filepath[1], O_WRONLY | O_CREAT
				| O_TRUNC, 0600);
		if (redir->fd_file[1] < 0)
			error_str = create_strerror(error_str, redir->filepath[1]);
	}
	else if (redir->redir[1] == 2)
	{
		redir->fd_file[1] = open(redir->filepath[1], O_WRONLY | O_CREAT
				| O_APPEND, 400);
		if (redir->fd_file[1] < 0)
			error_str = create_strerror(error_str, redir->filepath[1]);
	}
	if (*error_str)
		return (ft_putstr_fd(error_str, STDERR_FILENO), free(error_str), 1);
	return (0);
}
