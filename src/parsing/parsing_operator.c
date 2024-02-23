/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:29:44 by svidot            #+#    #+#             */
/*   Updated: 2024/02/23 18:29:48 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_utils.h"
#include "libft.h"
#include<stdio.h>
t_ast_nde	*copy_node(t_ast_nde *node);
void	print_raw_rght(t_ast_nde *raw_rght);
int	set_space(t_ast_nde *node);
//t_ast_nde	*copy_node_child(t_ast_nde *node);
//int	set_dollar(t_ast_nde *node);
int	set_operator(t_ast_nde *node);

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
	
	if (fill_child_entire(sib, raw_lft, raw_rght, token, raw_lft_child_sav, raw_rght_child_sav))
		;
	else if (sib->start <= token->start && sib->end >= token->end)
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

static void	fill_child(t_ast_nde *sib, t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token)
{
	t_ast_nde	*raw_lft_child_sav;
	t_ast_nde	*raw_rght_child_sav;

	raw_lft_child_sav = NULL;
	raw_rght_child_sav = NULL;	
	while (sib)
	{		
		if (sib->token != RAW && sib->token != IN_DQUTE)		
			fill_child_entire(sib, raw_lft, raw_rght, token, &raw_lft_child_sav, &raw_rght_child_sav);		
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

t_ast_nde	*create_token(t_tok simpl_tok, t_tok doubl_tok, char *actual, char char_tok)
{
	t_ast_nde	*token_nde;
	
	token_nde = create_node(simpl_tok);
	token_nde->start = actual;
	token_nde->end = actual;
	if (*(actual + 1) == char_tok)
	{	
		token_nde->token = doubl_tok;				
		token_nde->end = ++actual;
	}
	return (token_nde);
}

t_ast_nde	*search_token(char *actual)
{
	t_ast_nde	*token_nde;
	
	if (*actual == '|')				
		return (create_token(PIPE, OR, actual, '|'));				
	else if (*actual == '&'
		&& *(actual + 1) == '&')
	{
		token_nde = create_node(AND);
		token_nde->start = actual;
		token_nde->end = ++actual;
		return (token_nde);
	}			
	else if (*actual == '<')				
		return (create_token(SCHEV_LFT,  DCHEV_LFT, actual, '<'));							
	else if (*actual == '>')
		return (create_token(SCHEV_RGTH,  DCHEV_RGTH, actual, '>'));
	return (NULL);
}

static t_ast_nde	*create_token_node(t_ast_nde *sib)
{
	t_ast_nde	*token_nde;
	char		*actual;
		
	while (sib)
	{
		actual = sib->start;	
		while (actual <= sib->end)
		{	
			if (sib->token == RAW)
			{
				token_nde = search_token(actual);
				if (token_nde)
					return (token_nde);
			}	
			actual++;
		}
		sib = sib->sibling;
	}
	return (NULL);
}

char	*translate_enum(t_tok token)
{
	if (token == AND)
		return "&&";
	else if (token == OR)
		return "||";
	else if (token == PIPE)
		return "|";
	else if (token == SCHEV_LFT)
		return "<";
	else if (token == DCHEV_LFT)
		return "<<";
	else if (token == SCHEV_RGTH)
		return ">";
	else if (token == DCHEV_RGTH)
		return ">>";	
	return (NULL);
}

void	token_child_handle(t_ast_nde *sib, t_ast_nde *sib_cont, t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token)
{
	raw_lft = create_token_child(sib_cont, token);
	raw_rght = raw_lft->sibling;	
	token->child = raw_lft;
	fill_child(sib, raw_lft->child, raw_rght->child, token);
	if (raw_lft->child)			
		set_space(raw_lft);		
	else
	{
		if (token->token == AND || token->token == OR || token->token == PIPE)
		{				
			ft_putstr_fd(translate_enum(token->token), 2);
			ft_putchar_fd('\n', 2);
			ft_putstr_fd("HANDLE this error\n", 2);
		}
	}
	if (raw_rght->child)
		set_operator(raw_rght);
	else
	{
		ft_putstr_fd(translate_enum(token->token), 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd("HANDLE this error HEREDOC\n", 2);	
	}
}

int	set_operator(t_ast_nde *node)
{
	t_ast_nde *sib;
	t_ast_nde *sib_cont;
	t_ast_nde *token;
	t_ast_nde *raw_lft;
	t_ast_nde *raw_rght;
	
	sib_cont = node->child;
	sib = sib_cont->child;	
	token = create_token_node(sib);
	sib_cont->sibling = token;
	if (token)	
		return (token_child_handle(sib, sib_cont, raw_lft, raw_rght, token), 1);	
	set_space(node);
	return (0);
}
