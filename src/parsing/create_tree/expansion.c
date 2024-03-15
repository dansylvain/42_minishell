/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 07:42:44 by seblin            #+#    #+#             */
/*   Updated: 2024/03/15 12:08:11 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static t_ast_nde	*search_token_joker(t_ast_nde *sib, char *actual)
{
	t_ast_nde	*token_nde;

	token_nde = NULL;
	while (actual <= sib->end)
	{
		if (token_nde)
			token_nde->end = actual;
		actual++;
	}
	return (token_nde);
}

static t_ast_nde	*search_token_dollar(t_ast_nde *sib, char *actual)
{
	t_ast_nde	*token_nde;

	if ((*actual == '$' && actual + 1 <= sib->end
			&& *(actual + 1) != ' ' && *(actual + 1) != '\''
			&& *(actual + 1) != '*' && *(actual + 1) != '.')
		|| (*actual == '$' && actual == sib->end && sib->sibling
			&& (sib->sibling->token == IN_DQUTE
				|| sib->sibling->token == IN_SQUTE)
		))
	{
		token_nde = create_node(DOLL);
		token_nde->start = actual;
		token_nde->end = actual;
		if (*++actual == '?')
		{
			token_nde->end = actual;
			return (token_nde);
		}
		while (actual <= sib->end && *actual != '$' && *actual != ' '
			&& *actual != '\'' && *actual != '*' && *actual != '?'
			&& *actual != '.')
			token_nde->end = actual++;
		return (token_nde);
	}
	return (NULL);
}

static t_ast_nde	*create_token_node(t_ast_nde *sib)
{
	char		*actual;
	t_ast_nde	*token_nde;

	while (sib)
	{
		actual = sib->start;
		while (actual <= sib->end)
		{
			if (sib->token == IN_DQUTE || sib->token == RAW)
			{
				token_nde = search_token_dollar(sib, actual);
				if (token_nde)
					return (token_nde);
			}
			if (sib->token == RAW)
			{
				token_nde = search_token_joker(sib, actual);
				if (token_nde)
					return (token_nde);
			}
			actual++;
		}
		sib = sib->sibling;
	}
	return (NULL);
}

int	set_dollar(t_ast_nde *node)
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
	{
		raw_lft = create_token_child(sib_cont, token);
		raw_rght = raw_lft->sibling;
		token->child = raw_lft;
		fill_child(sib, raw_lft->child, raw_rght->child, token);
		if (raw_rght->child)
			set_dollar(raw_rght);
		return (1);
	}
	return (0);
}
