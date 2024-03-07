/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:23:23 by svidot            #+#    #+#             */
/*   Updated: 2024/03/07 15:08:49 by seblin           ###   ########.fr       */
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
#include <sys/stat.h>
int	is_dir(char *path)
{
	struct stat path_stat;
	if (stat(path, &path_stat) == 0) {
        if (S_ISREG(path_stat.st_mode)) {
          	return (0);
        } else if (S_ISDIR(path_stat.st_mode)) {
            return (1);
        } else {
            return (0);
        }
    } else {
        ;//perror("stat a échoué pour le chemin");
    }   
}

static void	builtin_or_execve(char **argv[], char **argv_sav[],  char *envp[])
{
	t_Data	*data;

	data = get_data(NULL);
	if (!access(**argv, F_OK))
	{
		if (***argv == '.' && argv[0][0][1] == '/' || argv[0][0][0] == '/')
			exit (126);
		else 
			exit (127);
	}
	// else
	// {
	// 	ft_printf("NODIR!!!\n");	
	// }
		// if (access(**argv, X_OK))
		// {
		// 	exit (126);
		// }	
	if (!command_is_builtin(*argv, data, envp))
	{
		// ft_printf("la commande n'est pas un builtin -%i-\n", errno);
		
		if (access(**argv, X_OK))
		{
			// ft_printf("non executable -%i-\n", errno);
			// if (access(**argv, F_OK))
			// {
			//  	ft_printf("le fichier n'existe pas dans le rep courant-%i-\n", errno);
				
			// }
		
			if (errno == EISDIR)		
			{
				//Cible est un répertoire
				exit(127); // Ou un autre code de votre choix
			}
			if (search_path(*argv, envp))
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
		// if (!access(**argv, F_OK))
		// {
		// 	ft_printf("le fichier existe dans le rep courant! -%i-\n", errno);
		// //	exit()
		// }
		// ft_printf("le fichier est executable et av etre envoyé a execve -%i-\n", errno);
		// if (errno == EBADF) //9
		// {
		// 	// Commande non trouvée
		// 	exit(127);
		// } 
		execve(**argv, *argv, envp);
	//	ft_printf("erreur de exeve -%i-\n", errno);
		if (errno == ENOENT)
		{
			// Commande non trouvée
			exit(127);
		} 
		else if (errno == EISDIR)		
		{
    		// Cible est un répertoire
   			 exit(127); // Ou un autre code de votre choix
		}
		else if (errno == EACCES)
		{
			// Commande non exécutable ou permissions insuffisantes
			exit(126);
		}
		// else if (errno == EINVAL)
		// {
		// 	// Argument invalide
		// 	exit(13);
		// }
		// else if (errno == ETXTBSY)
		// {
		// 	// Texte occupé
		// 	exit(14);
		// }
		// else if (errno == E2BIG)
		// {
		// 	// Liste d'arguments trop longue
		// 	exit(15);
		// }
		// else if (errno == ENOMEM)
		// {
		// 	// Pas assez d'espace mémoire
		// 	exit(16);
		// }
		// else if (errno == EFAULT)
		// {
		// 	// Mauvaise adresse
		// 	exit(17);
		// }
		// else
		// {
		// 	// Autres erreurs
		// 	exit(18);
		// }

	
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
	char 	***argv_redir;

	pid = -42;
	argv_sav = argv;
	argv_redir = argv;
	init_redir(redir);
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
			{				
				set_io(argv_redir, redir);		
				if (redir->redir[0])
					set_pipefd_in(pipefd[0], redir);
				if (redir->redir[1])							
					pipefd[1][1] = redir->fd_file[1];							
				set_pipe_forward(pipefd[0], pipefd[1], *redir);
				builtin_or_execve(argv, argv_sav, envp);
			}
			else					
				switch_pipes(pipefd);			
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
	pipe_to_screen_or_file(pipefd_in[0], redir);
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
	exit_status = 1;
	pid = -1;
	pid = create_pipeline(argv, envp, redir);
	if (pid == -42)
		return (0);
	// if (pid < 0)
	// 	return (1);
	if (waitpid(pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		// if (exit_status >= 1)
		// 	exit_status = 127;
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




