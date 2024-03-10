/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:23:23 by svidot            #+#    #+#             */
/*   Updated: 2024/03/10 13:37:58 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	builtin_or_execve(char **argv[], char **argv_sav[], t_redir *redir)
{
	t_Data	*data;

	data = get_data(NULL);	
	if (!command_is_builtin(*argv, data))
	{
		if (!is_path(**argv))
		{		
			if (search_path(*argv, data->envp_tab))
				free_and_exit(redir, argv_sav, 127, NULL);
		}
		execve(**argv, *argv, data->envp_tab);
		execve(**argv, *argv, data->envp_tab);
		//ft_printf("%i\n", errno);	
		//perror("execve"); // Utilise errno pour générer un message d'erreur explicite
	//	exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
// ft_printf("%i\n", errno);	
		execve(**argv, *argv, data->envp_tab);			
		//ft_printf("%i\n", errno);	
		//perror("execve"); // Utilise errno pour générer un message d'erreur explicite
	//	exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
// ft_printf("%i\n", errno);	
		if (errno == EACCES)
		{
			if (access(**argv, X_OK))
			{
				display_error("minishell: ");
				display_error(**argv);
				free_and_exit(redir, argv_sav, 126, ": Permission denied\n");
			}	
			else			
			{	
				display_error("minishell: ");
				display_error(**argv);
				free_and_exit(redir, argv_sav, 126, ": Is a directory\n");
			}
		}
		else if (errno == ENOENT)
		{		
			display_error("minishell: ");
			display_error(**argv);
			free_and_exit(redir, argv_sav, 127, ": No such file or directory\n");			
		}
		else if (errno == ENOEXEC)					
			free_and_exit(redir, argv_sav, EXIT_SUCCESS, NULL);
		free_and_exit(redir, argv_sav, EXIT_FAILURE, NULL);		
	}
	else
		free_and_exit(redir, argv_sav, EXIT_SUCCESS, NULL);
}

static int	forward_next_cmd(char ***argv[])
{
	while  (**argv && ****argv != '|')
	{	
		if (****argv != '>' && ****argv != '<' )
			return (1);
		(*argv)++;		
	}
	return (0);
}

static void	child_area(char **argv[], char **argv_sav[], char **argv_redir[],
	t_redir *redir)
{	
	set_redir_io(argv_redir, redir);
	if (redir->redir[0])
		set_pipefd_in(redir->pipe_io[0], redir);
	if (redir->redir[1])
		redir->pipe_io[1][1] = redir->fd_file[1];
	set_pipe_forward(redir->pipe_io[0], redir->pipe_io[1]);
	if (forward_next_cmd(&argv))			
		builtin_or_execve(argv, argv_sav, redir);
	// else//	ft_printf("je vais execve ou builtin, je dois etre une commande: -%s-\n", **argv);
	// 	{
			
	// 	exit(-175);
	// 	}
}
static int	forward_next_pipe(char ***argv[])
{
	while  (**argv)
	{	
		if (***(*argv)++ == '|')	
			return (1);			
	}
	return (0);	
}

static pid_t	nurcery(char **argv[], t_redir *redir)
{
	pid_t	pid;
	char	***argv_sav;
	char	***argv_redir;

	pid = -42;
	argv_sav = argv;
	argv_redir = argv;

	while(*argv)
	{
		if (pipe(redir->pipe_io[1]) < 0)
			exit(1);
		pid = fork();
		if (!pid)		
			child_area(argv, argv_sav, argv_redir, redir);		
		else
		{
			switch_pipes(redir->pipe_io);		
			if (forward_next_pipe(&argv))			
				argv_redir = argv;	
		}
	}
	return (pid);
}

// static pid_t	nurcery2(char **argv[], t_redir *redir)
// {
// 	pid_t	pid;
// 	char	***argv_sav;
// 	char	***argv_redir;

// 	pid = -42;
// 	argv_sav = argv;
// 	argv_redir = argv;
// 	while (*argv)
// 	{
// 		if (***argv == '|')
// 			argv_redir = argv + 1;
// 	//	if (***argv != '>' && ***argv != '<' && ***argv != '|')
// 	//	{
// 		//if (***argv != '>' && ***argv != '<' && ***argv != '|')
// 			if (pipe(redir->pipe_io[1]) < 0)
// 				exit(1);
// 			pid = fork();
// 			if (!pid)
// 			{
// 				//if (***argv != '>' && ***argv != '<' && ***argv != '|')
// 				child_area(argv, argv_sav, argv_redir, redir);
// 			}
// 			else
// 				switch_pipes(redir->pipe_io);
// 		}
// 		argv++;
// 	}
// 	return (pid);
// }

static pid_t	create_pipeline(char **argv[])
{
	pid_t	pid;
	t_redir	redir;

	pid = -1;
	init_redir(&redir);
	pid = nurcery(argv, &redir);
	if (pid < 0)
		return (pid);
	close_fd(redir.pipe_io[0][1]);
	pipe_to_screen_or_file(redir);
	close_fd(redir.pipe_io[0][0]);
	close_fds(redir.pipe_io[1]);
	return (pid);
}

int	pipex(char **argv[])
{
	pid_t	pid;
	int		status;
	int		exit_status;

	exit_status = 1;
	pid = -1;
	pid = create_pipeline(argv);
	if (pid == -42)
		return (0);
	if (waitpid(pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	while (wait(&(int){0}) > 0)
		;
	return (exit_status);
}
