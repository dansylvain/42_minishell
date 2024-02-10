/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/02/09 16:16:08 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
// # include "../lib/get_next_line/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct t_Data
{
	char	**envp_tab;
}	t_Data;

void	handle_signals(void);
int		prompt_loop(t_Data *data, char *envp[]);
void	display_error(char *str);
void	free_data(t_Data *data);
void	close_minishell(t_Data *data);
void	exec_env(char *envp[], char **command_tab);
int		command_is_builtin(char	*cmd[], t_Data *data, char *envp[]);
void	exec_pwd(void);
int		exec_cd(char **command_tab);
void	exec_echo(char **command_tab);
void	exec_unset(char *envp[], char **command_tab);
void	free_command_tab(char **command_tab);
char	**duplicate_envp(t_Data *data, char *envp[]);
int		exec_export(char **command_tab, t_Data *data);

#endif
