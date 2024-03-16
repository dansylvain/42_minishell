/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:52:11 by seblin            #+#    #+#             */
/*   Updated: 2024/03/16 12:28:59 by seblin           ###   ########.fr       */
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
void	display_error_free(char *str);

#include "ft_printf.h"

int	reset_par(int reset, int *count, t_ast_nde	**token_nde, int free_flag)
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
void	open_par(t_ast_nde	**token_nde, char *actual, int *count, int *err)
{
	if (!*token_nde)
	{
		*err = 2;
		*token_nde = create_node(PRTH);
		(*token_nde)->start = actual;
	}
	(*count)++;
}

static t_ast_nde	*search_token(char *actual, t_tok token, int *err, int reset, int free_flag)
{
	static t_ast_nde	*token_nde;
	static int	count;
	
	if (reset_par(reset, &count, &token_nde, free_flag))
		return (NULL);
	if (*actual == '(' && token == RAW)	
		open_par(&token_nde, actual, &count, err);	
	else if  (*actual == ')' && token == RAW) 
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
	search_token(NULL, 0, NULL, 1, 1);
	return (-1);
}

static int	create_token_node(t_ast_nde *sib, t_ast_nde **token_nde)
{	
	char		*actual;
	int			err;

	err = 0;
	while (sib)
	{
		actual = sib->start;
		while (actual <= sib->end)
		{			
			*token_nde = search_token(actual, sib->token, &err, 0, 0);			
			if (*token_nde)
			{
				search_token(NULL, 0, NULL, 1, 0);			
				return (0);
			}
			if (err == 1)
				err_par_handle("`)'\n");
			actual++;
		}
		sib = sib->sibling;
	}
	if (err == 2)
		err_par_handle("`('\n");
	return (0);
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

int	token_child_handle(t_ast_nde *sib_cont,
	t_ast_nde *raw_lft, t_ast_nde *token)
{
	t_ast_nde	*sib;
	t_ast_nde 	*raw_rght;
	
	if (token)
	{			
		sib = sib_cont->child;		
		raw_lft = create_token_child_par(sib_cont, token);		
		raw_rght = raw_lft->sibling->sibling;
		token->child = raw_lft;		
		fill_child_par(sib, raw_lft->child, raw_lft->sibling->child, raw_rght->child, token);	
		return (set_parenthesis(raw_rght));		
	}	
}

int	set_parenthesis(t_ast_nde *node)
{
	t_ast_nde	*sib;
	t_ast_nde	*cont_sib;
	t_ast_nde	*token;
	t_ast_nde	*raw_lft;
	int			is_token;

	token = NULL;
	if (node && node->child && node->child->child)
	{		
		cont_sib = node->child;
		sib = cont_sib->child;	
		is_token = create_token_node(sib, &token);
		if (is_token < 0)	
			return (-1);		
	
		cont_sib->sibling = token;
		if (token)
			return (token_child_handle(cont_sib, raw_lft, token));	
	}
	else 
		return (1);
	return (0);
}
