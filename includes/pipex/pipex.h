/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:01 by seblin            #+#    #+#             */
/*   Updated: 2024/03/10 22:13:51 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "ft_printf.h"
# include "libft.h"
# include "minishell.h"
# include "pipex_global_utils.h"

t_Data	*get_data(char *envp[]);
int		command_is_builtin(char	*cmd[], t_Data *data);
char	**search_path(char *argv[], char *envp[]);
void	init_redir( t_redir *redir);
int		set_redir_io(char **argv[], t_redir *redir);
void	pipe_to_screen_or_file(t_redir redir);
void	switch_pipes(int pipefd[][2]);
void	set_pipe_forward(int pipefd_in[], int pipefd_out[]);
void	set_pipefd_in(int pipefd_in[], t_redir *redir);
int		is_path(char *path);
void	free_and_exit(t_redir *redir, char **argv_sav[], int n_exit,
			char *err_str);
void	errno_handle(char **argv[], char **argv_sav[], t_redir *redir);
char	***forward_next_cmd(char **argv[]);
int		forward_next_pipe(char ***argv[]);

#endif