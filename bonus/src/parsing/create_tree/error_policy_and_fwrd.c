/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_policy_and_fwrd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:43:52 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 16:28:33 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_policy_and_fwrd.h"

int	*get_err_policy(void)
{
	static int	policy_flags[3] = {0, 1, 0};

	return (policy_flags);
}

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
	int	*policy;

	policy = get_err_policy();
	if (!policy[0])
	{
		if (protected_left(raw_lft, token))
			return (1);
		return (protected_right(raw_rght, token));
	}
	if (policy[0] == 3)
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
	int	*policy;

	policy = get_err_policy();
	if (policy[0] == 1)
	{
		if (raw_lft->child)
			set_space(raw_lft);
		return (protected_right(raw_rght, token));
	}
	if (policy[0] == 2)
	{
		if (protected_left(raw_lft, token))
			return (1);
		if (raw_rght->child)
			return ((set_operator(raw_rght)));
	}
	return (0);
}
