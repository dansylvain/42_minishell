/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:57:05 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 12:25:52 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static int	set_redir_out(char **argv, t_redir *redir)
{
	if (**argv == '>')
	{
		redir->redir[1] = 1;
		if (!ft_strcmp(*argv, ">>"))
			redir->redir[1] = 2;
		redir->filepath[1] = argv[1];
		if (get_fd_out(redir))
		{
			redir->redir[1] = 0;
			return (1);
		}
	}
	return (0);
}

static int	set_redir_in(char **argv, t_redir *redir)
{
	if (**argv == '<')
	{
		redir->redir[0] = 1;
		if (!ft_strcmp(*argv, "<<"))
		{
			redir->delim = argv[1];
			redir->redir[0] = 2;
			close_fds(redir->pipe_hd);
			if (pipe(redir->pipe_hd) < 0)
				exit(1);
			here_doc_handle(redir->pipe_hd, *redir);
		}
		else
		{
			redir->filepath[0] = argv[1];
			if (get_fd_in(redir))
			{
				redir->redir[0] = 0;
				return (1);
			}
		}
	}
	return (0);
}

int	set_redir_io(char **argv[], t_redir *redir)
{
	while (*argv && ***argv != '|')
	{
		if (set_redir_in(*argv, redir))
			exit (1);
		if (set_redir_out(*argv, redir))
			exit (1);
		argv++;
	}
	return (0);
}

void	init_redir( t_redir *redir)
{
	redir->fd_file[0] = -1;
	redir->fd_file[1] = -1;
	redir->pipe_hd[0] = -1;
	redir->pipe_hd[1] = -1;
	redir->redir[0] = 0;
	redir->redir[1] = 0;
	redir->delim = NULL;
	redir->filepath[0] = NULL;
	redir->filepath[1] = NULL;
}
