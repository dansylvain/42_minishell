/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:36:13 by svidot            #+#    #+#             */
/*   Updated: 2024/02/18 13:57:43 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "libft.h"

static int	is_raw(char *str)
{
	return (!(*(str - 1) != '\\' && (*str == '\'' || *str == '\"')));
}

static int	is_qute(char *str, char qute)
{
	return (*(str - 1) != '\\' && *str == qute);
}

static void	set_raw_nde(t_ast_nde *raw, char **str)
{
	raw->start = *str;
	raw->end = *str;
	
	while (*++(*str))
	{
		if (!is_raw(*str))			
			break ;
		raw->end = *str;			
	}	
}

static int set_qute_nde(t_ast_nde *qute_nde, char qute,
	t_ast_nde *sibling_sav, char **str)
{
	qute_nde->start = *str;
	while (**str)
	{
		if (is_qute(*str, qute))
		{		
			qute_nde->end = (*str - 1);		
			break ;
		}
		(*str)++;	
	}
	if (!qute_nde->end)
	{		
		ft_putstr_fd("HANDLE this quote error\n", 2);
		free_sibling(sibling_sav);
		free_sibling(qute_nde);
		return (1);
	}
	return (0);
}

static void	link_inqute_node(t_tok tok, char qute, t_ast_nde **qute_sibling,
	t_ast_nde **qute_sibling_sav, char **str)
{
	t_ast_nde	*new_nde;
	
	// new_nde = create_node(tok[0]);
	// new_nde->start = *str;
	// new_nde->end = (*str)++;
	// add_sibling(new_nde, qute_sibling, qute_sibling_sav);
	(*str)++;
	new_nde = create_node(tok);
	set_qute_nde(new_nde, qute, *qute_sibling_sav, str); 	
	add_sibling(new_nde, qute_sibling, qute_sibling_sav);
	(*str)++;
	// new_nde = create_node(tok[0]);
	// new_nde->start= *str;
	// new_nde->end = (*str)++;
	// add_sibling(new_nde, qute_sibling, qute_sibling_sav);
}

t_ast_nde	*set_qute_sib(char *str)
{
	t_ast_nde	*qute_sibling_sav;
	t_ast_nde	*qute_sibling;
	t_ast_nde	*raw_nde;

	qute_sibling_sav = NULL;
	while (*str)
	{
		if (is_qute(str, '\''))
			link_inqute_node(IN_SQUTE, '\'', &qute_sibling, &qute_sibling_sav, &str);
		else if (is_qute(str, '\"'))
			link_inqute_node(IN_DQUTE, '\"', &qute_sibling, &qute_sibling_sav, &str);
		else
		{
			raw_nde = create_node(RAW);
			set_raw_nde(raw_nde, &str);
			add_sibling(raw_nde, &qute_sibling, &qute_sibling_sav);
		}
	}
	//qute_sibling_sav = unquote_sibling(qute_sibling_sav);
	return (qute_sibling_sav);
}
