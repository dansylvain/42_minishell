/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wip3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/01/31 17:57:21 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing_utils.h"
#include "libft.h"
#include "stdio.h"
#include "parsing_spce.h"
#include "parsing_qute.h"

static int	is_raw3(char *str)
{
	return (!(*(str - 1) != '\\' && (*str == '\'' || *str == '\"')));
}

static int	is_qute3(char *str, char qute)
{
	return (*(str - 1) != '\\' && *str == qute);
}

static void	set_raw_nde3(t_ast_nde *raw, char **str)
{
	raw->start = *str;
	raw->end = *str;
	
	while (*++(*str))
	{
		if (!is_raw3(*str))			
			break ;
		raw->end = *str;			
	}	
}

static int set_qute_nde3(t_ast_nde *qute_nde, char qute,
	t_ast_nde *sibling_sav, char **str)
{
	qute_nde->start = *str;
	while (**str)
	{
		if (is_qute3(*str, qute))
		{		
			qute_nde->end = (*str - 1);		
			break ;
		}
		(*str)++;	
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

static void	link_inqute_node3(t_tok *tok, char qute, t_ast_nde **qute_sibling,
	t_ast_nde **qute_sibling_sav, char **str)
{
	t_ast_nde	*new_nde;
	
	new_nde = create_node(tok[0]);
	new_nde->start = *str;
	new_nde->end = (*str)++;
	add_sibling(new_nde, qute_sibling, qute_sibling_sav);
	new_nde = create_node(tok[1]);
	set_qute_nde3(new_nde, qute, *qute_sibling_sav, str); 	
	add_sibling(new_nde, qute_sibling, qute_sibling_sav);
	new_nde = create_node(tok[0]);
	new_nde->start= *str;
	new_nde->end = (*str)++;
	add_sibling(new_nde, qute_sibling, qute_sibling_sav);
}

static t_ast_nde	*set_qute_sib3(char *str)
{
	t_ast_nde	*qute_sibling_sav;
	t_ast_nde	*qute_sibling;
	t_ast_nde	*raw_nde;

	qute_sibling_sav = NULL;
	while (*str)
	{
		if (is_qute3(str, '\''))
			link_inqute_node3((t_tok[]){SQUTE, IN_SQUTE}, '\'', &qute_sibling, &qute_sibling_sav, &str);
		else if (is_qute3(str, '\"'))
			link_inqute_node3((t_tok[]){DQUTE, IN_DQUTE}, '\"', &qute_sibling, &qute_sibling_sav, &str);
		else
		{
			raw_nde = create_node(NONE);
			set_raw_nde3(raw_nde, &str);
			add_sibling(raw_nde, &qute_sibling, &qute_sibling_sav);
		}
	}
	return (qute_sibling_sav);
}

void	print_qute_sib3(t_ast_nde *sib)
{
	int	i;	
	int	back_color;
	
	while (sib)
	{
		if (sib->token == NONE)				
			back_color = 41;		
		else if (sib->token == SQUTE)	
			back_color = 40;
		else if (sib->token == IN_SQUTE)	
			back_color = 42;		
		else if (sib->token == DQUTE)		
			back_color = 45;
		else if (sib->token == IN_DQUTE)	
			back_color = 46;	
		i = 0;
		while (sib->start + i <= sib->end)
			printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
		sib = sib->sibling;
	}
	printf("\n");
}

static char	**create_ast3(char *str)
{
	char		**ast_res;
	t_ast_nde	*qute_sib;
	t_ast_nde	*spce_sib;
	t_ast_nde	*parnths_sib;
	
	qute_sib = set_qute_sib3(str);
	print_qute_sib3(qute_sib);

	free_sib(qute_sib);
	return (ast_res);
}
char	*parse3(char *str)
{
	if (!*str)
		return (NULL);
	create_ast3(str);
	return ("ok");
}
int	tmp_main3(void)
{
	//char *str = "x'e \"s 't \"\"ju\"' m\"oi' bie '   n ";
	char *str = "x 'e \"s '  t \"\"ju\"' m\"oi' bie '   n ";
	printf("%s\n", str);
	parse3(str);
	return(0);
}