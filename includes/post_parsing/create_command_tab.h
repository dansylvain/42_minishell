/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:07:23 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:39:15 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_COMMAND_TAB_H
# define CREATE_COMMAND_TAB_H

# include <minishell_struct.h>
# include "parsing_utils.h"
# include <stddef.h>
# include "libft.h"

void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);;
void	store_and_free_cmd_tab(char ***cmd_tab);;
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

#endif
