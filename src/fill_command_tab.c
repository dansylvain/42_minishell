/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:38:25 by seblin            #+#    #+#             */
/*   Updated: 2024/03/07 11:20:41 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	store_and_free_cmd_tab(char ***cmd_tab);

void	add_pipe_tab_to_tab(char ****cmd_tab, int *i)
{
	(*i)++;
	(*cmd_tab)[*i][0][0] = '|';
}

char	***fill_cmd_tab_tabs(t_Data *data, t_ast_nde *node, char ***cmd_tab)
{
	int			i;

	i = 0;
	while (node)
	{
		if (!node)
			break ;
		if (is_chevron(node))
		{
			if (create_chevron_tab(&cmd_tab, &i, &node, data))
				continue ;
			else
				break ;
		}
		if (!is_separator(node))
		{
			if (create_separator_tab(data, &node, &cmd_tab, &i))
				continue ;
			else
				break ;
		}
		if (is_separator(node) || ((node)->sibling
			&& is_chevron((node)->sibling)))
		{
			// ft_printf("add_pipe_tab_to_tab\n");
			add_pipe_tab_to_tab(&cmd_tab, &i);
			(i)++;
		}
		(node) = (node)->sibling;
		// viva_norminette(&node, &i);
	}
	cmd_tab[i + 1] = NULL;
	return (cmd_tab);
}

int	create_chevron_tab(char ****cmd_tab, int *i, t_ast_nde **node, t_Data *data)
{
	(*cmd_tab)[*i][0] = ft_strndup((*node)->start,
			(*node)->end - (*node)->start + 1);
	(*cmd_tab)[*i][1] = get_node_str(data, (*node)->sibling->child);
	(*cmd_tab)[*i][2] = NULL;
	if ((*node)->sibling->sibling)
		(*node) = (*node)->sibling->sibling;
	else
	{
		return (0);
	}
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
	char		**tab;

	current = (*node);
	k = 0;
	while (!is_separator(current) && !is_chevron(current))
	{
		if (current->token)
		{
			j = 0;
			while (current->start[j])
			{
				if (current->start[j] == ' ')
					k++;
				j++;
			}
		}
		k++;
		current = current->sibling;
	}
	// ft_printf("k: %i\n", k);
	j = 0;
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
	}
	(*cmd_tab)[*i][j] = NULL;
	if (!is_separator((*node)))
		(*i)++;
	return (1);
}
