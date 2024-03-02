/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:52:11 by seblin            #+#    #+#             */
/*   Updated: 2024/03/02 21:24:13 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parenthesis.h"
#include <stdlib.h>
#include "parsing_utils.h"
#include "libft.h"

t_ast_nde	*copy_node(t_ast_nde *node);
int			set_space(t_ast_nde *node);
int			set_operator(t_ast_nde *node);
char		*translate_enum(t_tok token);
t_ast_nde	*create_token_child(t_ast_nde *raw, t_ast_nde *token);
void		fill_child(t_ast_nde *sib, t_ast_nde *raw_lft,
				t_ast_nde *raw_rght, t_ast_nde *token);
int			set_parenthesis(t_ast_nde *node);
void	print_cmd(t_ast_nde *cmd);
void print_sibling(t_ast_nde *sib);
void	print_node_and_childs(t_ast_nde *sib);
void	print_node(t_ast_nde *sib);
void	print_raw(t_ast_nde *raw);

#include "ft_printf.h"
static t_ast_nde	*search_token(char *actual, t_tok token, int *err, int reset)
{
	static t_ast_nde	*token_nde;
	static int	count;
	
	if (reset)
	{
		count = 0;
		token_nde = NULL;
		return (NULL);	
	}
	//ft_printf("search token\n count :%d, actual:%c\n", count, *actual);
	if (*actual == '(' && token == RAW)//!	
	{	//ft_printf("search token in 1\n");
		if (!token_nde)
		{
			*err = 2;
			token_nde = create_node(PRTH);
			token_nde->start = actual;
		}
		count++;
	}
	else if  (*actual == ')' && token == RAW) 
	{ //ft_printf("search token in 2\n");
		count--;
		if (count < 0)
		{
			*err = 1;//!
			ft_printf("ERROUR\n");
		}
		else if (!count)
		{		
		//	ft_printf("search token in 2 before actual\n");
			//if 
			token_nde->end = actual;
			// ft_printf("search token in 2 after actual\n");
			return (token_nde);
		}		
	}
	return (NULL);
}

static t_ast_nde	*create_token_node(t_ast_nde *sib)
{
	t_ast_nde	*token_nde;
	char		*actual;
	int			err;

	err = 0;
	while (sib)
	{
		actual = sib->start;
		while (actual <= sib->end)//! raw
		{
		//	ft_printf("actual :%c\n", *actual);
			token_nde = search_token(actual, sib->token, &err, 0);
			
			if (token_nde)
			{
				search_token(NULL, 0, NULL, 1);
				//print_node(token_nde);
				return (token_nde);
			}
			if (err == 1)
			{
				ft_printf("err 1\n");
				return (NULL);//! data status ?
			}
			actual++;
		}
		if (err == 2)
		{
			ft_printf("err 2\n");
			return (NULL);//! data status ?
		}
		sib = sib->sibling;
	}
	return (NULL);
}
static int	fill_child_entire_par(t_ast_nde *sib, t_ast_nde *raw_lft_child,  t_ast_nde *middle_child, t_ast_nde *raw_rght_child, t_ast_nde *token, t_ast_nde **raw_lft_child_sav, t_ast_nde **middle_child_sav, t_ast_nde **raw_rght_child_sav)
{
	if (sib->end < token->start)
		add_sibling(copy_node(sib), &raw_lft_child->child, raw_lft_child_sav);
	else if (sib->start > token->end)
		add_sibling(copy_node(sib), &raw_rght_child->child, raw_rght_child_sav);
	else
		return (0);
	return (1);
}

static void	fill_child_overlap_par(t_ast_nde *sib, t_ast_nde *raw_lft_child, t_ast_nde *middle_child, t_ast_nde *raw_rght_child, t_ast_nde *token, t_ast_nde **raw_lft_child_sav, t_ast_nde **middle_child_sav, t_ast_nde **raw_rght_child_sav)
{
	t_ast_nde	*raw_overlap;

	if (sib->start <= token->start && sib->end >= token->end)
	{
		if (sib->start < token->start)
		{
			raw_overlap = copy_node(sib);
			raw_overlap->end = token->start - 1;
			add_sibling(raw_overlap, &raw_lft_child->child, raw_lft_child_sav);
		}
		if (sib->end > token->end)
		{
			raw_overlap = copy_node(sib);
			raw_overlap->start = token->end + 1;
			add_sibling(raw_overlap, &raw_rght_child->child, raw_rght_child_sav);
		}
		if (sib->start <= token->start && sib->end >= token->end)		
		{	
			raw_overlap = copy_node(sib);			
			raw_overlap->start = token->start + 1;
			raw_overlap->end =  token->end - 1;			
			add_sibling(raw_overlap, &middle_child->child, middle_child_sav);	
		}
	}
}

static void	fill_child_par(t_ast_nde *sib, t_ast_nde *raw_lft_child, t_ast_nde *middle_child, t_ast_nde *raw_rght_child,
	t_ast_nde *token)
{
	t_ast_nde	*raw_lft_child_sav;
	t_ast_nde	*middle_child_sav;
	t_ast_nde	*raw_rght_child_sav;

	raw_lft_child_sav = NULL;
	middle_child_sav = NULL;
	raw_rght_child_sav = NULL;
	while (sib)
	{
		if (fill_child_entire_par(sib, raw_lft_child, middle_child, raw_rght_child, token, &raw_lft_child_sav, &middle_child_sav, &raw_rght_child_sav))
			;
		else
			fill_child_overlap_par(sib, raw_lft_child, middle_child, raw_rght_child, token, &raw_lft_child_sav, &middle_child_sav, &raw_rght_child_sav);
		sib = sib->sibling;
	}
	if (raw_lft_child)
		raw_lft_child->child = raw_lft_child_sav;
	if (raw_lft_child && raw_lft_child->sibling)
		raw_lft_child->sibling->child = middle_child_sav;
	if (raw_rght_child)
		raw_rght_child->child = raw_rght_child_sav;
}
static t_ast_nde	*create_token_child_par(t_ast_nde *cont_sib, t_ast_nde *token)
{
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;

	raw_lft = create_node(RAW);
	raw_lft->start = cont_sib->start;
	raw_lft->end = token->start - 1;
	if (cont_sib->start != token->start)
		raw_lft->child = copy_node(raw_lft);	
	raw_rght = create_node(RAW);
	raw_rght->start = token->end + 1;
	raw_rght->end = cont_sib->end;
	if (cont_sib->end != token->end)
		raw_rght->child = copy_node(raw_rght);
	raw_lft->sibling = copy_node(token);
	raw_lft->sibling->child = copy_node(token);
	raw_lft->sibling->sibling = raw_rght;	
	return (raw_lft);
}

void	token_child_handle(t_ast_nde *sib_cont,
	t_ast_nde *raw_lft, t_ast_nde *raw_rght, t_ast_nde *token)
{
	t_ast_nde	*sib;
	
	if (token)
	{			
		sib = sib_cont->child;
		
		raw_lft = create_token_child_par(sib_cont, token);
		
		raw_rght = raw_lft->sibling->sibling;
		token->child = raw_lft;
	
		ft_printf("raw_left\n");
		print_raw(raw_lft);
		ft_printf("\nmiddle\n");
		print_raw(raw_lft->sibling);
		ft_printf("\nraw_right\n");
		print_raw(raw_rght);
		ft_printf("\nend\n");
		
		fill_child_par(sib, raw_lft->child, raw_lft->sibling->child, raw_rght->child, token);

		ft_printf("raw_left\n");
		print_raw(raw_lft);
		ft_printf("\nmiddle\n");
		print_raw(raw_lft->sibling);
		ft_printf("\nraw_right\n");
		print_raw(raw_rght);
		ft_printf("\nend\n");
		//exit(1);
		// if (set_operator(raw_lft))
		// {	
		// 	;// ft_putstr_fd("\nsyntax error near unexpected token\n", 2);
		// }
		if (set_parenthesis(raw_lft->sibling))
		{			
			;// ft_putstr_fd("\nsyntax error near unexpected token\n", 2);
		}
		if (set_parenthesis(raw_rght))
		{
			;// ft_putstr_fd("\nsyntax error near unexpected token\n", 2);
		}
	}	
}

int	set_parenthesis(t_ast_nde *node)
{
	t_ast_nde	*sib;
	t_ast_nde	*cont_sib;
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;
	
	if (node && node->child && node->child->child)
	{		
		cont_sib = node->child;
		sib = cont_sib->child;	
		//ft_printf("yea 1\n");
		//print_sibling(sib);
		//ft_printf("\nyea 2\n");
		token = create_token_node(sib);
				
		cont_sib->sibling = token;
		if (token)
			return (token_child_handle(cont_sib, raw_lft, raw_rght, token), 1);
		//set_operator(node);
	}
	else 
		return (1);
	return (0);
}
