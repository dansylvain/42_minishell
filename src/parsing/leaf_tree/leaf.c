/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:01:47 by seblin            #+#    #+#             */
/*   Updated: 2024/03/15 12:06:56 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaf.h"

static void	leaf_raw_lft(t_ast_nde	*raw_lft, t_ast_nde **rslt,
		t_ast_nde **rslt_sav, t_Data *data)
{
	if (raw_lft && raw_lft->child)
	{
		if (raw_lft->child->sibling)
			leaf_tree(raw_lft->child->sibling, rslt, rslt_sav, data);
		else
			add_sibling(copy_node_and_child(raw_lft->child), rslt, rslt_sav);
	}
}

static void	leaf_raw_rght(t_ast_nde	*raw_rght, t_ast_nde **rslt,
		t_ast_nde **rslt_sav, t_Data *data)
{
	t_ast_nde	*next_operator;

	next_operator = NULL;
	if (raw_rght && raw_rght->child)
		next_operator = raw_rght->child->sibling;
	if (next_operator)
		leaf_tree(next_operator, rslt, rslt_sav, data);
	else if (raw_rght && raw_rght->child)
		add_sibling(copy_node_and_child(raw_rght->child), rslt, rslt_sav);
}

void	leaf_tree(t_ast_nde *operator, t_ast_nde **rslt,
		t_ast_nde **rslt_sav, t_Data *data)
{
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;
	t_ast_nde	*tmp_op;

	raw_lft = NULL;
	raw_rght = NULL;
	if (operator)
		raw_lft = operator->child;
	if (raw_lft)
		raw_rght = raw_lft->sibling;
	if (operator && (operator->token == DOLL))
		return (add_sibling(rebuild_dollar_str_node
				(rebuild_dollar_str(operator, NULL, data),
					operator->token), rslt, rslt_sav));
	leaf_raw_lft(raw_lft, rslt, rslt_sav, data);
	if (operator && operator->token != SPCE && operator->token != RAW)
	{
		tmp_op = copy_node(operator);
		tmp_op->child = copy_node(operator);
		add_sibling(tmp_op, rslt, rslt_sav);
	}
	leaf_raw_rght(raw_rght, rslt, rslt_sav, data);
}
