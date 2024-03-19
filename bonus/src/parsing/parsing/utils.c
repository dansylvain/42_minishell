/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:37:11 by svidot            #+#    #+#             */
/*   Updated: 2024/03/17 17:35:33 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_ast_nde	*create_node(t_tok token)
{
	t_ast_nde	*new_node;

	new_node = (t_ast_nde *) ft_calloc(1, sizeof(t_ast_nde));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	return (new_node);
}

void	add_sibling(t_ast_nde *node, t_ast_nde **sibling,
					t_ast_nde **sibling_sav)
{
	if (node)
	{
		if (!*sibling_sav)
		{
			*sibling = node;
			*sibling_sav = *sibling;
		}
		else
		{
			(*sibling)->sibling = node;
			*sibling = (*sibling)->sibling;
		}
	}
}

t_ast_nde	*copy_node(t_ast_nde *node)
{
	t_ast_nde	*new_node;

	new_node = NULL;
	if (node)
	{
		new_node = create_node(node->token);
		if (!new_node)
			return (NULL);
		new_node->start = node->start;
		new_node->end = node->end;
	}
	return (new_node);
}

t_ast_nde	*copy_node_child(t_ast_nde *node)
{
	t_ast_nde	*new_node;

	new_node = NULL;
	if (node)
	{
		new_node = create_node(node->token);
		if (!new_node)
			return (NULL);
		new_node->start = node->start;
		new_node->end = node->end;
		new_node->child = node->child;
	}
	return (new_node);
}

t_ast_nde	*copy_node_and_child(t_ast_nde *node)
{
	t_ast_nde	*child;
	t_ast_nde	*new_node;
	t_ast_nde	*new_sibling;
	t_ast_nde	*new_sibling_sav;

	new_sibling_sav = NULL;
	new_node = NULL;
	if (node)
	{
		child = node->child;
		while (child)
		{
			new_node = copy_node(child);
			add_sibling(new_node, &new_sibling, &new_sibling_sav);
			child = child->sibling;
		}
		new_node = copy_node(node);
		new_node->child = new_sibling_sav;
	}
	return (new_node);
}
