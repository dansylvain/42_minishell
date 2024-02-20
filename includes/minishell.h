/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/02/20 18:24:09 by dan              ###   ########.fr       */
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
# include "parsing_utils.h"
# include <dirent.h>

typedef struct t_Data
{
	char	**envp_tab;
	int		exit_status;
}	t_Data;

void	handle_signals(void);
int		prompt_loop(t_Data *data, char *envp[]);
void	display_error(char *str);
void	display_error_detail(char *str, char *details, char *str2);
void	free_data(t_Data *data);
void	close_minishell(t_Data *data);
void	exec_env(t_Data *data, char **command_tab);
int		command_is_builtin(char	*cmd[], t_Data *data, char *envp[]);
void	exec_pwd(t_Data *data);
int		exec_cd(t_Data *data, char **command_tab);
void	exec_echo(t_Data *data, char **command_tab);
void	exec_unset(t_Data *data, char **command_tab);
void	free_command_tab(char **command_tab);
char	**duplicate_envp(t_Data *data, char *envp[]);
int		exec_export(char **command_tab, t_Data *data);

/*   exec_export.c                                  :+:      :+:    :+:   */
void	add_env_var_to_envp_tab(char **command_tab, t_Data *data, int *i);
char	**create_new_env_var(char **envp, char *env_var);
char	*get_env_var(t_Data *data, char *to_find);
void	display_export_tab(char export_tab[][500]);
void	create_export_tab(t_Data *data, char export_tab[][500]);

/*   exec_echo.c                                  :+:      :+:    :+:   */
int	is_only_space(char *str);

/*   exec_exit.c                                  :+:      :+:    :+:   */
int	str_is_digit(char *str);

/*   exec_unset.c                                  :+:      :+:    :+:   */
void	unset_var(char **envp, int index);


void		free_command_tab_lg(char ***command_tab);
int			pipex(char **argv[], char *envp[]);
t_ast_nde	*copy_node_child(t_ast_nde *node);

/*   exec_pipex.c                                       :+:      :+:    :+:   */
char		**parse_cmd(char **command, char **env);
t_ast_nde	*parse(char *str, t_Data *data);
void		launch_command_tab(t_Data *data, t_ast_nde *node,
				char *envp[], int flag);
char			*wilcard_func(char *pattern);


/*   handle_signals.c                                   :+:      :+:    :+:   */
static void	sigint_handler(int signum);
static void	sigquit_handler(int signum);
#endif

/*   create_command_tab.c                           :+:      :+:    :+:   */
t_ast_nde 	*copy_sibling(t_ast_nde *node);

/*   create_command_tab.c                               :+:      :+:    :+:   */
int		is_separator(t_ast_nde *node);
int		is_chevron(t_ast_nde *node);
int		is_pipeline(t_ast_nde *cmd_tab_node_sav);
char	*get_node_str(t_Data *data, t_ast_nde *node);
void	display_command_tab(char **command_tab);
void	display_command_tab_big(char ***command_tab);
void	launch_command_tab(t_Data *data, t_ast_nde *node,
		char *envp[], int flag);
char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[]);
char	***fill_cmd_tab_tabs(t_Data *data, t_ast_nde *node, char ***cmd_tab);
int		get_cmd_nbr(t_ast_nde *node);
void	build_command_tab(char ****cmd_tab, t_Data *data,
		t_ast_nde **cmd_tab_node_sav, char *envp[]);


