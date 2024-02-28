/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:59:03 by seblin            #+#    #+#             */
/*   Updated: 2024/02/09 13:19:52 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "space.h"

static t_ast_nde	*create_space_node(t_ast_nde *sib)
{
	t_ast_nde	*token_nde;
	char		*actual;

	while (sib)
	{
		actual = sib->start;
		while (sib->token == RAW && actual <= sib->end)
		{
			if (*actual == ' ')
			{
				token_nde = create_node(SPCE);
				token_nde->start = actual;
				token_nde->end = actual;
				while (*++actual == ' ')
					token_nde->end = actual;
				return (token_nde);
			}
			actual++;
		}
		sib = sib->sibling;
	}
	return (NULL);
}

int	set_space(t_ast_nde *node)
{
	t_ast_nde	*sib;
	t_ast_nde	*sib_cont;
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;

	sib_cont = node->child;
	sib = sib_cont->child;
	token = create_space_node(sib);
	sib_cont->sibling = token;
	if (token)
	{
		raw_lft = create_token_child(sib_cont, token);
		raw_rght = raw_lft->sibling;
		token->child = raw_lft;
		fill_child(sib, raw_lft->child, raw_rght->child, token);
		if (raw_lft->child)
			set_dollar(raw_lft);
		if (raw_rght->child)
			set_space(raw_rght);
		return (1);
	}
	set_dollar(node);
	return (0);
}
