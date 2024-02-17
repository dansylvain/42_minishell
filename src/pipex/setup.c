/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:45:59 by svidot            #+#    #+#             */
/*   Updated: 2024/02/17 18:19:03 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

#include "pipex_setup.h"

static void	close_fd(int fd[])
{
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
}

static char	*create_strerror(char *error_str, char *filepath)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	tmp = ft_strjoin(strerror(errno), ": ");
	tmp2 = ft_strjoin(tmp, filepath);
	tmp3 = ft_strjoin(tmp2, "\n");
	tmp4 = NULL;
	if (*error_str)
		tmp4 = error_str;
	error_str = ft_strjoin(error_str, tmp3);
	free(tmp);
	free(tmp2);
	free(tmp3);
	if (tmp4)
		free(tmp4);
	return (error_str);
}

char	*get_fd_outfile(char *error_str, t_redir *redir)
{
	if (redir->redir[1] == 1)
	{	
		redir->fd_file[1] = open(redir->filepath[1], O_WRONLY | O_CREAT 
				| O_TRUNC, 400);
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
	return (error_str);
}

int	get_fdio(t_redir *redir)
{
	char	*error_str;
	
	error_str = "";
	redir->fd_file[0] = -1;
	redir->fd_file[1] = -1;
	if (redir->redir[0] == 1)
	{
		redir->fd_file[0] = open(redir->filepath[0], O_RDONLY);
		if (redir->fd_file[0] < 0)
			error_str = create_strerror(error_str, redir->filepath[0]);	
	}
	error_str = get_fd_outfile(error_str, redir);
	if (*error_str)
		return (ft_putstr_fd(error_str, STDERR_FILENO), free(error_str),
			close_fd(redir->fd_file), 1);
	return (0);
}
	