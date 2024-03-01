/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:52:11 by seblin            #+#    #+#             */
/*   Updated: 2024/03/01 23:03:54 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parenthesis.h"
#include <stdlib.h>
#include "parsing_utils.h"
#include "libft.h"

t_ast_nde	*copy_node(t_ast_nde *node);
int			set_space(t_ast_nde *node);
int			set_operator(t_ast_nde *node);
char		*translate_enum(t_tok token);
t_ast_nde	*create_token_child(t_ast_nde *raw, t_ast_nde *token);
void		fill_child(t_ast_nde *sib, t_ast_nde *raw_lft,
				t_ast_nde *raw_rght, t_ast_nde *token);
int			set_parenthesis(t_ast_nde *node);

static t_ast_nde	*search_token(char *actual, int *err)
{
	t_ast_nde	*token_nde;
	static int	count;
	
	token_nde = NULL;
	if (*actual == '(')//!	
	{	
		if (!token_nde)
		{
			*err = 2;
			token_nde = create_node(PRTH);
			token_nde->start = actual;
		}
		count++;
	}
	else if  (*actual == ')') 
	{
		count--;
		if (count < 0)
		{
			*err = 1;//!
		}
		else if (!count)
		{		
			token_nde->end = actual;
			return (token_nde);
		}		
	}
	return (NULL);
}

static t_ast_nde	*create_token_node(t_ast_nde *sib)
{
	t_ast_nde	*token_nde;
	char		*actual;
	int			err;

	err = 0;
	while (sib)
	{
		actual = sib->start;
		while (sib->token == RAW && actual <= sib->end)
		{
			token_nde = search_token(actual, &err);
			if (token_nde)
				return (token_nde);
			if (err == 1)
				return (NULL);//! data status ?
			actual++;
		}
		if (err == 2)
			return (NULL);//! data status ?
		sib = sib->sibling;
	}
	return (NULL);
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

void	token_child_handle(t_ast_nde *sib_cont,
	t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token)
{
	t_ast_nde	*sib;
	
	if (token)
	{			
		sib = sib_cont->child;
		raw_lft = create_token_child(sib_cont, token);
		raw_rght = raw_lft->sibling;
		token->child = raw_lft;
		fill_child(sib, raw_lft->child, raw_rght->child, token);
		if (set_operator(raw_lft))
		{	
			// ft_putstr_fd("\nsyntax error near unexpected token\n", 2);
		}
		if (set_parenthesis(raw_rght))
		{			
			// ft_putstr_fd("\nsyntax error near unexpected token\n", 2);
		}
	}	
}

int	set_parenthesis(t_ast_nde *node)
{
	t_ast_nde	*sib;
	t_ast_nde	*sib_cont;
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;
	
	if (node && node->child && node->child->child)
	{		
		sib_cont = node->child;
		sib = sib_cont->child;
		token = create_token_node(sib);
		sib_cont->sibling = token;
		if (token)
			return (token_child_handle(sib_cont, raw_lft, raw_rght, token), 1);
		set_operator(node);
	}
	else 
		return (1);
	return (0);
}
