/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:27:30 by seblin            #+#    #+#             */
/*   Updated: 2024/03/10 15:04:59 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

static void	free_all(t_redir *redir, char **argv_sav[])
{
	free_data(get_data(NULL));
	free_command_tab_lg(argv_sav);
	store_and_free_cmd_list(NULL);
	if (redir->delim)
		free(redir->delim);
}

void	free_and_exit(t_redir *redir, char **argv_sav[], int n_exit,
	char *err_str)
{
	if (err_str)
		display_error(err_str);
	free_all(redir, argv_sav);
	exit(n_exit);
}

int	is_dir(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISREG(path_stat.st_mode))
			return (1);
		else if (S_ISDIR(path_stat.st_mode))
			return (1);
		else
			return (0);
	}
	return (0);
}
int	is_path(char *path)
{
	while (*path)	
		if (*path++ == '/')
			return (1);
	return (0);	
}

void	check_filedir_error(char **argv[], char **argv_sav[], t_redir *redir)
{
	if (!access(**argv, F_OK)) // n'est pas un fichier
	{
		if ((***argv == '.' && argv[0][0][1] == '/') || argv[0][0][0] == '/')  // est un path    vis_path(**argv)
		{
			if (access(**argv, X_OK))
				free_and_exit(redir, argv_sav, 126, " Permission denied\n");
		}
		else
		{
			display_error(**argv);
			display_error(":");	
			free_and_exit(redir, argv_sav, 127, " command not found\n");
		}
	}
	else if ((***argv == '.' && argv[0][0][1] == '/') || argv[0][0][0] == '/')
	{
		display_error("minishell: ");
		display_error(**argv);
		display_error(":");
		free_and_exit(redir, argv_sav, 127, " No such file or directory\n");
	}
}

void	handle_ctrl_d(char *line, t_redir *redir)
{
	free(line);
	get_next_line(42);
	char	*ctrl_d = ft_strdup(redir->delim);
	ctrl_d[ft_strlen(redir->delim) - 1] = 0;
	ft_printf("\nwarning: here-document at line 1 \
delimited by end-of-file (wanted '%s\')\n", ctrl_d);
	free(ctrl_d);
}
void	here_doc_handle(t_redir *redir)
{
	char	*line;

	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (line)
		{
			if (line[ft_strlen(line) - 1] != '\n')
				ft_printf("\n");
			else if (ft_strcmp(line, redir->delim))
				ft_putstr_fd(line, redir->pipe_hd[1]);
			else
			{
				free(line);
				get_next_line(42);
				break ;
			}
		}
		else
			return (handle_ctrl_d(line, redir));
		free(line);
	}
}
// void	here_doc_handle2(t_redir *redir)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		ft_printf("heredoc> ");		
// 		if (line)
// 		{
// 			if (ft_strcmp(line, redir->delim))
// 				ft_putstr_fd(line, redir->pipe_hd[1]);
// 			else
// 			{
// 				free(line);
// 				get_next_line(42);
// 				break ;
// 			}
// 		}
// 		else 
// 		{
// 			ft_printf("\rwarning: here-document at line 1 
// delimited by end-of-file (wanted '%s')\n", redir->delim);
// 			break ;
// 		}	
// 		free(line);
// 	}
// }
// void	here_doc_handle3(t_redir *redir)
// {
// 	char	*line;

// 	//ft_printf("heredoc> ");
// 		ft_printf("heredoc> ");	
// 		line = get_next_line(0);
// 	while (1)
// 	{	
// 		if (line)
// 		{
// 			if (line[ft_strlen(line) - 1] == '\n')
// 			{					
// 					//	ft_printf("CRAPEAU\n> ");	
// 				if (ft_strcmp(line, redir->delim))
// 					ft_putstr_fd(line, redir->pipe_hd[1]);
// 				else
// 				{
// 					free(line);
// 					get_next_line(42);
// 					break ;
// 				}		
// 			}
				
// 		}
// 		else if (line[ft_strlen(line) - 1] == '\n')
// 		{
// 			free(line);
// 			get_next_line(42);
// 			char	*ctrl_d = ft_strdup(redir->delim);
// 			ctrl_d[ft_strlen(redir->delim) - 1] = 0;
// 			ft_printf("\nwarning: here-document at line 1 
// delimited by end-of-file (wanted '%s\')\n", ctrl_d);
// 			free(ctrl_d);
// 			break ;
// 		}
// 		if (line[ft_strlen(line) - 1] == '\n')
// 		{
// 			ft_printf("heredoc> ");	
// 		}					
// 		//free(line);
// 		if (line[ft_strlen(line) - 1] != '\n')
// 		{
// 			char * tmp = line;
// 			line = get_next_line(0);
// 			line = tmp;
// 		}
// 		line = get_next_line(0);		
		
// 	}
// }
