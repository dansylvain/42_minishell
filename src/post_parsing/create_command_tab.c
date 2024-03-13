/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/13 07:16:21 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_command_tab.h"

/**========================================================================
 *                           store_and_free_cmd_tab
 *========================================================================**/
void	store_and_free_cmd_tab(char ***cmd_tab)
{
	static char	***cmd_tab_lcl;

	if (cmd_tab)
		cmd_tab_lcl = cmd_tab;
	else
		free_command_tab_lg(cmd_tab_lcl);
}

/**========================================================================
 *                           create_command_tab
 *========================================================================**/
char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
{
	char	***cmd_tab;
	int		pipe_parts_nbr;

	pipe_parts_nbr = get_pipe_parts_nbr(&node);
	cmd_tab = alloc_memory_for_pipe_parts(cmd_tab, pipe_parts_nbr);
	alloc_memory_for_tab_tabs(cmd_tab, node);
	return (cmd_tab);
}
