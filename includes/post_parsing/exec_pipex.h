/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:03:33 by dan               #+#    #+#             */
/*   Updated: 2024/03/16 10:41:39 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPEX_H
# define EXEC_PIPEX_H

# include <minishell.h>
# include "parsing_utils.h"
# include <stddef.h>

int			exec_pipex(t_Data *data, char *cmd, char *envp[], int reset);
void		store_and_free_cmd_list(t_ast_nde *cmd_list);
t_ast_nde	*parse(char *str, t_Data *data);
int			launch_command_tab(t_Data *data, t_ast_nde *node,
				char *envp[], int flag);
void		build_command_tab(char ****cmd_tab, t_Data *data,
				t_ast_nde **cmd_tab_node_sav, char *envp[]);
t_Data		*get_data(char *envp[]);

#endif
