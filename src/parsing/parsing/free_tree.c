/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:59:08 by seblin            #+#    #+#             */
/*   Updated: 2024/02/25 15:28:59 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_utils.h"

void	free_tree(t_ast_nde *operator);

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

void	free_branch(t_ast_nde *raw)
{
	t_ast_nde *cont;
	
	cont = raw->child;
	free(raw);
	if (cont)
		free_sibling(cont->child);
	if (cont && cont->sibling)	
	{
		free_tree(cont->sibling);
		free(cont);
	}
}

void	free_tree(t_ast_nde *operator)
{	
	t_ast_nde *raw_lft;
	t_ast_nde *raw_rght;
	
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
