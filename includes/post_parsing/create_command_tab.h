/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:07:23 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:07:34 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_COMMAND_TAB_H
# define CREATE_COMMAND_TAB_H

# include <minishell_struct.h>
# include "parsing_utils.h"
# include <stddef.h>

void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);;
void	store_and_free_cmd_tab(char ***cmd_tab);;
void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);
void	store_and_free_cmd_tab(char ***cmd_tab);
int		alloc_memory_for_command_tab(t_ast_nde *node, char ****cmd_tab);
void	build_command_tab(char ****cmd_tab, t_Data *data,
			t_ast_nde **cmd_tab_node_sav, char *envp[]);

#endif
