/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:29:44 by svidot            #+#    #+#             */
/*   Updated: 2024/02/06 18:57:28 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_utils.h"

t_ast_nde	*copy_node(t_ast_nde *node);

#include<stdio.h>
static void	fill_child(t_ast_nde *sib, t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token)
{
	t_ast_nde	*raw_lft_child_sav;
	t_ast_nde	*raw_rght_child_sav;
	t_ast_nde	*raw_overlap;

	raw_lft_child_sav = NULL;
	raw_rght_child_sav = NULL;
	//	printf("bonnet\n");
			//exit(1);
	while (sib)
	{
		//	printf("chapeau\n");
			//exit(1);
		if (sib->token != RAW)
		{
			if 	(sib->end < token->start)
				add_sibling(copy_node(sib), &raw_lft->child, &raw_lft_child_sav);				
			else if (sib->start > token->end)
				add_sibling(copy_node(sib), &raw_rght->child, &raw_rght_child_sav );	
		}
		else
		{
			if 	(sib->end < token->start)
				add_sibling(copy_node(sib), &raw_lft->child, &raw_lft_child_sav);				
			else if (sib->start > token->end)
				add_sibling(copy_node(sib), &raw_rght->child, &raw_rght_child_sav );
			else if (sib->start <= token->start && sib->end >= token->end)
			{
				if (sib->start < token->start)
				{
					raw_overlap = copy_node(sib);
					raw_overlap->end = token->start - 1;
					add_sibling(raw_overlap, &raw_lft->child, &raw_lft_child_sav);					
				}
				if (sib->end > token->end)
				{					
					raw_overlap = copy_node(sib);
					raw_overlap->start = token->end + 1;
					add_sibling(raw_overlap, &raw_rght->child, &raw_rght_child_sav);
				}
			}			
		}		
		sib = sib->sibling;
	}
	raw_lft->child = raw_lft_child_sav;
	raw_rght->child = raw_rght_child_sav;	
}

static t_ast_nde	*create_token_child(t_ast_nde *raw, t_ast_nde *token)
{		
	t_ast_nde	*raw_lft; 
	t_ast_nde	*raw_rght;
	
	raw_lft = create_node(RAW);
	raw_lft->start = raw->start;
	raw_lft->end = token->start - 1;
	raw_rght = create_node(RAW);
	raw_rght->start = token->end + 1;
	raw_rght->end = raw->end;
	raw_lft->sibling = raw_rght;
	return (raw_lft);	
}
static t_ast_nde	*create_token_node(t_ast_nde *sib)
{
	t_ast_nde	*token_nde;
	char		*actual;
	
	token_nde = NULL;
	while (sib)
	{
		actual = sib->start;	
		while (sib->token == RAW && actual <= sib->end)
		{
			if (*(actual - 1) != '\\' && *actual == '<')
			{
				token_nde = create_node(SCHEV_LFT);
				token_nde->start = actual;
				token_nde->end = actual;
				if (*(actual + 1) == '<')
				{	
					token_nde->token = DCHEV_LFT;				
					token_nde->end = ++actual;
				}
				return (token_nde);
			}
			else if (*(actual - 1) != '\\' && *actual == '>')
			{
				token_nde = create_node(SCHEV_RGTH);
				token_nde->start = actual;
				token_nde->end = actual;
				if (*(actual + 1) == '>')
				{	
					token_nde->token = DCHEV_LFT;				
					token_nde->end = ++actual;
				}
				return (token_nde);
			}
			else if (*(actual - 1) != '\\' && *actual == '|')
			{
				token_nde = create_node(PIPE);
				token_nde->start = actual;
				token_nde->end = actual;
				if (*(actual + 1) == '|')
				{	
					token_nde->token = OR;				
					token_nde->end = ++actual;
				}
				return (token_nde);
			}
			else if (*(actual - 1) != '\\' && *actual == '&'
				&& *(actual + 1) == '&')
			{
				token_nde = create_node(AND);
				token_nde->start = actual;
				token_nde->end = ++actual;
				return (token_nde);
			}
			actual++;
		}
		sib = sib->sibling;
	}
	return (token_nde);
}

t_ast_nde	*set_operator(t_ast_nde *node)
{
	t_ast_nde *sib;
	t_ast_nde *sib_parent;
	t_ast_nde *token;
	t_ast_nde *raw_lft;
	t_ast_nde *raw_rght;
	printf("une fois\n");
	sib_parent = node->child;
	sib = sib_parent->child;
	token = create_token_node(sib);
	sib_parent->sibling = token;
	if (token)
	{
		raw_lft = create_token_child(sib_parent, token);
		token->child = raw_lft;
		raw_rght = raw_lft->sibling;
		raw_rght->child = copy_node(raw_rght);
		fill_child(sib, raw_lft, raw_rght, token);
		set_operator(raw_lft->sibling);
	}
	
	// if (pipe)
	// {
	// 	//error_detector(pipe, start, end);
	// 	sib->child = create_pipe(start, end, pipe);
	// 	fill_child(sib);
	// 	set_pipe(sib->child->child);		
	// }
	return (sib);
}
