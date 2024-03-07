/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/07 15:07:21 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast_nde	*copy_node_and_child(t_ast_nde *node);
void		store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);
void		store_and_free_cmd_tab(char ***cmd_tab);

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
	if (cmd_tab_node_sav)
		build_command_tab(&cmd_tab, data, &cmd_tab_node_sav, envp);
	flag = data->exit_status;
	if (node && node->token == OR)
		flag = !flag;
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
	// display_command_tab_big(*cmd_tab);
	store_and_free_cmd_tab(*cmd_tab);
	if (is_pipeline(*cmd_tab_node_sav))
	{ //ft_printf("je suis un putain de pipeline\n");
		free_sibling_and_child(*cmd_tab_node_sav);
		data->exit_status = pipex(*cmd_tab, envp);
	}
	else if (!command_is_builtin(*(*cmd_tab), data, envp))
	{
		free_sibling_and_child(*cmd_tab_node_sav);
		data->exit_status = pipex(*cmd_tab, envp);
	}
	else
	{
		free_sibling_and_child(*cmd_tab_node_sav);
	}
	free_command_tab_lg(*cmd_tab);
}

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

int	alloc_memory_for_command_tab(t_ast_nde *node, char ****cmd_tab)
{
	int lstsize;
	int i;
	int	j;

	lstsize = 0;
	// ft_printf("cmd_nbr: %i\n", cmd_nbr);
	while (node)
	{
		lstsize++;
		node = node->sibling;
	}
	// ft_printf("lst_size: %i\n", lstsize);
	*cmd_tab = (char ***)ft_calloc(lstsize + 1, sizeof (char **));
	if (*cmd_tab == NULL)
		return (0);
	i = 0;
	while (i < lstsize)
	{
		(*cmd_tab)[i] = (char **)ft_calloc(lstsize + 1, sizeof (char *));
		if ((*cmd_tab)[i] == NULL)
			return (0);
		j = 0;
		while (j < lstsize)
		{
			(*cmd_tab)[i][j] = (char *)ft_calloc(100, sizeof (char));
			if ((*cmd_tab)[i][j] == NULL)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/**========================================================================
 *                           create_command_tab
 *========================================================================**/
char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
{
	char		***cmd_tab;
	int			cmd_nbr;
	
	if (alloc_memory_for_command_tab(node, &cmd_tab) == 0)
		free_command_tab_lg(cmd_tab);
	cmd_tab = fill_cmd_tab_tabs(data, node, cmd_tab);
	//display_command_tab_big(cmd_tab);

	return (cmd_tab);
}
