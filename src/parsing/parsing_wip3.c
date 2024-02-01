/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wip3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/01 21:15:53 by seblin           ###   ########.fr       */
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

void	print_sib(t_ast_nde *sib)
{
	int	i;	
	int	color;
	
	color = 31;
	while (sib)
	{		
		i = 0;
		while (sib->start + i <= sib->end)
			printf("\033[%dm%c\033[0m", color, sib->start[i++]);
		color = (color - 31 + 1) % 7 + 31;	
		sib = sib->sibling;
	}
	printf("\n");
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
t_ast_nde	*copy_node(t_ast_nde *node)
{
	t_ast_nde	*new_node;
	
	new_node = create_node(node->token);
	if (!new_node)
		return (NULL);
	new_node->start = node->start;
	new_node->end = node->end;
	return (new_node);	
}

static t_ast_nde	*set_pipe_sib(t_ast_nde *sib)
{
	t_ast_nde	*pip_sib_sav;
	t_ast_nde	*pip_sib;
	t_ast_nde	*pip_nde;
	t_ast_nde	*raw_nde;
	t_ast_nde	*raw_nde_sav;	
	char *tmp_sib_start;

	pip_sib_sav = NULL;
	while (sib)
	{
		if (sib->token == SQUTE || sib->token == IN_SQUTE
			|| sib->token == DQUTE || sib->token == IN_DQUTE)
		{
			if (!raw_nde)
			{				
				raw_nde = create_node(NONE);
				raw_nde->start = sib->start;
				raw_nde->end = sib->end;
				raw_nde->child = copy_node(sib);
			}
			else
			{
				raw_nde->end = sib->end;
				add_sibling(copy_node(sib), &raw_nde, &raw_nde_sav);
			}
		}
		else 
		{
			tmp_sib_start = sib->start;
			while (sib->start <= sib->end)
			{printf("truc %s\n", sib->start);
				if (*sib->start == '|')				
				{
					pip_nde = create_node(PIPE);
					pip_nde->start = sib->start;
					pip_nde->end = sib->end;
					if (raw_nde)
					{
						add_sibling(raw_nde, &pip_sib, &pip_sib_sav);
						raw_nde = NULL;	
					}
					add_sibling(pip_nde, &pip_sib, &pip_sib_sav);
				}
				else 
				{
					;	
				}
				sib->start++;
			}
			sib->start = tmp_sib_start;
		}
		sib = sib->sibling;
	}
	return (pip_sib_sav);
}

static char	**create_ast3(char *str)
{
	char		**ast_res;
	t_ast_nde	*qute_sib;
	t_ast_nde	*spce_sib;
	t_ast_nde	*pip_sib;
	t_ast_nde	*parnths_sib;
	
	qute_sib = set_qute_sib3(str);
	print_qute_sib3(qute_sib);
	pip_sib = set_pipe_sib(qute_sib);
	print_sib(pip_sib);
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
	char *str = "  cat <file1|\"rev\"|ca't' |grep -n \" cmd1 | cmd2\"| >file2 cut -d':' -f1 ";
	printf("%s\n", str);
	parse3(str);
	return(0);
}