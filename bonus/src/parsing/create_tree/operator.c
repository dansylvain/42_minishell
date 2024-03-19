/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:29:44 by svidot            #+#    #+#             */
/*   Updated: 2024/03/19 13:08:18 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

static t_ast_nde	*create_token(t_tok simpl_tok, t_tok doubl_tok,
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

static t_ast_nde	*search_token(char *actual)
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

static int	token_child_handle(t_ast_nde *sib_cont,
	t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token)
{
	t_ast_nde	*sib;

	sib = sib_cont->child;
	raw_lft = create_token_child(sib_cont, token);
	raw_rght = raw_lft->sibling;
	token->child = raw_lft;
	fill_child(sib, raw_lft->child, raw_rght->child, token);
	if (error_policy_and_forwarding(raw_lft, raw_rght, token)
		|| error_policy_and_forwarding_2(raw_lft, raw_rght, token))
		return (1);
	return (0);
}

int	set_operator(t_ast_nde *node)
{
	t_ast_nde	*sib;
	t_ast_nde	*sib_cont;
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;

	raw_lft = NULL;
	raw_rght = NULL;
	sib_cont = node->child;
	sib = sib_cont->child;
	token = create_token_node(sib);
	sib_cont->sibling = token;
	if (token)
		return (token_child_handle(sib_cont, raw_lft, raw_rght, token));
	set_space(node);
	return (0);
}
