/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:59:08 by seblin            #+#    #+#             */
/*   Updated: 2024/03/16 10:20:08 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_tree.h"

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

static void	free_branch(t_ast_nde *raw, void (*rec) (t_ast_nde *nde))
{
	t_ast_nde	*cont;

	cont = raw->child;
	free(raw);
	if (cont)
	{
		free_sibling(cont->child);
		if (cont->sibling)
			rec(cont->sibling);
		free(cont);
	}
}

void	free_tree(t_ast_nde *operator)
{
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;

	raw_lft = NULL;
	raw_rght = NULL;
	if (operator)
	{
		raw_lft = operator->child;
		if (raw_lft)
			raw_rght = raw_lft->sibling;
		free(operator);
	}
	if (raw_lft)
		free_branch(raw_lft, free_tree);
	if (raw_rght)
		free_branch(raw_rght, free_tree);
}

void	free_tree_par(t_ast_nde *operator)
{
	t_ast_nde	*raw_lft;
	t_ast_nde	*middle;
	t_ast_nde	*raw_rght;

	raw_lft = NULL;
	middle = NULL;
	raw_rght = NULL;
	if (operator)
	{
		raw_lft = operator->child;
		if (raw_lft)
			middle = raw_lft->sibling;
		if (middle)
			raw_rght = middle->sibling;
		free(operator);
	}
	if (raw_lft)
		free_branch(raw_lft, free_tree_par);
	if (middle)
		free_branch(middle, free_tree_par);
	if (raw_rght)
		free_branch(raw_rght, free_tree_par);
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
