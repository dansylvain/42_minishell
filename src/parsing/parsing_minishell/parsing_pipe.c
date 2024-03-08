/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:40:28 by svidot            #+#    #+#             */
/*   Updated: 2024/02/05 15:32:05 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_utils.h"
#include "ft_printf.h"
#define RAW RAW //

t_ast_nde	*copy_node(t_ast_nde *node);

static char	*search_pipe(const t_ast_nde *sib)
{
	char	*pipe;
	char	*start;

	if (sib)
		start = sib->start;	
	pipe = NULL;
	while (sib)
	{
		while (sib->token == RAW && start <= sib->end)
		{
			if (*(start - 1) != '\\' && *start == '|')
				pipe = start;
			start++;
		}
		sib = sib->sibling;
	}
	return (pipe);
}
static void	error_detector(const char *const pipe, const char *const start, const char *const end)
{
	if (pipe == start)
	{
		ft_printf("pipe left operand missing.\n");
		exit(1);
	}
	if (pipe == end)
	{
		ft_printf("pipe right operand missing.\n");
		exit(1);
	}
}

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

static void	fill_child(t_ast_nde *sib)
{
	const t_ast_nde	*const pipe = sib->child;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;
	t_ast_nde	*raw_lft_child_sav;
	t_ast_nde	*raw_rght_child_sav;
	t_ast_nde	*raw_overlap;
	raw_lft_child_sav = NULL;
	raw_rght_child_sav = NULL;
	raw_lft = pipe->child;
	raw_rght = raw_lft->sibling;
	while (sib)
	{
		if (sib->token == SQUTE || sib->token == IN_SQUTE
 			|| sib->token == DQUTE || sib->token == IN_DQUTE)
		{
			if 	(sib->end < pipe->start)
				add_sibling(copy_node(sib), &raw_lft->child, &raw_lft_child_sav);				
			else if (sib->start > pipe->start)
				add_sibling(copy_node(sib), &raw_rght->child, &raw_rght_child_sav );	
		}
		else
		{
			if 	(sib->end < pipe->start)
				add_sibling(copy_node(sib), &raw_lft->child, &raw_lft_child_sav);				
			else if (sib->start > pipe->start)
				add_sibling(copy_node(sib), &raw_rght->child, &raw_rght_child_sav );
			else if (sib->start <= pipe->start && sib->end >= pipe->start)
			{
				if (sib->start < pipe->start)
				{
					raw_overlap = copy_node(sib);
					raw_overlap->end = pipe->start - 1;
					add_sibling(raw_overlap, &raw_lft->child, &raw_lft_child_sav);					
				}
				if (sib->end > pipe->start)
				{					
					raw_overlap = copy_node(sib);
					raw_overlap->start = pipe->start + 1;
					add_sibling(raw_overlap, &raw_rght->child, &raw_rght_child_sav);
				}
			}			
		}		
		sib = sib->sibling;
	}
	raw_lft->child = raw_lft_child_sav;
	raw_rght->child = raw_rght_child_sav;	
}

t_ast_nde	*set_pipe(t_ast_nde *node)
{
	t_ast_nde *sib = node->child;
	char 	*start;
	char 	*end;
	char	*pipe;
	
	start = node->start;
	end = node->end;	
	pipe = search_pipe(sib);    // gestion des double quotes, simple qute, 	
	if (pipe)
	{
		error_detector(pipe, start, end);
		sib->child = create_pipe(start, end, pipe);
		fill_child(sib);
		set_pipe(sib->child->child);		
	}
	return (sib);
}