/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:29:44 by svidot            #+#    #+#             */
/*   Updated: 2024/02/06 11:52:55 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_utils.h"
#define RAW NONE 

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
					token_nde->end = *(++actual);
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
					token_nde->end = *(++actual);
				}
			}
			else if (*(actual - 1) != '\\' && *actual == '|')
			{
				token_nde = create_node(PIPE);
			}
			actual++;
		}
		sib = sib->sibling;
	}
	return (token_nde);
}

t_ast_nde	*set_operator(t_ast_nde *node)
{
	t_ast_nde *sib = node->child;
	char 	*start;
	char 	*end;
	char	*token;
	
	start = node->start;
	end = node->end;	
	token = search_pipe(sib);    
	if (pipe)
	{
		error_detector(pipe, start, end);
		sib->child = create_pipe(start, end, pipe);
		fill_child(sib);
		set_pipe(sib->child->child);		
	}
	return (sib);
}