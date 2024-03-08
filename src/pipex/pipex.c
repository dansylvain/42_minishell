/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:23:23 by svidot            #+#    #+#             */
/*   Updated: 2024/03/08 13:35:00 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
#include <sys/stat.h>
int	is_dir(char *path)
{
	struct stat path_stat;
	
	if (stat(path, &path_stat) == 0) 
	{
        if (S_ISREG(path_stat.st_mode)) 
		{
          	return (0);
        } 
		else if (S_ISDIR(path_stat.st_mode)) 
		{
            return (1);
        } 
		else 
		{
            return (0);
        }
    } 
	return (0);     
}

static void	builtin_or_execve(char **argv[], char **argv_sav[])
{
	t_Data	*data;

	data = get_data(NULL);
	if (!access(**argv, F_OK))
	{
		if (***argv == '.' && argv[0][0][1] == '/' || argv[0][0][0] == '/')
		{
			if (access(**argv, X_OK))
			{				
				display_error(" Permission denied\n");
				exit (126);			
			}
		}
		else 
		{	
			display_error(" command not found\n");		
			exit (127);
		}
	}
	else if (***argv == '.' && argv[0][0][1] == '/' || argv[0][0][0] == '/')		
		display_error(" No such file or directory\n");
	if (!command_is_builtin(*argv, data))
	{
		// ft_printf("la commande n'est pas un builtin -%i-\n", errno);
		
		if (access(**argv, X_OK))
		{
				 
			if (errno == EISDIR)		
			{				
				//Cible est un répertoire
				exit(127); // Ou un autre code de votre choix
			}
			if (search_path(*argv, data->envp_tab))
			{
				if (!access(**argv, F_OK) && access(**argv, X_OK) )
				{					
				//	ft_printf("le fichier n'existe pas dans le rep courant-%i-\n", errno);
					exit (126);
				}
				store_and_free_cmd_list(NULL);
				free_command_tab_lg(argv_sav);					
				//  ft_printf("chemin non trouvé... exit -%i-\n", errno);
				exit(127);
			}
			// else
			// 	ft_printf("chemin trouvé! execve -%i-\n", errno);
			if (errno == EACCES)
			{			
				// Commande non exécutable ou permissions insuffisantes
				exit(127);
			}
		}
	
		execve(**argv, *argv, data->envp_tab);
	//	ft_printf("erreur de exeve -%i-\n", errno);
		if (errno == ENOENT)
		{
			display_error(" BOOOUUM !!\n");
			//!!
			// Commande non trouvée
			exit(127);
		} 
		else if (errno == EISDIR)		
		{
			//!!
    		// Cible est un répertoire
   			 exit(127); // Ou un autre code de votre choix
		}
		else if (errno == EACCES)
		{
			display_error(" Is a directory\n");
			// Commande non exécutable ou permissions insuffisantes
			exit(126);
		}	
	}
	else
	{
		free_data(data);
		free_command_tab_lg(argv_sav);
		store_and_free_cmd_list(NULL);
		exit(EXIT_SUCCESS);
	}
}

void	child_area(char **argv[], char **argv_sav[], char **argv_redir[], int *pipefd[], t_redir *redir)
{
	set_redir_io(argv_redir, redir);
	if (redir->redir[0])
		set_pipefd_in(pipefd[0], redir);
	if (redir->redir[1])
		pipefd[1][1] = redir->fd_file[1];
	set_pipe_forward(pipefd[0], pipefd[1], *redir);
	builtin_or_execve(argv, argv_sav);
}

static pid_t	nurcery(char **argv[], int fd_file[], int *pipefd[], t_redir *redir)
{
	pid_t	pid;
	char 	***argv_sav;
	char 	***argv_redir;

	pid = -42;
	argv_sav = argv;
	argv_redir = argv;	
	while (*argv)
	{	
		if (***argv == '|')
			argv_redir = argv + 1;
		if (***argv != '>' && ***argv != '<' && ***argv != '|')
		{
			if (pipe(pipefd[1]) < 0)
				exit(1);
			pid = fork();
			if (!pid)
				child_area(argv, argv_sav, argv_redir, pipefd, redir);
			else
				switch_pipes(pipefd);
		}
		argv++;
	}
	return (pid);
}

static pid_t	create_pipeline(char **argv[])
{	
	pid_t	pid;
	t_redir redir;
	
	pid = -1;	
	init_redir(&redir);	
	pid = nurcery(argv, redir.fd_file,
			(int *[]){redir.pipe_io[0], redir.pipe_io[1]}, &redir);
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
