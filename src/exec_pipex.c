/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:33:40 by dan               #+#    #+#             */
/*   Updated: 2024/03/06 06:23:52 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**========================================================================
 *                           store_and_free_cmd_list
 *========================================================================**/
void	store_and_free_cmd_list(t_ast_nde *cmd_list)
{
	static t_ast_nde	*cmd_list_lcl;

	if (cmd_list)
		cmd_list_lcl = cmd_list;
	else
		free_sibling_and_child(cmd_list_lcl);
}

/**========================================================================
 *                           exec_pipex
 *========================================================================**/
void	exec_pipex(t_Data *data, char *cmd, char *envp[])
{
	t_ast_nde	*cmd_list;
	t_ast_nde	*current;

	cmd_list = parse(cmd, data);
	if (!cmd_list)
		return ;
	store_and_free_cmd_list(cmd_list);
	launch_command_tab(data, cmd_list, envp, 0);
	store_and_free_cmd_list(NULL);
}
