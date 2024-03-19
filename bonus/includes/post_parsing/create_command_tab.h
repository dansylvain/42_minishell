/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:07:23 by dan               #+#    #+#             */
/*   Updated: 2024/03/14 16:40:29 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_COMMAND_TAB_H
# define CREATE_COMMAND_TAB_H

# include <minishell.h>
# include "parsing_utils.h"
# include <stddef.h>
# include "libft.h"
# include "ft_printf.h"

void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);
void	store_and_free_cmd_tab(char ***cmd_tab);
int		alloc_memory_for_command_tab(t_ast_nde *node, char ****cmd_tab);
void	build_command_tab(char ****cmd_tab, t_Data *data,
			t_ast_nde **cmd_tab_node_sav, char *envp[]);
char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[]);
int		is_pipeline(t_ast_nde *cmd_tab_node_sav);
int		pipex(char **argv[]);
char	***fill_cmd_tab_tabs(t_Data *data, t_ast_nde *node, char ***cmd_tab);
int		command_is_builtin(char	*cmd[], t_Data *data);
void	free_command_tab_lg(char ***command_tab);
int		is_separator(t_ast_nde *node);
int		is_chevron(t_ast_nde *node);
void	display_command_tab_big(char ***command_tab);
void	print_node(t_ast_nde *node);
void	print_tree(t_ast_nde *node);
int		get_pipe_parts_nbr(t_ast_nde **node);
char	***alloc_memory_for_pipe_parts(char ***cmd_tab, int pipe_parts_nbr);
int		get_pipe_elements_nbr(t_ast_nde *node);
char	**alloc_memory_for_pipe_elements(char **cmd_tab, int pipe_elements_nbr);
char	***fill_command_tab(char ***cmd_tab, t_ast_nde *node);
int		is_not_empty_prompt(char *str);
void	display_error_detail(char *str, char *details, char *str2);
char	*get_node_str(t_ast_nde *node);

#endif
