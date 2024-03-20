/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/15 12:13:00 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launch_command_tab.h"

/**========================================================================
 *                           launch_command_tab
 *========================================================================**/
void	launch_command_tab(t_Data *data, t_ast_nde *node,
		char *envp[], int flag)
{
	t_ast_nde	*cmd_tab_node;
	t_ast_nde	*cmd_tab_node_sav;
	char		***cmd_tab;

	cmd_tab_node_sav = NULL;
	while (node && node->token != AND && node->token != OR)
	{
		if (!flag)
			add_sibling(copy_node_and_child(node), &cmd_tab_node,
				&cmd_tab_node_sav);
		node = node->sibling;
	}
	store_and_free_cmd_tab_node_sav(cmd_tab_node_sav);
	if (node && (node->token == AND || node->token == OR))
	{
		display_error("minishell: && and || operators not supported\n");
		data->exit_status = 1;
		return (store_and_free_cmd_tab_node_sav(NULL));
	}
	if (cmd_tab_node_sav)
		build_command_tab(&cmd_tab, data, &cmd_tab_node_sav, envp);
	flag = data->exit_status;
	if (node)
		launch_command_tab(data, node->sibling, envp, flag);
}

/**========================================================================
 *                           store_and_free_cmd_tab_node_sav
 *========================================================================**/
void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav)
{
	static t_ast_nde	*cmd_tab_lcl;

	if (cmd_tab_node_sav)
		cmd_tab_lcl = cmd_tab_node_sav;
	else
		free_sibling_and_child(cmd_tab_lcl);
}

/**========================================================================
 *                           build_command_tab
 *========================================================================**/
void	build_command_tab(char ****cmd_tab, t_Data *data,
		t_ast_nde **cmd_tab_node_sav, char *envp[])
{
	(*cmd_tab) = create_command_tab(data, (*cmd_tab_node_sav), envp);
	store_and_free_cmd_tab(*cmd_tab);
	if (is_pipeline(*cmd_tab_node_sav))
	{
		free_sibling_and_child(*cmd_tab_node_sav);
		data->exit_status = pipex(*cmd_tab);
	}
	else if (!command_is_builtin(*(*cmd_tab), data))
	{
		free_sibling_and_child(*cmd_tab_node_sav);
		data->exit_status = pipex(*cmd_tab);
	}
	else
	{
		free_sibling_and_child(*cmd_tab_node_sav);
	}
	free_command_tab_lg(*cmd_tab);
}

/**========================================================================
 *                           is_pipeline
 *========================================================================**/
int	is_pipeline(t_ast_nde *cmd_tab_node_sav)
{
	while (cmd_tab_node_sav)
	{
		if (cmd_tab_node_sav->token == PIPE || is_chevron(cmd_tab_node_sav))
			return (1);
		cmd_tab_node_sav = cmd_tab_node_sav->sibling;
	}
	return (0);
}
