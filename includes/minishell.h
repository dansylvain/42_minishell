/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 08:59:03 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 13:35:43 by seblin           ###   ########.fr       */
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
# include "parsing_utils.h"
# include <dirent.h>

typedef struct t_Data
{
	char	**envp_tab;
	int		exit_status;
}	t_Data;

// extern t_Data	*data;

t_Data	*get_data(char *envp[]);


void	build_prompt(char prompt[]);
void	handle_signals(void);
int		prompt_loop(t_Data *data, char *envp[]);
void	display_error(char *str);
void	display_error_detail(char *str, char *details, char *str2);
void	free_data(t_Data *data);
void	close_minishell(t_Data *data);
void	exec_env(t_Data *data, char **command_tab);
int		command_is_builtin(char	*cmd[], t_Data *data);
void	exec_pwd(t_Data *data);
int		exec_cd(t_Data *data, char **command_tab);
void	exec_echo(t_Data *data, char **command_tab);
void	exec_unset(t_Data *data, char **command_tab);
void	free_command_tab(char ***command_tab);
char	**duplicate_envp(t_Data *data, char *envp[]);
int		exec_export(char **command_tab, t_Data *data);

/*   exec_export.c                                  :+:      :+:    :+:   */
void	add_env_var_to_envp_tab(char **command_tab, t_Data *data, int *i);
char	**create_new_env_var(char **envp, char *env_var);
char	*get_env_var(t_Data *data, char *to_find);
void	display_export_tab(char export_tab[][500]);
void	create_export_tab(t_Data *data, char export_tab[][500]);
int		are_only_valid_chars(char *str);
int		are_only_valid_chars(char *str);
char	*get_env_var(t_Data *data, char *to_find);
int		has_var(char *str);
void	insert_quote(char *str);
void	format_export_tab(char export_tab[][500]);



/*   exec_echo.c                                  :+:      :+:    :+:   */
int	is_only_space(char *str);

/*   exec_exit.c                                  :+:      :+:    :+:   */
int	str_is_digit(char *str);

/*   exec_unset.c                                  :+:      :+:    :+:   */
void	unset_var(char **envp, int index);


void		free_command_tab_lg(char ***command_tab);
int			pipex(char **argv[]);
t_ast_nde	*copy_node_child(t_ast_nde *node);

/*   exec_pipex.c                                       :+:      :+:    :+:   */
char		**parse_cmd(char **command, char **env);
t_ast_nde	*parse(char *str, t_Data *data);
void		launch_command_tab(t_Data *data, t_ast_nde *node,
				char *envp[], int flag);
char			*wilcard_func(char *pattern);
void	store_and_free_cmd_list(t_ast_nde *cmd_list);


/*   handle_signals.c                                   :+:      :+:    :+:   */
void	sigint_handler(int signum);
void	sigquit_handler(int signum);

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


int	create_separator_tab(t_Data *data, t_ast_nde **node, char ****cmd_tab, int *i);
int	create_chevron_tab(char ****cmd_tab, int *i, t_ast_nde **node, t_Data *data);

void		exec_pipex(t_Data *data, char *cmd, char *envp[]);
int			exec_exit(t_Data *data, char **command_tab);

/*   create_envp.c                                      :+:      :+:    :+:   */
void	update_shlvl(char	**envp_tab);



/*   wildcard_expansion.c                               :+:      :+:    :+:   */
int		get_matching_elements(const char *pattern, DIR *dir,
			struct dirent *entry, char ***matches);
int		matches_pattern(const char *filename, const char *pattern);
char	*wilcard_func(char *pattern);
char	**expand_wildcards(const char *pattern);
int		get_str_size(char **matches);
char	*copy_matches(char ***matches, char **ret_str,
			int index, char **pattern);
			
#endif