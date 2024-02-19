/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:43:41 by svidot            #+#    #+#             */
/*   Updated: 2024/02/19 22:08:01 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_utils.h"
#include "ft_printf.h"


void	print_qute_sib(t_ast_nde *sib)
{
	int	i;	
	int	back_color;
	
	ft_printf("\n");
	while (sib)
	{
		if (sib->token == RAW)				
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
			ft_printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
		sib = sib->sibling;
	}
	ft_printf("\n\n");
}


void print_sibling(t_ast_nde *sib)
{
	int	i;
	int	back_color;	

	back_color = 41;
	i = 0;
	while (sib)
	{	
		i = 0;
		while (sib->start + i <= sib->end)
			ft_printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);			
		back_color = (back_color - 41 + 1) % 7 + 41;
		sib = sib->sibling;
	}	
}
void	print_cmd(t_ast_nde *cmd)
{
	print_sibling(cmd);
	ft_printf("\n\n");
	while (cmd)
	{
		if (cmd->child)
			print_sibling(cmd->child);
		ft_printf("\n\n");
		cmd = cmd->sibling;
	}
}

void	print_raw(t_ast_nde *raw)
{
	int	i;
	int	back_color;
	t_ast_nde	*sib;

	back_color = 41;
	i = 0;
	while (raw && raw->start + i <= raw->end)
		ft_printf("\033[%dm%c\033[0m", back_color, raw->start[i++]);	
	sib = raw->child;
	ft_printf("\n");
	while (sib)
	{
		i = 0;
		while (sib->start + i <= sib->end)
			ft_printf("\033[%dm%c\033[0m", back_color, sib->start[i++]);
		back_color = (back_color - 41 + 1) % 7 + 41;
		sib = sib->sibling;
	}
	ft_printf("\n");
}
void	print_tree(t_ast_nde *node)
{
	t_ast_nde	*operator;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;
	
	operator = node;
	raw_lft = NULL;
	raw_rght = NULL;
	if (operator)
		raw_lft = operator->child;
	if (raw_lft)
	 	raw_rght = raw_lft->sibling;
	if (raw_lft && raw_lft->child)
	{
		print_raw(raw_lft->child);
		ft_printf("\n");
	}
	operator = NULL;
	if (raw_rght && raw_rght->child)
		operator = raw_rght->child->sibling;
	else if (raw_lft && raw_lft->child)
		operator = raw_lft->child->sibling;
	if (operator)
		print_tree(operator);
	else
	{		
		if (raw_rght && raw_rght->child)
		{
			print_raw(raw_rght->child);
			ft_printf("\n");		
		}
	} 
}

void	print_space_tree(t_ast_nde *node)
{
	t_ast_nde	*operator;
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;
	
	operator = node;
	raw_lft = NULL;
	raw_rght = NULL;
	if (operator)
		raw_lft = operator->child;
	if (raw_lft)
	 	raw_rght = raw_lft->sibling;
	if (raw_lft && raw_lft->child)
	{
		print_raw(raw_lft->child);
		ft_printf("\n");
	}
	operator = NULL;
	if  (raw_lft && raw_lft->child && raw_lft->child->sibling)
	{
		operator = raw_lft->child->sibling;
		print_space_tree(operator);
	}
	
	operator = NULL;	
	if (raw_rght && raw_rght->child)
		operator = raw_rght->child->sibling;
	// else if (raw_lft && raw_lft->child)
	// 	operator = raw_lft->child->sibling;
	if (operator)
		print_space_tree(operator);
	else
	{		
		if (raw_rght && raw_rght->child)
		{
			print_raw(raw_rght->child);
			ft_printf("\n");		
		}
	} 
}