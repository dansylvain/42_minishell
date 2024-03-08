/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:57:05 by seblin            #+#    #+#             */
/*   Updated: 2024/03/07 15:02:48 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
int	get_fd_in(t_redir *redir);
int	get_fd_out(t_redir *redir);

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
			close_fds(redir->pipe);
			if (pipe(redir->pipe) < 0)
				exit(1);
			here_doc_handle(redir->pipe, *redir);
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

int	set_all_redir_out(char **argv[], t_redir *redir)
{
	int	ret;

	ret = 0;
	while (*argv && ***argv != '|')
	{
		ret += set_redir_out(*argv, redir);
		if (ret)
			return (ret);
		argv++;
	}
	return (ret);
}

int	set_all_redir_in(char **argv[], t_redir *redir)
{
	int	ret;

	ret = 0;
	while (*argv && ***argv != '|')
	{
		ret += set_redir_in(*argv, redir);
		if (ret)
			return (ret);
		argv++;
	}
	return (ret);
}

void	set_redir_io(char **argv[], t_redir *redir)
{
	if (set_all_redir_in(argv, redir))
		exit(1);
	if (set_all_redir_out(argv, redir))
		exit(1);
}

int	set_io(char **argv[], t_redir *redir)
{
	
	while (*argv  && ***argv != '|')
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
	redir->pipe[0] = -1;
	redir->pipe[1] = -1;
	redir->redir[0] = 0;
	redir->redir[1] = 0;
	redir->delim = NULL;
	redir->filepath[0] = NULL;
	redir->filepath[1] = NULL;
}
