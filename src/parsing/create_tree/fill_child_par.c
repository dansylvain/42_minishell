/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_child_par.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:33:24 by seblin            #+#    #+#             */
/*   Updated: 2024/03/16 12:59:26 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_child_par.h"

static int	fill_child_entire_par(t_ast_nde *sib, t_ast_nde *raw_lft_child,  t_ast_nde *middle_child, t_ast_nde *raw_rght_child, t_ast_nde *token, t_ast_nde **raw_lft_child_sav, t_ast_nde **middle_child_sav, t_ast_nde **raw_rght_child_sav)
{
	if (sib->end < token->start)
		add_sibling(copy_node(sib), &raw_lft_child->child, raw_lft_child_sav);
	else if (sib->start > token->end)
		add_sibling(copy_node(sib), &raw_rght_child->child, raw_rght_child_sav);
	else
		return (0);
	return (1);
}

static void	fill_child_overlap_par(t_ast_nde *sib, t_ast_nde *raw_lft_child, t_ast_nde *middle_child, t_ast_nde *raw_rght_child, t_ast_nde *token, t_ast_nde **raw_lft_child_sav, t_ast_nde **middle_child_sav, t_ast_nde **raw_rght_child_sav)
{
	t_ast_nde	*raw_overlap;

	if (sib->start <= token->start && sib->end >= token->end)
	{
		if (sib->start < token->start)
		{
			raw_overlap = copy_node(sib);
			raw_overlap->end = token->start - 1;
			add_sibling(raw_overlap, &raw_lft_child->child, raw_lft_child_sav);
		}
		if (sib->end > token->end)
		{
			raw_overlap = copy_node(sib);
			raw_overlap->start = token->end + 1;
			add_sibling(raw_overlap, &raw_rght_child->child, raw_rght_child_sav);
		}
		if (sib->start <= token->start && sib->end >= token->end)		
		{	
			raw_overlap = copy_node(sib);			
			raw_overlap->start = token->start + 1;
			raw_overlap->end =  token->end - 1;			
			add_sibling(raw_overlap, &middle_child->child, middle_child_sav);	
		}
	}
}

void	fill_child_par(t_ast_nde *sib, t_ast_nde *raw_lft_child, t_ast_nde *middle_child, t_ast_nde *raw_rght_child,
	t_ast_nde *token)
{
	t_ast_nde	*raw_lft_child_sav;
	t_ast_nde	*middle_child_sav;
	t_ast_nde	*raw_rght_child_sav;

	raw_lft_child_sav = NULL;
	middle_child_sav = NULL;
	raw_rght_child_sav = NULL;
	while (sib)
	{
		if (fill_child_entire_par(sib, raw_lft_child, middle_child, raw_rght_child, token, &raw_lft_child_sav, &middle_child_sav, &raw_rght_child_sav))
			;
		else
			fill_child_overlap_par(sib, raw_lft_child, middle_child, raw_rght_child, token, &raw_lft_child_sav, &middle_child_sav, &raw_rght_child_sav);
		sib = sib->sibling;
	}
	if (raw_lft_child)
		raw_lft_child->child = raw_lft_child_sav;
	if (raw_lft_child && raw_lft_child->sibling)
		raw_lft_child->sibling->child = middle_child_sav;
	if (raw_rght_child)
		raw_rght_child->child = raw_rght_child_sav;
}