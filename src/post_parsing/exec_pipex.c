/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:33:40 by dan               #+#    #+#             */
/*   Updated: 2024/03/12 14:59:17 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_pipex.h"

#include <test.h>
t_Data	*get_data(char *envp[]);
/**========================================================================
 *                           exec_pipex
 *========================================================================**/
int	exec_pipex(t_Data *data, char *cmd, char *envp[], int reset)
{
	t_ast_nde	*cmd_list;
	static int	or_flag;

	//ft_printf("cmd: %s\n", cmd);
	if (reset)
	{
		or_flag = 0;
		return (0);
	}
	
	//printf("orflag: %i\n", or_flag);
	cmd_list = NULL;
	cmd_list = parse(cmd, data);
	if (!cmd_list)
		return (0) ;
	store_and_free_cmd_list(cmd_list);
	or_flag = launch_command_tab(data, cmd_list, envp, or_flag);
	//get_data(NULL)->exit_status = or_flag;
	store_and_free_cmd_list(NULL);
	return (or_flag);
}

/**========================================================================
 *                           store_and_free_cmd_list
 *========================================================================**/
void	store_and_free_cmd_list(t_ast_nde *cmd_list)
{
	static t_ast_nde	*cmd_list_lcl;

	if (cmd_list)
		cmd_list_lcl = cmd_list;
	else
	{
		free_sibling_and_child(cmd_list_lcl);
		cmd_list_lcl = NULL;	
	}
}
