/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:23:23 by svidot            #+#    #+#             */
/*   Updated: 2024/02/07 16:12:24 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
#include "../../lib/get_next_line/get_next_line.h"
#include "pipex_setup.h"

void	set_filepath_and_delim(int *argc, char **argv[], t_redir *redir);
void	get_fdio(t_redir *redir);
char	**parse_cmd(char *argv[], char *envp[]);

void	set_pipe_forward(int pipefd_in[], int pipefd_out[], t_redir redir)
{
	if (pipefd_in[0])
	{		
		dup2(pipefd_in[0], STDIN_FILENO);
		close(pipefd_in[0]);
	}
		close(pipefd_in[1]);
	dup2(pipefd_out[1], STDOUT_FILENO);
	close(pipefd_out[1]);
	close(pipefd_out[0]);
}

pid_t	nurcery(char *argv[], char *envp[], int fd_file[], int *pipefd[], t_redir redir)
{
	pid_t	pid;
	char	**split;
	int		offset;
	
	offset = 0;
	if (redir.redir[1])
		offset = 3;
	while (*(argv + offset))
	{
		pid = fork();
		if (pid == 0)
		{
			close(fd_file[1]);
			set_pipe_forward(pipefd[0], pipefd[1], redir);
			split = parse_cmd(argv, envp);
			execve(split[0], split, envp);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipefd[0][1]);
			if (pipefd[0][0] > 2)
				close(pipefd[0][0]);
			pipefd[0][0] = pipefd[1][0];
			pipefd[0][1] = pipefd[1][1];
			pipe(pipefd[1]);
		}
		argv++;
	}
	return (pid);
}

void	here_doc_handle(char **argv[], int pipefd_in[], t_redir redir)
{
	char	*line;
		
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (line)
		{
			line[ft_strlen(line) - 1] = 0;
			if (ft_strcmp(line, redir.delim))
			{
				line[ft_strlen(line)] = '\n';
				ft_putstr_fd(line, pipefd_in[1]);
			}
			else
			{
				free(line);
				get_next_line(42);
				break ;
			}
		}
		else	
			break ;
		free(line);
	}
}
// void	here_doc_handle(char **argv[], int pipefd_in[])
// {
// 	(void) argv;
// 	(void) pipefd_in;
// }
pid_t	create_pipeline(char *argv[], char *envp[], t_redir redir)
{
	int		pipefd_in[2];
	int		pipefd_out[2];
	char	buf;
	pid_t	pid;
	
	pid = -1;
	pipe(pipefd_in);
	pipe(pipefd_out);
	if (!redir.redir[0])
	{
		close(pipefd_in[0]);
		pipefd_in[0] = 0;
	}
	else if (redir.redir[0] == 1)
	{		
		close(pipefd_in[0]);
		pipefd_in[0] = redir.fd_file[0];
	}
	else if (redir.redir[0] == 2)
		here_doc_handle(&argv, pipefd_in, redir);
	pid = nurcery(argv, envp, redir.fd_file, (int *[]){pipefd_in, pipefd_out}, redir);
	close(pipefd_in[1]);
	close(pipefd_out[1]);
	close(pipefd_out[0]);
	if (redir.redir[1])
	{
		while (read(pipefd_in[0], &buf, 1))
			ft_putchar_fd(buf, redir.fd_file[1]);
		close(redir.fd_file[1]);		
	}
	else
	{		
		while (read(pipefd_in[0], &buf, 1))
			ft_putchar_fd(buf, 1);		
	}
	close(pipefd_in[0]);
	return (pid);
}

int	arr_len(const void *arr[])
{
	int	i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}

void	set_redir(int *argc, char **argv[], int redir[])
{	
	redir[0] = 0;
	redir[1] = 0;
	if (***argv == '<')
	{
		redir[0] = 1;
		if (!ft_strcmp(**argv, "<<"))
			redir[0] = 2;	 
		(*argv)++;
		(*argc)--;	
	}
	if (*(*argv)[*argc - 2] == '>')
	{
		redir[1] = 1;		
		if (!ft_strcmp((*argv)[*argc - 2], ">>"))
			redir[1] = 2;	
	}
}
void	set_filepath_and_delim(int *argc, char **argv[], t_redir *redir)
{
	redir->delim = NULL;
	redir->filepath[0] = NULL;
	redir->filepath[1] = NULL;
	if (redir->redir[0] == 1)	
		redir->filepath[0] = *(*argv)++;
	else if (redir->redir[0] == 2)
		redir->delim = *(*argv)++;
	if (redir->redir[0])
		(*argc)--;
	if (redir->redir[1])
	redir->filepath[1] = (*argv)[(*argc) - 1];
}
int	pipex(char *argv[], char *envp[])
{
	t_redir redir;
	int		argc;
	pid_t	pid;
	int status;
	int exit_status;
	
	exit_status = -1;
	pid = -1;
	argc = arr_len((void *)argv);
	if (!argc)
		return (1);
	set_redir(&argc, &argv, redir.redir);
	set_filepath_and_delim(&argc, &argv, &redir);
	get_fdio(&redir);
//ft_printf("argv: %s, redir 0:%d, redir 1:%d, fdfile 0:%d, fdfile 1:%d, filepath 0:%s, filepath 1:%s, delim : %s", *argv, redir.redir[0], redir.redir[1], redir.fd_file[0], redir.fd_file[1], redir.filepath[0], redir.filepath[1], redir.delim); exit(1);
	pid = create_pipeline(argv, envp, redir);	
	if(waitpid(pid, &status, 0) > 0) // Attend spécifiquement la fin du dernier processus enfant
	{
		if (WIFEXITED(status))		
    		exit_status = WEXITSTATUS(status);		
	}
	else 
    	ft_printf("waitpid a échoué ou il n'y avait aucun enfant à attendre\n");
	while (wait(&(int){0}) > 0)
		;
	return (exit_status);
}
