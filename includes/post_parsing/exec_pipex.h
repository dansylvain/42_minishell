/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:03:33 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPEX_H
# define EXEC_PIPEX_H

# include <minishell.h>
# include "parsing_utils.h"
# include <stddef.h>

void		exec_pipex(t_Data *data, char *cmd, char *envp[]);
void		store_and_free_cmd_list(t_ast_nde *cmd_list);
t_ast_nde	*parse(char *str, t_Data *data);
void		launch_command_tab(t_Data *data, t_ast_nde *node,
				char *envp[], int flag);
void		build_command_tab(char ****cmd_tab, t_Data *data,
				t_ast_nde **cmd_tab_node_sav, char *envp[]);

#endif
