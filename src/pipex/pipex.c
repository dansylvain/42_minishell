/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:23:23 by svidot            #+#    #+#             */
/*   Updated: 2024/03/06 09:18:50 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipes_io(int pipefd_in[2], int pipefd_out[2])
{
	pipefd_in[0] = -1;
	pipefd_in[1] = -1;
	pipefd_out[0] = -1;
	pipefd_out[1] = -1;
}

void	here_doc_handle(int pipefd_in[], t_redir redir) //argv!!
{
	char	*line;

	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (line)
		{
			line[ft_strlen(line) - 1] = 0; //optimisable ... ajout \n a delim
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
		{
			ft_printf("\rwarning: here-document at line 1 \
delimited by end-of-file (wanted '%s')\n", redir.delim);
			break ;
		}
		free(line); //opti
	}
}
void	store_and_free_cmd_list(t_ast_nde *cmd_list);
void	free_data(t_Data *data);
static void	builtin_or_execve(char **argv[], char **argv_sav[],  char *envp[])
{
	t_Data	*data;

	data = get_data(NULL);
	if (!command_is_builtin(*argv, data, envp))
	{
		if (access(**argv, X_OK))
		{
			if (search_path(*argv, envp))
			{
				store_and_free_cmd_list(NULL);
				free_command_tab_lg(argv_sav);	
				exit(127);
			}
		}
		execve(**argv, *argv, envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		free_data(data);
		free_command_tab_lg(argv_sav);
		store_and_free_cmd_list(NULL);
		exit(EXIT_SUCCESS);
	}
}
int	set_io(char **argv[], t_redir *redir);
int	set_all_redir_in(char **argv[], t_redir *redir);
int	set_all_redir_out(char **argv[], t_redir *redir);
static pid_t	nurcery(char **argv[], char *envp[], int fd_file[], int *pipefd[], t_redir *redir)
{
	pid_t	pid;
	char 	***argv_sav;
	pid = -42;
	init_redir(redir);
	if (set_io(argv, redir))
		return (-1);
	set_pipefd_in(pipefd[0], redir);
	argv_sav = argv;
	while (*argv)
	{
		if (***argv != '>' && ***argv != '<')
		{
			if (pipe(pipefd[1]) < 0)
				exit(1);
			pid = fork();
			if (!pid)
			{
				//gerer a chaque pipe savoir si une redir 
	// if (set_all_redir_in(argv, redir))
	// 	exit(1);
	// set_pipefd_in(pipefd[0], redir);
				close_fd(fd_file[1]);
				set_pipe_forward(pipefd[0], pipefd[1], *redir);
				builtin_or_execve(argv, argv_sav, envp);
			}
			else
			{
				//verif si une redir out est prevue our ce
				// si une redir out grere une nouvelle fonction qui ecrira sur le pipe de sortie 
				// if(set_all_redir_out(argv, redir))
				// 	exit(1);
				switch_pipes(pipefd);				
			
			}
		}
		argv++;
	}
	return (pid);
}


static pid_t	create_pipeline(char **argv[], char *envp[], t_redir redir)
{
	int		pipefd_in[2];
	int		pipefd_out[2];
	pid_t	pid;

	pid = -1;
	init_pipes_io(pipefd_in, pipefd_out);
	pid = nurcery(argv, envp, redir.fd_file,
			(int *[]){pipefd_in, pipefd_out}, &redir);
	if (pid < 0)
		return (pid);
	close_fd(pipefd_in[1]);
	pipe_to_screen(pipefd_in[0], redir);
	close_fd(pipefd_in[0]);
	close_fds(pipefd_out);
	return (pid);
}
// int	arr_len(const void *arr[])
// {
// 	int	i;

// 	i = 0;
// 	while(arr[i])
// 		i++;
// 	return (i);
// }
int	pipex(char **argv[], char *envp[])
{
	t_redir	redir;
	pid_t	pid;
	int		status;
	int		exit_status;
	// if (arr_len((void *) *argv))
	// return (
	exit_status = -1;
	pid = -1;
	pid = create_pipeline(argv, envp, redir);
	if (pid == -42)
		return (0);
	if (pid < 0)
		return (1);
	if (waitpid(pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		if (exit_status >= 1)
			exit_status = 127;
	}
	while (wait(&(int){0}) > 0)
		;
	return (exit_status);
}

// int	arr_len(const void *arr[])
// {
// 	int	i;

// 	i = 0;
// 	while(arr[i])
// 		i++;
// 	return (i);
// }

// void	set_redir2(int argc, char **argv[], int redir[])
// {	
// 	redir[0] = 0;
// 	redir[1] = 0;
// 	if (***argv == '<')
// 	{
// 		redir[0] = 1;
// 		if (!ft_strcmp(**argv, "<<"))
// 			redir[0] = 2;	 			
// 	}
// 	if (**(argv)[argc - 1] == '>')
// 	{
// 		redir[1] = 1;		
// 		if (!ft_strcmp(*argv[argc - 1], ">>"))
// 			redir[1] = 2;	
// 	}
// }
// void	set_filepath_and_delim2(int *argc, char ***argv[], t_redir *redir)
// {
// 	redir->delim = NULL;
// 	redir->filepath[0] = NULL;
// 	redir->filepath[1] = NULL;
// 	if (redir->redir[0] == 1)	
// 		redir->filepath[0] = (*(*argv)++)[1];
// 	else if (redir->redir[0] == 2)
// 		redir->delim = (*(*argv)++)[1];
// 	if (redir->redir[0])
// 		(*argc)--;
// 	if (redir->redir[1])
// 	redir->filepath[1] = (*argv)[(*argc) - 1][1];
// }
// void	set_filepath(int *argc, char **argv, char *filepath[])
// {
// 	if (redir->redir[0] == 1)	
// 		redir->filepath[0] = (*argv)++[1];	
// 	if (redir->redir[0])
// 		(*argc)--;
// 	if (redir->redir[1])
// 	redir->filepath[1] = (*argv)[(*argc) - 1][1];

// }


// int	set_io(char **argv[], t_redir *redir)
// {
// 	redir->fd_file[0] = -1;
// 	redir->fd_file[1] = -1;
// 	redir->pipe[0] = -1;
// 	redir->pipe[1] = -1;
// 	redir->redir[0] = 0;	
// 	redir->redir[1] = 0;
// 	redir->delim = NULL;
// 	redir->filepath[0] = NULL;
// 	redir->filepath[1] = NULL;
// 	while (*argv)
// 	{
// 		if (set_redir_in(*argv, redir))
// 			;//return (1);
// 		if (set_redir_out(*argv, redir))
// 			;//return (1);
// 		argv++;
// 	}
// 	return (0);
// }




