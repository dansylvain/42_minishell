/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wip3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/03 08:47:25 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing_utils.h"
#include "libft.h"
#include "stdio.h"
#include "parsing_spce.h"
#include "parsing_qute.h"
#include "ft_printf.h"

#define RAW NONE

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

void	print_sib42(t_ast_nde *sib)
{
	int	i;	
	int	back_color;
	const t_ast_nde *sib_sav;
	t_ast_nde *sib_sav2;
		printf("deb\n");
	back_color = 41; 
	sib_sav2 = sib;	
	while (sib)
	{	
		sib_sav = sib;
		while (sib)
		{	
			i = 0;
			while (sib->start + i <= sib->end)
				printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
			back_color = (back_color - 41 + 1) % 7 + 41;
			sib = sib->sibling;
		}
		if (sib_sav && sib_sav->token == PIPE)
		{
			printf("right\n");
			t_ast_nde *tmp = sib_sav->child->sibling->child;
			while (tmp)
			{	
				i = 0;
				while (tmp->start + i <= tmp->end)
					printf("\033[%dm%c\033[0m", back_color, tmp->start[i++]);
				back_color = (back_color - 41 + 1) % 7 + 41;	
				tmp = tmp->sibling;				
			}
			printf("\n");
		}		
		sib = sib_sav->child;
		
		printf("f\n");
	}
	printf("\n");
	// sib = sib_sav2;
	// while (sib)
	// {	
	// 	sib_sav2 = sib;
	// 	while (sib)
	// 	{	
	// 		i = 0;
	// 		while (sib->start + i <= sib->end)
	// 			printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
	// 		back_color = (back_color - 41 + 1) % 7 + 41;	
	// 		sib = sib->sibling;
	// 	}
	// 	//if (sib_sav2->child)
	// 	sib = sib_sav2->child;
	// 	printf("f\n");
	// }
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

t_ast_nde	*sib_last(t_ast_nde *sib)
{	
	while (sib && sib->sibling)		
		sib = sib->sibling; 
	return (sib);
}

char	*search_pipe(const t_ast_nde *sib)
{
	char	*pipe;
	char	*start;

	if (sib)
		start = sib->start;	
	pipe = NULL;
	while (sib)
	{
		while (sib->token == RAW && start <= sib->end)
		{
			if (*(start - 1) != '\\' && *start == '|')
				pipe = start;
			start++;
		}
		sib = sib->sibling;
	}
	return (pipe);
}
void	error_detector(const char *const pipe, const char *const start, const char *const end)
{
	if (pipe == start)
		ft_printf("pipe left operande missing.");
	if (pipe == end)
		ft_printf("pipe right operande missing.");
}

t_ast_nde	*create_pipe(char *start, char *end, char *pipe)
{	
	t_ast_nde	*raw_lft; 
	t_ast_nde	*raw_rght;
	t_ast_nde	*pipe_nde;

	raw_lft = create_node(RAW);
	raw_lft->start = start;
	raw_lft->end = pipe - 1;
	raw_rght = create_node(RAW);
	raw_rght->start = pipe + 1;
	raw_rght->end = end;	
	pipe_nde = create_node(PIPE);
	pipe_nde->start = pipe;
	pipe_nde->end = pipe;
	raw_lft->sibling = raw_rght;
	pipe_nde->child = raw_lft;	
	return (pipe_nde);
}

t_ast_nde	*fill_child(t_ast_nde *sib)
{
	const t_ast_nde	*const pipe = sib->child;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;
	t_ast_nde	*raw_lft_child_sav;
	t_ast_nde	*raw_rght_child_sav;
	t_ast_nde	*raw_overlap;
	raw_lft_child_sav = NULL;
	raw_rght_child_sav = NULL;
	raw_lft = pipe->child;
	raw_rght = raw_lft->sibling;
	while (sib)
	{
		if (sib->token == SQUTE || sib->token == IN_SQUTE
 			|| sib->token == DQUTE || sib->token == IN_DQUTE)
		{
			if 	(sib->end < pipe->start)
				add_sibling(copy_node(sib), &raw_lft->child, &raw_lft_child_sav);				
			else if (sib->start > pipe->start)
				add_sibling(copy_node(sib), &raw_rght->child, &raw_rght_child_sav );	
		}
		else
		{
			if 	(sib->end < pipe->start)
				add_sibling(copy_node(sib), &raw_lft->child, &raw_lft_child_sav);				
			else if (sib->start > pipe->start)
				add_sibling(copy_node(sib), &raw_rght->child, &raw_rght_child_sav );
			else if (sib->start <= pipe->start && sib->end >= pipe->start)
			{
				if (sib->start < pipe->start)
				{
					raw_overlap = copy_node(sib);
					raw_overlap->end = pipe->start - 1;
					add_sibling(raw_overlap, &raw_lft->child, &raw_lft_child_sav);					
				}
				if (sib->end > pipe->start)
				{					
					raw_overlap = copy_node(sib);
					raw_overlap->start = pipe->start + 1;
					add_sibling(raw_overlap, &raw_rght->child, &raw_rght_child_sav);
				}
			}			
		}		
		sib = sib->sibling;
	}
	raw_lft->child = raw_lft_child_sav;
	raw_rght->child = raw_rght_child_sav;
	
}

static t_ast_nde	*set_pipe(t_ast_nde *node)
{
	t_ast_nde *sib = node->child;
	char 	*start;
	char 	*end;
	char	*pipe;
	
	start = node->start;
	end = node->end;	
	pipe = search_pipe(sib);    // gestion des double quotes, simple qute, 	
	if (pipe)
	{
		error_detector(pipe, start, end);
		sib->child = create_pipe(start, end, pipe);
		fill_child(sib);
		set_pipe(sib->child->child);
		//return (sib->child->child);
	}
	return (sib);
}
// static t_ast_nde	*set_pipe_sib(t_ast_nde *sib)
// {
// 	t_ast_nde	*pip_sib_sav;
// 	t_ast_nde	*pip_sib;
// 	t_ast_nde	*pip_nde;
// 	t_ast_nde	*raw_nde;
// 	t_ast_nde	*raw_nde_sav;	
// 	char *tmp_sib_start;

// 	pip_sib_sav = NULL;
// 	while (sib)
// 	{
// 		if (sib->token == SQUTE || sib->token == IN_SQUTE
// 			|| sib->token == DQUTE || sib->token == IN_DQUTE)
// 		{
// 			if (!raw_nde)
// 			{				
// 				raw_nde = create_node(NONE);
// 				raw_nde->start = sib->start;
// 				raw_nde->end = sib->end;
// 				raw_nde->child = copy_node(sib);
// 			}
// 			else
// 			{
// 				raw_nde->end = sib->end;
// 				add_sibling(copy_node(sib), &raw_nde, &raw_nde_sav);
// 			}
// 		}
// 		else 
// 		{
// 			tmp_sib_start = sib->start;
// 			while (sib->start <= sib->end)
// 			{printf("truc %s\n", sib->start);
// 				if (*sib->start == '|')				
// 				{
// 					pip_nde = create_node(PIPE);
// 					pip_nde->start = sib->start;
// 					pip_nde->end = sib->end;
// 					if (raw_nde)
// 					{
// 						add_sibling(raw_nde, &pip_sib, &pip_sib_sav);
// 						raw_nde = NULL;	
// 					}
// 					add_sibling(pip_nde, &pip_sib, &pip_sib_sav);
// 				}
// 				else 
// 				{
// 					;	
// 				}
// 				sib->start++;
// 			}
// 			sib->start = tmp_sib_start;
// 		}
// 		sib = sib->sibling;
// 	}
// 	return (pip_sib_sav);
// }

static char	**create_ast3(char *str)
{
	char		**ast_res;
	t_ast_nde	*qute_sib;
	t_ast_nde	*spce_sib;
	t_ast_nde	*pip_sib;
	t_ast_nde	*parnths_sib;
	t_ast_nde	*base;
	
	qute_sib = set_qute_sib3(str);
	print_qute_sib3(qute_sib);
	base = create_node(NONE);
	base->start = qute_sib->start;
	base->end = sib_last(qute_sib)->end;
	base->child = qute_sib;
	pip_sib = set_pipe(base);	
	print_sib42(pip_sib);
	//free_sib(qute_sib);
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
	char *str = "  cat <file1|\"rev\"|ca't'e |grep -n \" cmd1 | cmd2\"| >file2 cut -d':' -f1 ";
	printf("%s\n", str);
	parse3(str);
	return(0);
}