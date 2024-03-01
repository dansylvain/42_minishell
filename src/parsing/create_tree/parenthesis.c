/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:52:11 by seblin            #+#    #+#             */
/*   Updated: 2024/03/01 15:32:39 by seblin           ###   ########.fr       */
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
int	set_parenthesis(t_ast_nde *node);

t_ast_nde	*create_token(t_tok simpl_tok, t_tok doubl_tok,
	char *actual, char char_tok)
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
	else if (*actual == '&' && *(actual + 1) == '&')
	{
		token_nde = create_node(AND);
		token_nde->start = actual;
		token_nde->end = ++actual;
		return (token_nde);
	}
	else if (*actual == '<')
		return (create_token(SCHEV_LFT, DCHEV_LFT, actual, '<'));
	else if (*actual == '>')
		return (create_token(SCHEV_RGTH, DCHEV_RGTH, actual, '>'));
	return (NULL);
}

static t_ast_nde	*create_token_node(t_ast_nde *sib)
{
	t_ast_nde	*token_nde;
	char		*actual;

	while (sib)
	{
		actual = sib->start;
		while (sib->token == RAW && actual <= sib->end)
		{
			token_nde = search_token(actual);
			if (token_nde)
				return (token_nde);
			actual++;
		}
		sib = sib->sibling;
	}
	return (NULL);
}

void	token_child_handle(t_ast_nde *sib_cont,
	t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token)
{
	t_ast_nde	*sib;

	sib = sib_cont->child;
	raw_lft = create_token_child(sib_cont, token);
	raw_rght = raw_lft->sibling;
	token->child = raw_lft;
	fill_child(sib, raw_lft->child, raw_rght->child, token);
	if (raw_lft->child)
		set_operator(raw_lft);
	else
	{
		if (token->token == AND || token->token == OR || token->token == PIPE)
		{
			ft_putstr_fd(translate_enum(token->token), 2);
			ft_putstr_fd("\nsyntax error near unexpected token\n", 2);
		}
	}
	if (raw_rght->child)
		set_parenthesis(raw_rght);
	else
	{
		ft_putstr_fd(translate_enum(token->token), 2);
		ft_putstr_fd("\nsyntax error near unexpected token\n", 2);
	}
}

int	set_parenthesis(t_ast_nde *node)
{
	t_ast_nde	*sib;
	t_ast_nde	*sib_cont;
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;

	sib_cont = node->child;
	sib = sib_cont->child;
	token = create_token_node(sib);
	sib_cont->sibling = token;
	if (token)
		return (token_child_handle(sib_cont, raw_lft, raw_rght, token), 1);
	set_operator(node);
	return (0);
}
