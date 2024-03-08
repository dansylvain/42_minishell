/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:38:25 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 20:41:23 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_command_tab.h"

//error management to be added here...
int	cmd_tab_error_check(t_ast_nde *node)
{
	return (1);
}

void	create_dollar_tab(t_Data *data,
		t_ast_nde **node, char ****cmd_tab, int *i)
{
	int		j;
	char	*env_var;
	int		len;

	env_var = get_node_str(data, (*node)->child);
	len = ft_strlen(env_var);
	j = 0;
	while ((*cmd_tab)[*i][j] && (*cmd_tab)[*i][j][0])
		j++;
	ft_memcpy((*cmd_tab)[*i][j], env_var, len + 1);
	(*cmd_tab)[*i][j + 1] = NULL;
}

char	***fill_cmd_tab_tabs(t_Data *data, t_ast_nde *node, char ***cmd_tab)
{
	t_ast_nde	*current;
	int			i;
	int			j;

	current = node;
	while (current)
	{
		if (cmd_tab_error_check(node) == 0)
		{
			ft_printf("ERROR!!!\n");
		}
		current = current->sibling;
	}
	i = 0;
	current = node;
	while (current && node)
	{
		while (!is_separator(current))
		{
			if (is_chevron(current))
			{
				create_chev_tab(&cmd_tab, &current, &i);
				if (current && is_separator(current->sibling->sibling)
					&& current->sibling->child->sibling)
				{
					complete_raw_tab(data, &cmd_tab, current->sibling, &i);
				}
			}
			current = current->sibling;
		}
		while (node && !is_separator(node))
		{
			if (is_raw(node))
				add_raw_to_cmd_tab(data, &cmd_tab, node, &i);
			else if (node->child->token == DOLL)
				create_dollar_tab(data, &node, &cmd_tab, &i);
			node = node->sibling;
		}
		if (node && node->token == PIPE)
		{
			add_pipe_tab_to_tab(&cmd_tab, &i);
			node = node->sibling;
		}
		if (current && current->sibling)
			current = current->sibling;
	}
	j = 0;
	while ((cmd_tab)[i][j] && (cmd_tab)[i][j][0])
		j++;
	(cmd_tab)[i][j] = NULL;
	cmd_tab[i + 1] = NULL;
	return (cmd_tab);
}

/* 
while (!is_separator((*node)) && !is_chevron((*node)))
{
	if ((*node)->token == JOKER)
	{
		tab = ft_split((*node)->start, ' ');
		k = 0;
		while (tab[k])
		{
			(*cmd_tab)[*i][j++] = ft_strdup(tab[k]);
			free(tab[k]);
			k++;
		}
		(*cmd_tab)[*i][j] = NULL;
		if ((*node)->start)
		{
			free((*node)->start);
		}
		free(tab);
	}
	else if ((*node)->token == DOLL)
	{
		(*cmd_tab)[*i][j++] = get_node_str(data, (*node)->child);
		if ((*node)->start)
			free((*node)->start);
	}
	else
		(*cmd_tab)[*i][j++] = get_node_str(data, (*node)->child);
	(*node) = (*node)->sibling;
} */