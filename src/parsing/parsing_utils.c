/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:37:11 by svidot            #+#    #+#             */
/*   Updated: 2024/02/19 22:33:31 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include <stdlib.h>
#include "libft.h"

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

t_ast_nde	*sib_last(t_ast_nde *sib)
{	
	while (sib && sib->sibling)		
		sib = sib->sibling; 
	return (sib);
}

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

void	free_sibling_and_child(t_ast_nde *sib)
{
	t_ast_nde	*tmp;
	
	while (sib)
	{
		free_sibling(sib->child);
		tmp = sib->sibling;
		free(sib);
		sib = tmp;
	}
}

void	free_sibling(t_ast_nde *sib)
{
	t_ast_nde	*tmp;

	while (sib)
	{
		tmp = sib->sibling;
		free(sib);
		sib = tmp;
	}
}

void	free_ptr_arr(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}