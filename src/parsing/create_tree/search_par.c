/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_par.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:39:15 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 17:59:45 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "search_par.h"

static int	reset_par(int reset, int free_flag, int *count,
	t_ast_nde **token_nde)
{
	if (reset)
	{
		*count = 0;
		if (*token_nde && free_flag)
			free(*token_nde);
		*token_nde = NULL;
		return (1);
	}
	return (0);
}

static void	open_par(t_ast_nde **token_nde, char *actual,
	int *count, int *err)
{
	if (!*token_nde)
	{
		*err = 2;
		*token_nde = create_node(PRTH);
		(*token_nde)->start = actual;
	}
	(*count)++;
}

static t_ast_nde	*search_token(char *actual, t_tok token,
	int *err, int *reset)
{
	static t_ast_nde	*token_nde;
	static int			count;

	if (reset_par(reset[0], reset[1], &count, &token_nde))
		return (NULL);
	if (*actual == '(' && token == RAW)
		open_par(&token_nde, actual, &count, err);
	else if (*actual == ')' && token == RAW)
	{
		count--;
		if (count < 0)
			*err = 1;
		else if (!count)
		{
			token_nde->end = actual;
			return (token_nde);
		}
	}
	return (NULL);
}

static int	err_par_handle(char *token)
{
	display_error_free(ft_strjoin("minishell: syntax error near \
unexpected token ", token));
	search_token(NULL, 0, NULL, (int []){1, 1});
	return (-1);
}

int	create_token_node(t_ast_nde *sib, t_ast_nde **token_nde)
{
	char	*actual;
	int		err;

	err = 0;
	while (sib)
	{
		actual = sib->start;
		while (actual <= sib->end)
		{
			*token_nde = search_token(actual, sib->token, &err, (int []){0, 0});
			if (*token_nde)
			{
				search_token(NULL, 0, NULL, (int []){1, 0});
				return (0);
			}
			if (err == 1)
				return (err_par_handle("`)'\n"));
			actual++;
		}
		sib = sib->sibling;
	}
	if (err == 2)
		return (err_par_handle("`('\n"));
	return (0);
}
