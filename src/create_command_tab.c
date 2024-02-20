/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/02/20 19:10:51 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			add_sibling(copy_sibling(node), &cmd_tab_node, &cmd_tab_node_sav);
		node = node->sibling;
	}
	if (cmd_tab_node_sav)
		build_command_tab(&cmd_tab, data, &cmd_tab_node_sav, envp);
	flag = data->exit_status;
	if (node && node->token == OR)
		flag = !flag;
	if (node)
		launch_command_tab(data, node->sibling, envp, flag);
}

void	build_command_tab(char ****cmd_tab, t_Data *data,
		t_ast_nde **cmd_tab_node_sav, char *envp[])
{
	(*cmd_tab) = create_command_tab(data, (*cmd_tab_node_sav), envp);
	if (is_pipeline((*cmd_tab_node_sav)))
		data->exit_status = pipex((*cmd_tab), envp);
	else if (!command_is_builtin(*(*cmd_tab), data, envp))
		data->exit_status = pipex((*cmd_tab), envp);
	free_sibling_and_child((*cmd_tab_node_sav));
	free_command_tab_lg((*cmd_tab));
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
	cmd_tab[cmd_nbr] = NULL;
	cmd_tab = fill_cmd_tab_tabs(data, node, cmd_tab);
	return (cmd_tab);
}

int	create_chevron_tab(char ****cmd_tab, int *i, t_ast_nde **node, t_Data *data)
{
	(*cmd_tab)[*i] = (char **)malloc(sizeof(char *) * 3);
	if ((*cmd_tab)[*i] == NULL)
		return (0);
	(*cmd_tab)[*i][0] = ft_strndup((*node)->start,
			(*node)->end - (*node)->start + 1);
	(*cmd_tab)[*i][1] = get_node_str(data, (*node)->sibling->child);
	(*cmd_tab)[*i][2] = NULL;
	if ((*node)->sibling->sibling)
		(*node) = (*node)->sibling->sibling;
	else
		return (0);
	if (!is_separator((*node)))
		(*i)++;
	return (1);
}

char	***fill_cmd_tab_tabs(t_Data *data, t_ast_nde *node, char ***cmd_tab)
{
	char		str[2000];
	int			i;
	t_ast_nde	*current;
	int			j;
	int			k;

	i = 0;
	while (node)
	{
		if (!node)
			break ;
		if (is_chevron(node))
			if (create_chevron_tab(&cmd_tab, &i, &node, data))
				continue ;
			else
				break ;
		if (!is_separator(node) && node->token != DOLL)
		{
			current = node;
			k = 0;
			while (!is_separator(current) && !is_chevron(current))
			{
				k++;
				current = current->sibling;
			}
			cmd_tab[i] = (char **)ft_calloc(k + 1, sizeof(char *));
			if (cmd_tab[i] == NULL)
				return (NULL);
			j = 0;
			while (!is_separator(node) && !is_chevron(node))
			{
				cmd_tab[i][j++] = get_node_str(data, node->child);
				node = node->sibling;
			}
			cmd_tab[i][j] = NULL;
			if (!is_separator(node))
				i++;
			continue ;
		}
		if (is_separator(node) || (node->sibling && is_chevron(node->sibling)))
			i++;
		node = node->sibling;
	}
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
		if ((node->token == PIPE))
			cmd_nbr++;
		node = node->sibling;
	}
	return (cmd_nbr);
}
