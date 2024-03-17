/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_policy_and_fwrd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:43:52 by seblin            #+#    #+#             */
/*   Updated: 2024/03/17 18:20:24 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_policy_and_fwrd.h"

extern int	p_flag;

static int	protected_left(t_ast_nde *raw_lft, t_ast_nde *token)
{
	if (raw_lft && raw_lft->child && raw_lft->child->child
		&& !is_sibling_only_space(raw_lft->child->child))
		set_space(raw_lft);
	else if (token && (token->token == AND || token->token == OR
			|| token->token == PIPE))
		return (display_error_free(ft_strjoin("minishell: syntax error near \
unexpected token ", translate_enum(token->token))), 1);
	return (0);
}

static int	protected_right(t_ast_nde *raw_rght, t_ast_nde *token)
{
	if (raw_rght->child && raw_rght->child->child
		&& !is_sibling_only_space(raw_rght->child->child))
		return ((set_operator(raw_rght)));
	else if ((token->token == AND || token->token == OR || token->token == PIPE
			|| is_chevron(token)))
		return (display_error_free(ft_strjoin("minishell: syntax error near \
unexpected token ", translate_enum(token->token))), 1);
	return (0);
}

int	error_policy_and_forwarding(t_ast_nde *raw_lft, t_ast_nde *raw_rght,
	t_ast_nde *token)
{
	if (!p_flag)
	{
		if (protected_left(raw_lft, token))
			return (1);
		return (protected_right(raw_rght, token));
	}
	if (p_flag == 3)
	{
		if (raw_lft->child)
			set_space(raw_lft);
		if (raw_rght->child)
			return ((set_operator(raw_rght)));
	}
	return (0);
}

int	error_policy_and_forwarding_2(t_ast_nde *raw_lft, t_ast_nde *raw_rght,
	t_ast_nde *token)
{
	if (p_flag == 1)
	{
		if (raw_lft->child)
			set_space(raw_lft);
		return (protected_right(raw_rght, token));
	}
	if (p_flag == 2)
	{
		if (protected_left(raw_lft, token))
			return (1);
		if (raw_rght->child)
			return ((set_operator(raw_rght)));
	}
	return (0);
}
