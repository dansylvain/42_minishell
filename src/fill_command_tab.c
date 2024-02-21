/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:25:16 by dan               #+#    #+#             */
/*   Updated: 2024/02/21 12:38:17 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	***fill_cmd_tab_tabs(t_Data *data, t_ast_nde *node, char ***cmd_tab)
{
	char		str[2000];
	int			i;

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
			if (create_separator_tab(data, &node, &cmd_tab, &i))
				continue ;
		else
			break ;
		if (is_separator(node) || (node->sibling && is_chevron(node->sibling)))
			i++;
		node = node->sibling;
	}
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

int	create_separator_tab(t_Data *data, t_ast_nde **node,
	char ****cmd_tab, int *i)
{
	t_ast_nde	*current;
	int			k;
	int			j;

	current = (*node);
	k = 0;
	while (!is_separator(current) && !is_chevron(current))
	{
		k++;
		current = current->sibling;
	}
	(*cmd_tab)[*i] = (char **)ft_calloc(k + 1, sizeof(char *));
	if ((*cmd_tab)[*i] == NULL)
		return (0);
	j = 0;
	while (!is_separator((*node)) && !is_chevron((*node)))
	{
		(*cmd_tab)[*i][j++] = get_node_str(data, (*node)->child);
		(*node) = (*node)->sibling;
	}
	(*cmd_tab)[*i][j] = NULL;
	if (!is_separator((*node)))
		(*i)++;
	return (1);
}
