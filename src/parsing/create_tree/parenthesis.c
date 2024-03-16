/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:52:11 by seblin            #+#    #+#             */
/*   Updated: 2024/03/16 13:05:59 by seblin           ###   ########.fr       */
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
void	print_cmd(t_ast_nde *cmd);
void print_sibling(t_ast_nde *sib);
void	print_node_and_childs(t_ast_nde *sib);
void	print_node(t_ast_nde *sib);
void	print_raw(t_ast_nde *raw);

#include "ft_printf.h"
void	fill_child_par(t_ast_nde *sib, t_ast_nde *raw_lft_child, t_ast_nde *middle_child, t_ast_nde *raw_rght_child,
	t_ast_nde *token);
int	create_token_node(t_ast_nde *sib, t_ast_nde **token_nde);

static t_ast_nde	*create_token_child_par(t_ast_nde *cont_sib, t_ast_nde *token)
{
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;

	raw_lft = create_node(RAW);
	raw_lft->start = cont_sib->start;
	raw_lft->end = token->start - 1;
	if (cont_sib->start != token->start)
		raw_lft->child = copy_node(raw_lft);	
	raw_rght = create_node(RAW);
	raw_rght->start = token->end + 1;
	raw_rght->end = cont_sib->end;
	if (cont_sib->end != token->end)
		raw_rght->child = copy_node(raw_rght);
	raw_lft->sibling = copy_node(token);
	raw_lft->sibling->child = copy_node(token);
	raw_lft->sibling->sibling = raw_rght;	
	return (raw_lft);
}

int	token_child_handle(t_ast_nde *sib_cont,
	t_ast_nde *raw_lft, t_ast_nde *token)
{
	t_ast_nde	*sib;
	t_ast_nde 	*raw_rght;
	
	if (token)
	{			
		sib = sib_cont->child;		
		raw_lft = create_token_child_par(sib_cont, token);		
		raw_rght = raw_lft->sibling->sibling;
		token->child = raw_lft;		
		fill_child_par(sib, raw_lft->child, raw_lft->sibling->child, raw_rght->child, token);	
		return (set_parenthesis(raw_rght));		
	}	
}

int	set_parenthesis(t_ast_nde *node)
{
	t_ast_nde	*sib;
	t_ast_nde	*cont_sib;
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	int			is_token;

	token = NULL;
	if (node && node->child && node->child->child)
	{		
		cont_sib = node->child;
		sib = cont_sib->child;	
		is_token = create_token_node(sib, &token);
		if (is_token < 0)	
			return (-1);		
	
		cont_sib->sibling = token;
		if (token)
			return (token_child_handle(cont_sib, raw_lft, token));	
	}
	else 
		return (1);
	return (0);
}
