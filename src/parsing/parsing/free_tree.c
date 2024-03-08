/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:59:08 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 10:42:55 by svidot           ###   ########.fr       */
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

static void	free_branch(t_ast_nde *raw)
{
	t_ast_nde	*cont;

	cont = raw->child;
	free(raw);
	if (cont)
	{
		free_sibling(cont->child);
		if (cont->sibling)
			free_tree(cont->sibling);
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
		free_branch(raw_lft);
	if (raw_rght)
		free_branch(raw_rght);
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
