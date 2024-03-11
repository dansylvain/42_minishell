/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:43:41 by svidot            #+#    #+#             */
/*   Updated: 2024/03/10 23:23:02 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_utils.h"
#include "ft_printf.h"

void	print_raw(t_ast_nde *raw);

void	print_qute_sib(t_ast_nde *sib)
{
	int	i;	
	int	back_color;
	
	ft_printf("\n");
	back_color = 42;
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

void	print_node(t_ast_nde *node)
{
	int	i;
	int	back_color;
	
	back_color = 41;
	i = 0;
	while (node->start + i <= node->end)
		ft_printf("\033[%dm%c\033[0m", back_color, node->start[i++]);			
	back_color = (back_color - 41 + 1) % 7 + 41;
}

void	print_sibling(t_ast_nde *sib)
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
	ft_printf("\n");
	while (cmd)
	{
		if (cmd->child)
			print_sibling(cmd->child);
		cmd = cmd->sibling;
		ft_printf(" ");
	}
	ft_printf("\n\n");
}

void	print_descend(t_ast_nde *node)
{
	if (node)
	{		
		print_sibling(node);					
		ft_printf("\n");
		print_descend(node->child);
	}	
}

void	print_raw(t_ast_nde *raw)
{		
	if (raw)
	{		
		print_node(raw);					
		ft_printf("\n");
		print_descend(raw->child);
	}	
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
	if (operator->token != SPCE)
	{		
		ft_printf("operator\n");
		print_sibling(operator);
		ft_printf("end operator\n");
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