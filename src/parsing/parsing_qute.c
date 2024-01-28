/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_qute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:08:19 by svidot            #+#    #+#             */
/*   Updated: 2024/01/28 18:32:08 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "parsing_utils.h"

char	clean_quotes(char *start, t_ast_nde	*qute_nde)
{
	static t_ast_nde	*lcl_qute_nde;
	t_ast_nde			*tmp_nde;

	if (qute_nde && qute_nde->start)
	{
		lcl_qute_nde = qute_nde;
		return (0);
	}
	tmp_nde = lcl_qute_nde;
	while (tmp_nde)
	{
		if (start != tmp_nde->start && start != tmp_nde->end)
			tmp_nde = tmp_nde->sibling;
		else
			return (0);
	}
	return (*start);
}

static void	set_dqute_nde(t_ast_nde *dqute, t_ast_nde *sibling_sav,
							char **argv)
{
	while (**argv)
	{
		if (**argv == '\"')
		{
			if (!dqute->start)
				dqute->start = *argv;
			else
			{
				dqute->end = *argv;
				break ;
			}
		}
		(*argv)++;
	}
	if (dqute->start && !dqute->end)
	{
		ft_putstr_fd("double quote error\n", 2);
		free_sib(sibling_sav);
		free_sib(dqute);
		exit(1);
	}
}

static void	set_squte_nde(t_ast_nde *squte, t_ast_nde *sibling_sav,
							char **argv)
{
	while (**argv)
	{
		if (**argv == '\'')
		{
			if (!squte->start)
				squte->start = *argv;
			else
			{
				squte->end = *argv;
				break ;
			}
		}
		(*argv)++;
	}
	if (squte->start && !squte->end)
	{
		ft_putstr_fd("simple quote error\n", 2);
		free_sib(sibling_sav);
		free_sib(squte);
		exit(1);
	}
}

t_ast_nde	*set_quote_nde(char *argv)
{
	t_ast_nde	*qute_sibling_sav;
	t_ast_nde	*qute_sibling;
	t_ast_nde	*qute_nde;

	qute_sibling_sav = NULL;
	while (*argv)
	{
		if (*argv == '\'')
		{
			qute_nde = create_node(SQUTE);
			set_squte_nde(qute_nde, qute_sibling_sav, &argv);
			add_sibling(qute_nde, &qute_sibling, &qute_sibling_sav);
		}
		else if (*argv == '\"')
		{
			qute_nde = create_node(DQUTE);
			set_dqute_nde(qute_nde, qute_sibling_sav, &argv);
			add_sibling(qute_nde, &qute_sibling, &qute_sibling_sav);
		}
		argv++;
	}
	return (qute_sibling_sav);
}

static int	is_other(char *str)
{
	return (!(*str - 1 != '\\' && (*str == '\'' || *str == '\"')));
}

static int	is_qute(char *str, char qute)
{
	return ((*str - 1) != '\\' && (*str == qute));
}

static void	set_other_nde(t_ast_nde *other, char **str)
{
	other->start = *str;
	other->end = *str;
	while (*(*++str))
	{
		if (!is_other(*str))			
			break ;
		other->end = *str;			
	}	
}

static int set_qute_nde(t_ast_nde *qute_nde, char qute,
	t_ast_nde *sibling_sav, char **str)
{
	qute_nde->start = *str;
	while (*(*++str))
	{
		if (is_qute(*str, qute))
		{		
			qute_nde->end = *str;
			break ;
		}		
	}
	if (!qute_nde->end)
	{
		ft_putstr_fd("quote error\n", 2);
		free_sib(sibling_sav);
		free_sib(qute_nde);
		return (1);
	}
	return (0);
}
static void	link_node(t_tok tok, t_ast_nde *qute_sibling,
	t_ast_nde **qute_sibling_sav, char **str)
{
	t_ast_nde	*new_nde;
	
	new_nde = create_node(tok);
	set_qute_nde(new_nde, '\'', *qute_sibling_sav, str);
	add_sibling(new_nde, qute_sibling, qute_sibling_sav);
}

t_ast_nde	*set_quote_nde2(char *str)
{
	t_ast_nde	*qute_sibling_sav;
	t_ast_nde	*qute_sibling;
//	t_ast_nde	*qute_nde;
	t_ast_nde	*other_nde;
	
	qute_sibling_sav = NULL;
	while (*str)
	{
		if (is_qute(str, '\''))
		{
			link_node(SQUTE)
			qute_nde = create_node(SQUTE);
			set_qute_nde(qute_nde, '\'', qute_sibling_sav, &str);
			add_sibling(qute_nde, &qute_sibling, &qute_sibling_sav);
		}
		else if (is_qute(str, '\"'))
		{
			qute_nde = create_node(DQUTE);
			set_qute_nde(qute_nde, '\"', qute_sibling_sav, &str);
			add_sibling(qute_nde, &qute_sibling, &qute_sibling_sav);
		}
		else
		{
			other_nde = create_node(NONE);
			set_other_nde(other_nde, &str);
			add_sibling(qute_nde, &qute_sibling, &qute_sibling_sav);
		}	
	}
	return (qute_sibling_sav);
}
// t_ast_nde	*set_quote_nde2(char *str)
// {
// 	t_ast_nde	*qute_sibling_sav;
// 	t_ast_nde	*qute_sibling;
// //	t_ast_nde	*qute_nde;
// 	t_ast_nde	*other_nde;
	
// 	qute_sibling_sav = NULL;
// 	while (*str)
// 	{
// 		if (is_qute(str, '\''))
// 		{
// 			qute_nde = create_node(SQUTE);
// 			set_qute_nde(qute_nde, '\'', qute_sibling_sav, &str);
// 			add_sibling(qute_nde, &qute_sibling, &qute_sibling_sav);
// 		}
// 		else if (is_qute(str, '\"'))
// 		{
// 			qute_nde = create_node(DQUTE);
// 			set_qute_nde(qute_nde, '\"', qute_sibling_sav, &str);
// 			add_sibling(qute_nde, &qute_sibling, &qute_sibling_sav);
// 		}
// 		else
// 		{
// 			other_nde = create_node(NONE);
// 			set_other_nde(other_nde, &str);
// 			add_sibling(qute_nde, &qute_sibling, &qute_sibling_sav);
// 		}	
// 	}
// 	return (qute_sibling_sav);
// }