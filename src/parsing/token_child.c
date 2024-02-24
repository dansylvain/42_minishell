/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:37:22 by seblin            #+#    #+#             */
/*   Updated: 2024/02/24 17:37:59 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include <stdlib.h>

int	fill_child_entire(t_ast_nde *sib, t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token, t_ast_nde **raw_lft_child_sav, t_ast_nde **raw_rght_child_sav)
{
	if 	(sib->end < token->start)
		add_sibling(copy_node(sib), &raw_lft->child, raw_lft_child_sav);				
	else if (sib->start > token->end)
		add_sibling(copy_node(sib), &raw_rght->child, raw_rght_child_sav);
	else
		return (0);
	return (1);
}

void	fill_child_overlap(t_ast_nde *sib, t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token, t_ast_nde **raw_lft_child_sav, t_ast_nde **raw_rght_child_sav)
{
	t_ast_nde	*raw_overlap;
	
	if (sib->start <= token->start && sib->end >= token->end)
	{
		if (sib->start < token->start)
		{
			raw_overlap = copy_node(sib);
			raw_overlap->end = token->start - 1;
			add_sibling(raw_overlap, &raw_lft->child, raw_lft_child_sav);					
		}
		if (sib->end > token->end)
		{					
			raw_overlap = copy_node(sib);
			raw_overlap->start = token->end + 1;
			add_sibling(raw_overlap, &raw_rght->child, raw_rght_child_sav);
		}
	}
}

void	fill_child(t_ast_nde *sib, t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token)
{
	t_ast_nde	*raw_lft_child_sav;
	t_ast_nde	*raw_rght_child_sav;

	raw_lft_child_sav = NULL;
	raw_rght_child_sav = NULL;	
	while (sib)
	{		
		if (fill_child_entire(sib, raw_lft, raw_rght, token, &raw_lft_child_sav, &raw_rght_child_sav))
			;		
		else		
			fill_child_overlap(sib, raw_lft, raw_rght, token, &raw_lft_child_sav, &raw_rght_child_sav);	
		sib = sib->sibling;
	}
	if (raw_lft)
		raw_lft->child = raw_lft_child_sav;
	if (raw_rght)
		raw_rght->child = raw_rght_child_sav;	
}

t_ast_nde	*create_token_child(t_ast_nde *raw, t_ast_nde *token)
{		
	t_ast_nde	*raw_lft; 
	t_ast_nde	*raw_rght;
		
	raw_lft = create_node(RAW);
	raw_lft->start = raw->start;
	raw_lft->end = token->start - 1;
	if (raw->start != token->start)
		raw_lft->child = copy_node(raw_lft);	
	raw_rght = create_node(RAW);
	raw_rght->start = token->end + 1;
	raw_rght->end = raw->end;
	if (raw->end != token->end)
		raw_rght->child = copy_node(raw_rght);
	raw_lft->sibling = raw_rght;
	return (raw_lft);
}
