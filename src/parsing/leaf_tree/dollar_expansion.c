/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:14:09 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 16:22:50 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dollar_expansion.h"

t_ast_nde	*rebuild_dollar_str_node(char *str, t_tok token)
{
	t_ast_nde	*str_node;

	str_node = NULL;
	if (str)
	{
		if (token == STAT)
			str_node = create_node(STAT);
		else if (token == JOKER)
			str_node = create_node(JOKER);
		else if (token == DOLL)
			str_node = create_node(DOLL);
		else
			str_node = create_node(RAW);
		str_node->start = str;
		str_node->end = str + ft_strlen(str) - 1;
		str_node->child = copy_node(str_node);
	}
	return (str_node);
}

static char	*link_sibling(const t_ast_nde *node)
{
	char	*str;
	char	*node_str;

	str = NULL;
	if (node)
		node = node->child;
	while (node)
	{
		node_str = ft_strndup(node->start, node->end - node->start + 1);
		if (str && node_str)
			str = ft_strjoin_up(str, node_str, 1, 1);
		else
			str = node_str;
		node = node->sibling;
	}
	return (str);
}

static void	merge_str_and_sibling(char **str, const t_ast_nde *sibling)
{
	char	*new_str;

	new_str = NULL;
	if (sibling && str)
	{
		new_str = link_sibling(sibling);
		if (new_str)
		{
			if (*str)
				*str = ft_strjoin_up(*str, new_str, 1, 1);
			else if (!*str)
				*str = new_str;
		}
	}
}

static void	build_token_and_merge(const t_ast_nde *operator,
		char **str, t_Data *data)
{
	char	*str_tok;

	str_tok = NULL;
	if (operator)
	{
		if (operator->token == DOLL)
			str_tok = search_var(operator, data);
		else if (operator->token == JOKER)
			str_tok = wildcard_func(ft_strndup(operator->start,
						operator->end - operator->start + 1));
		if (str_tok)
		{
			if (str && *str)
				*str = ft_strjoin_up(*str, str_tok, 1, 1);
			else if (str)
				*str = str_tok;
		}
	}
}

char	*rebuild_dollar_str(t_ast_nde *operator, char *str, t_Data *data)
{
	t_ast_nde	*sibling_lft;
	t_ast_nde	*sibling_rght;
	t_ast_nde	*next_operator;

	sibling_lft = NULL;
	sibling_rght = NULL;
	next_operator = NULL;
	if (operator && operator->child)
	{
		if (operator->child->child)
			sibling_lft = operator->child->child;
		if (operator->child->sibling && operator->child->sibling->child)
		{
			sibling_rght = operator->child->sibling->child;
			if (operator->child->sibling->child->sibling)
				next_operator = operator->child->sibling->child->sibling;
		}
	}
	merge_str_and_sibling(&str, sibling_lft);
	build_token_and_merge(operator, &str, data);
	if (next_operator)
		str = rebuild_dollar_str(next_operator, str, data);
	else
		merge_str_and_sibling(&str, sibling_rght);
	return (str);
}
