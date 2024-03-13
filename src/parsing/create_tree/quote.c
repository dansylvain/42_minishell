/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:36:13 by svidot            #+#    #+#             */
/*   Updated: 2024/03/13 09:04:23 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote.h"

static void	set_raw_nde(t_ast_nde *raw, char **str)
{
	raw->start = *str;
	raw->end = *str;
	while (*++(*str))
	{
		if (**str == '\'' || **str == '"')
			break ;
		raw->end = *str;
	}
}

static int	set_qute_nde(t_ast_nde *qute_nde, char qute,
	t_ast_nde *sibling_sav, char **str)
{
	qute_nde->start = *str;
	while (**str)
	{
		if (**str == qute)
		{
			qute_nde->end = (*str - 1);
			break ;
		}
		(*str)++;
	}
	if (!qute_nde->end)
	{
		display_error("minishell: Quote error\n");
		get_data(NULL)->exit_status = 2;
		free_sibling(sibling_sav);
		free_sibling(qute_nde);
		return (1);
	}
	return (0);
}

static int	link_inqute_node(t_tok tok, char qute, t_ast_nde **qute_sibling[],
	char **str)
{
	t_ast_nde	*new_nde;

	(*str)++;
	new_nde = create_node(tok);
	if (set_qute_nde(new_nde, qute, *qute_sibling[1], str))
		return (1);
	add_sibling(new_nde, qute_sibling[0], qute_sibling[1]);
	(*str)++;
	return (0);
}

static void	create_raw_node(t_ast_nde **raw_nde, char **str,
	t_ast_nde **qute_sibling, t_ast_nde **qute_sibling_sav)
{
	*raw_nde = create_node(RAW);
	set_raw_nde(*raw_nde, str);
	add_sibling(*raw_nde, qute_sibling, qute_sibling_sav);
}

t_ast_nde	*set_qute_sib(char *str)
{
	t_ast_nde	*qute_sibling_sav;
	t_ast_nde	*qute_sibling;
	t_ast_nde	*raw_nde;

	qute_sibling_sav = NULL;
	while (*str)
	{
		if (*str == '\'')
		{
			if (link_inqute_node(IN_SQUTE, '\'',
					(t_ast_nde **[]){&qute_sibling, &qute_sibling_sav}, &str))
				return (NULL);
		}
		else if (*str == '"')
		{
			if (link_inqute_node(IN_DQUTE, '"', (t_ast_nde **[]){&qute_sibling,
					&qute_sibling_sav}, &str))
				return (NULL);
		}
		else
			create_raw_node(&raw_nde, &str, &qute_sibling,
				&qute_sibling_sav);
	}
	return (qute_sibling_sav);
}
