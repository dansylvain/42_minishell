/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:56:32 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <minishell.h>
# include "rl_header.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include "ft_printf.h"

int		is_not_empty_prompt(char *str);;
int		main(int argc, char **argv, char *envp[]);
int		prompt_loop(t_Data *data, char *envp[]);
void	build_prompt(char prompt[]);
int		command_is_builtin(char	**cmd_tab, t_Data *data);
void	display_error(char *str);
t_Data	*get_data(char *envp[]);
void	free_data(t_Data *data);
void	handle_signals(void);
char	**duplicate_envp(t_Data *data, char *envp[]);
void	display_error_detail(char *str, char *details, char *str2);
void	exec_pipex(t_Data *data, char *cmd, char *envp[]);
int		is_only_space(char *str);
void	free_command_tab(char ***command_tab);
void	exec_pwd(t_Data *data);
int		exec_cd(t_Data *data, char **command_tab);
void	exec_echo(t_Data *data, char **command_tab);
void	exec_unset(t_Data *data, char **command_tab);
void	exec_env(t_Data *data, char **command_tab);
int		exec_exit(t_Data *data, char **command_tab);
int		exec_export(char **command_tab, t_Data *data);

#endif
