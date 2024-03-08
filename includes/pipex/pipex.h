/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:20:01 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 12:01:41 by svidot           ###   ########.fr       */
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
# include "../../lib/gnl/get_next_line.h"
# include "pipex_utils.h"
# include "../../includes/minishell.h"

int		command_is_builtin(char	*cmd[], t_Data *data);
char	**search_path(char *argv[], char *envp[]);
t_Data	*get_data(char *envp[]);
void	init_redir( t_redir *redir);
void	init_pipes_io(int pipefd_in[2], int pipefd_out[2]);
int		set_redir_io(char **argv[], t_redir *redir);
void	pipe_to_screen_or_file(int pipe, t_redir redir);
void	switch_pipes(int *pipefd[]);
void	set_pipe_forward(int pipefd_in[], int pipefd_out[], t_redir redir);
void	set_pipefd_in(int pipefd_in[], t_redir *redir);

#endif