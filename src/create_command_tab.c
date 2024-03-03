/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/03 14:38:12 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_ast_nde *copy_node_and_child(t_ast_nde *node);
void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);
void	store_and_free_cmd_tab(char ***cmd_tab);

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
			add_sibling(copy_node_and_child(node), &cmd_tab_node, &cmd_tab_node_sav);
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

void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav)
{
	static t_ast_nde	*cmd_tab_lcl;
	
	if (cmd_tab_node_sav)
		cmd_tab_lcl = cmd_tab_node_sav;
	else
		free_sibling_and_child(cmd_tab_lcl);
}

void	build_command_tab(char ****cmd_tab, t_Data *data,
		t_ast_nde **cmd_tab_node_sav, char *envp[])
{
	(*cmd_tab) = create_command_tab(data, (*cmd_tab_node_sav), envp);
	if (is_pipeline(*cmd_tab_node_sav))
	{
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

void	store_and_free_cmd_tab(char ***cmd_tab)
{
	static char	***cmd_tab_lcl;
	
	if (cmd_tab)
		cmd_tab_lcl = cmd_tab;
	else
		free_command_tab_lg(cmd_tab_lcl);
}

char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
{
	char		***cmd_tab;
	int			cmd_nbr;
	t_ast_nde	*current;

	current = node;
	while (current)
		current = current->sibling;
	cmd_nbr = get_cmd_nbr(node);
	cmd_tab = (char ***)ft_calloc(cmd_nbr + 1, sizeof (char **));
	if (cmd_tab == NULL)
		return (NULL);
	store_and_free_cmd_tab(cmd_tab);
	cmd_tab[cmd_nbr] = NULL;
	cmd_tab = fill_cmd_tab_tabs(data, node, cmd_tab);
	return (cmd_tab);
}

int	get_cmd_nbr(t_ast_nde *node)
{
	int	cmd_nbr;

	cmd_nbr = 1;
	while (node)
	{
		if (is_chevron(node))
		{
			cmd_nbr++;
			if (!node->sibling || is_separator(node->sibling)
				|| is_chevron(node->sibling))
			{
				ft_printf("handle this error\n");
				
			}
			if (node->sibling->sibling)
				node = node->sibling->sibling;
			else
				break ;
			continue ;
		}
		if (node->token == PIPE)
			cmd_nbr++;
		node = node->sibling;
	}
	return (cmd_nbr);
}
