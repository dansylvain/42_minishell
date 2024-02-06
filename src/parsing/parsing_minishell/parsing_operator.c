/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:29:44 by svidot            #+#    #+#             */
/*   Updated: 2024/02/06 16:14:09 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_utils.h"

static t_ast_nde	*create_pipe(char *start, char *end, char *pipe)
{	
	t_ast_nde	*raw_lft; 
	t_ast_nde	*raw_rght;
	t_ast_nde	*pipe_nde;

	raw_lft = create_node(RAW);
	raw_lft->start = start;
	raw_lft->end = pipe - 1;
	raw_rght = create_node(RAW);
	raw_rght->start = pipe + 1;
	raw_rght->end = end;	
	pipe_nde = create_node(PIPE);
	pipe_nde->start = pipe;
	pipe_nde->end = pipe;
	raw_lft->sibling = raw_rght;
	pipe_nde->child = raw_lft;	
	return (pipe_nde);
}
static char	*create_token_node(t_ast_nde *sib, t_tok token)
{
	t_ast_nde	*token_nde;
	char		*actual;
	
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
			}
			else if (*(actual - 1) != '\\' && *actual == '&'
				&& *(actual + 1) == '&')
			{
				token_nde = create_node(AND);
				token_nde->start = actual;
				token_nde->end = ++actual;
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
	char 	*start;
	char 	*end;
	char	*token;
	
	sib = node->child;
	start = node->start;
	end = node->end;	
	token = search_pipe(sib);    
	if (pipe)
	{
		//error_detector(pipe, start, end);
		sib->child = create_pipe(start, end, pipe);
		fill_child(sib);
		set_pipe(sib->child->child);		
	}
	return (sib);
}