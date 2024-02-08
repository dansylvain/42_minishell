/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_chevron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:59:03 by seblin            #+#    #+#             */
/*   Updated: 2024/02/08 17:02:48 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_utils.h"

t_ast_nde	*set_chevron(t_ast_nde *node)
{
	t_ast_nde *sib;
	t_ast_nde *sib_parent;
	t_ast_nde *token;
	t_ast_nde *raw_lft;
	t_ast_nde *raw_rght;
	
	sib_parent = node->child;
	sib = sib_parent->child;
	
	token = create_token_node(sib);
	sib_parent->sibling = token;
	if (token)
	{
		raw_lft = create_token_child(sib_parent, token);
		token->child = raw_lft;
		raw_rght = raw_lft->sibling;	
		fill_child(sib, raw_lft->child, raw_rght, token);
		set_operator(raw_lft);
	}
	return (sib);
}