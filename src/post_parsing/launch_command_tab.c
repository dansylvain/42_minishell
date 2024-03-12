/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/12 09:06:41 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launch_command_tab.h"
#include <test.h>

/**========================================================================
 *                           launch_command_tab
 *========================================================================**/
int	launch_command_tab(t_Data *data, t_ast_nde *node,
		char *envp[], int flag)
{
	t_ast_nde	*cmd_tab_node;
	t_ast_nde	*cmd_tab_node_sav;
	char		***cmd_tab;
	//ft_printf("in flag: %d\n", flag);
	//print_node(node);
	//ft_printf("\n");
	cmd_tab_node_sav = NULL;
	while (node && node->token != AND && node->token != OR)
	{
		if (!flag)
			add_sibling(copy_node_and_child(node), &cmd_tab_node,
				&cmd_tab_node_sav);
		node = node->sibling;
	}
	//store_and_free_cmd_tab_node_sav(cmd_tab_node_sav);
	if (cmd_tab_node_sav)
		build_command_tab(&cmd_tab, data, &cmd_tab_node_sav, envp);
	flag = data->exit_status;
	if (node && node->token == OR)
		flag = !flag;
	// if (node)
	// 	print_node(node);
//	ft_printf("\n");
//	ft_printf("af flag: %d\n", flag);
	if (node && node->sibling)
		flag = launch_command_tab(data, node->sibling, envp, flag);
	return (flag);
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
