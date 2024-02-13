/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/13 17:57:43 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing_utils.h"
#include "libft.h"
#include "stdio.h"
#include "parsing_spce.h"
#include "parsing_qute.h"
#include "ft_printf.h"

t_ast_nde	*copy_node(t_ast_nde *node);
t_ast_nde	*copy_node_child(t_ast_nde *node);
t_ast_nde	*set_qute_sib(char *str);
t_ast_nde	*sib_last(t_ast_nde *sib);
t_ast_nde	*set_pipe(t_ast_nde *node);
void		print_qute_sib(t_ast_nde *sib);
void		print_sib(t_ast_nde *sib);
t_ast_nde	*set_operator(t_ast_nde *node);
void	print_tree(t_ast_nde *node);
t_ast_nde	*set_space(t_ast_nde *node);

void print_rslt(t_ast_nde *rslt, int flag);
// static void	leaf_tree(t_ast_nde *root, t_ast_nde **cmd, t_ast_nde **cmd_sav)
// {
// 	t_ast_nde	*head;
	
// 	head = root;
// 	while (head)
// 	{			
// 		if (head->token == PIPE)
// 		{				
// 			leaf_tree(head->child, cmd, cmd_sav);
// 			if (!head->child->child->child)			
// 				add_sibling(head->child, cmd, cmd_sav);			
// 			add_sibling(head->child->sibling, cmd, cmd_sav);
// 			return ;
// 		}		
// 		head = head->child;
// 	}	
// }


static void	leaf_tree(t_ast_nde *node, t_ast_nde **rslt, t_ast_nde **rslt_sav)
{
	t_ast_nde	*operator;
	t_ast_nde	*next_operator;
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
		// if (raw_lft->child->sibling && raw_lft->child->sibling->child && ((raw_lft->child->sibling->child->child)
		// 	|| (raw_lft->child->sibling->child->sibling && raw_lft->child->sibling->child->sibling->child)))				
		if (raw_lft->child->sibling)
			leaf_tree(raw_lft->child->sibling, rslt, rslt_sav);		
		else				
			add_sibling(raw_lft->child, rslt, rslt_sav);		
	}
	if (operator && operator->token != SPCE)
	{
		operator->child = copy_node(operator);	
		add_sibling(operator, rslt, rslt_sav);		
	}
	next_operator = NULL;
	if (raw_rght && raw_rght->child)
		next_operator = raw_rght->child->sibling;
	// else if (raw_lft && raw_lft->child)
	// 	next_operator = raw_lft->child->sibling;
	if (next_operator)
		leaf_tree(next_operator, rslt, rslt_sav);
	else if (raw_rght && raw_rght->child)
	{
		if (raw_rght->child->sibling)
		{
			leaf_tree(raw_rght->child->sibling, rslt, rslt_sav);
			//add_sibling(operator, rslt, rslt_sav);
		}	
		else
		{
			//add_sibling(operator, rslt, rslt_sav);
			add_sibling(raw_rght->child, rslt, rslt_sav);	
		}
	}
}


t_ast_nde	*ft_lstlast_sib(t_ast_nde *lst)
{
	if (!lst)
		return (NULL);
	while (lst->sibling)
		lst = lst->sibling;
	return (lst);
}

void	ft_lstadd_back_sib(t_ast_nde **lst, t_ast_nde *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_sib(*lst)->sibling = new;
}

t_ast_nde	*expand_vars(t_ast_nde *qute_sib)
{
	t_ast_nde *current;
	t_ast_nde *next_sibling;
	t_ast_nde *var_node;
	t_ast_nde *raw_node;
	t_ast_nde *exp_sib;
	
	int i;
	
	exp_sib = (t_ast_nde *)malloc(sizeof(t_ast_nde));
	if (exp_sib == NULL)
		return (NULL);
	exp_sib->sibling = NULL;
	
	

	var_node = NULL;
	current = qute_sib;
	while (current)
	{
		if (current->token == RAW || current->token == IN_DQUTE)
		{
			i = 0;
			raw_node = create_node(RAW);
			raw_node->start = &current->start[i];
			
			while (i < qute_sib->end + 1 - qute_sib->start)
			{
				if (qute_sib->start[i] == '$' && qute_sib->start[i + 1] && qute_sib->start[i + 1] != ' ')
				{
					if (i == 0)
						free (raw_node);
					else
					{
						raw_node->end = &current->start[i];
						ft_lstadd_back_sib(&exp_sib, raw_node);
					}
					


					// create env var node
					var_node = create_node(EXP);
					var_node->start = &qute_sib->start[i];
				}
				if (var_node && (qute_sib->start[i + 1] == ' ' || i == qute_sib->end - qute_sib->start))
				{
					var_node->end = &qute_sib->start[i];
					ft_lstadd_back_sib(&exp_sib, var_node);
					break;
				}
				i++;
			}
			

			if (var_node)
			{
				// ft_printf("var_node->start: %s\n", var_node->start);
				// ft_printf("starting_char: %c\n", var_node->start[0]);
				// ft_printf("ending_char: %c\n", var_node->end[0]);
			}
			// print_sib(exp_sib);
			
			// {
			// 	int i = 0;
			// 	while (i < (var_node->end - var_node->start) + 1)
			// 		write (1, &var_node->start[i++], 1);
			// 	ft_printf("\nvar_len = %i\nchar start: %c\nchar end: %c\n", var_node->end - var_node->start + 1, var_node->start[0], var_node->end[0]);
			// }
		}
		current = current->sibling;		
	}
	
	return (qute_sib);
}

t_ast_nde	*format_io(t_ast_nde* cmd)
{
	t_ast_nde	*actual;
	t_ast_nde	*format_cmd;
	t_ast_nde	*format_cmd_sav;
	t_ast_nde	*inter_cmd_tmp;
	
	format_cmd_sav = NULL;
	actual = cmd;
	while (actual)
	{	
		inter_cmd_tmp = actual;
		while (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
		{
			if (actual->token == SCHEV_LFT || actual->token == DCHEV_LFT)			
			{
				add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
				if (actual && actual->sibling && actual->sibling->token != PIPE && actual->sibling->token != AND  && actual->sibling->token != OR
					&& actual->sibling->token != SCHEV_LFT && actual->sibling->token != DCHEV_LFT)
				{
					add_sibling(copy_node_child(actual->sibling), &format_cmd, &format_cmd_sav);
					actual = actual->sibling;
				}
			}
			actual = actual->sibling;
		}
		actual = inter_cmd_tmp;
		while (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
		{
			if (actual->token == SCHEV_LFT || actual->token == DCHEV_LFT)			
			{			
				if (actual && actual->sibling && actual->sibling->token != PIPE && actual->sibling->token != AND  && actual->sibling->token != OR
					&& actual->sibling->token != SCHEV_LFT && actual->sibling->token != DCHEV_LFT)
					actual = actual->sibling;				
			}
			else
				add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
			actual = actual->sibling;
		}		
		if (actual)
		{
			add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
			actual = actual->sibling;
		}	
	}
	return (format_cmd_sav);
}

t_ast_nde	*format_io2(t_ast_nde* cmd)
{
	t_ast_nde	*actual;
	t_ast_nde	*format_cmd;
	t_ast_nde	*format_cmd_sav;
	t_ast_nde	*inter_cmd_tmp;
	
	format_cmd_sav = NULL;
	actual = cmd;
	while (actual)
	{	
		inter_cmd_tmp = actual;
		while (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
		{
			if (actual->token == SCHEV_RGTH || actual->token == DCHEV_RGTH)			
			{			
				if (actual && actual->sibling && actual->sibling->token != PIPE && actual->sibling->token != AND  && actual->sibling->token != OR
					&& actual->sibling->token != SCHEV_RGTH && actual->sibling->token != DCHEV_RGTH)
					actual = actual->sibling;
				// if (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
				// 	actual = actual->sibling;
			}
			else
				add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
			actual = actual->sibling;
		}		
		actual = inter_cmd_tmp;
		while (actual && actual->token != PIPE && actual->token != AND  && actual->token != OR)
		{
			if (actual->token == SCHEV_RGTH || actual->token == DCHEV_RGTH)			
			{
				add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
				if (actual && actual->sibling && actual->sibling->token != PIPE && actual->sibling->token != AND  && actual->sibling->token != OR
					&& actual->sibling->token != SCHEV_RGTH && actual->sibling->token != DCHEV_RGTH)
				{
					add_sibling(copy_node_child(actual->sibling), &format_cmd, &format_cmd_sav);
					actual = actual->sibling;
				}
			}
			actual = actual->sibling;
		}		
		if (actual)
		{
			add_sibling(copy_node_child(actual), &format_cmd, &format_cmd_sav);
			actual = actual->sibling;
		}
	//	actual = actual->sibling;
	}
	return (format_cmd_sav);
}



void	print_raw_rght(t_ast_nde *raw_rght);
void	print_space_tree(t_ast_nde *node);
static t_ast_nde	*create_ast(char *str)
{
	t_ast_nde	*ast_res;
	t_ast_nde	*qute_sib;
	t_ast_nde	*spce_sib;
	t_ast_nde	*pip_sib;
	t_ast_nde	*parnths_sib;
	t_ast_nde	*root;
	t_ast_nde	*cmd_sav;
	t_ast_nde	*cmd;
	
	cmd_sav = NULL;
	root = create_node(RAW);
	root->start = str;
	root->end = str + ft_strlen(str) - 1;
	root->child = copy_node(root);
	root->child->child = copy_node(root);
	root->child->child->child = set_qute_sib(str);
	//print_qute_sib(root->child->child->child);

	set_operator(root->child); 
	//print_tree(root->child->child->sibling);
	// if (root->child->child->sibling)
	// 	set_space(root->child->child->sibling->child);//exit(1);
	// else 
	// 	set_space(root->child);
	//exit(1);
	//ft_printf("space\n\n");
	
	// if (root->child && root->child->child && root->child->child->sibling && root->child->child->sibling->child && root->child->child->sibling->child->child)
	// 	print_space_tree(root->child->child->sibling->child->child->sibling);

	// else
	// 	print_space_tree(root->child);
//	ft_printf("end\n\n");//exit(1);
	//set_chevron();
	leaf_tree(root->child->child->sibling, &cmd, &cmd_sav);
	// print_rslt(cmd_sav, 1);
	//ft_printf("\n\n");
	// cmd_sav = format_io(cmd_sav);
	//exit(1);
	//print_rslt(cmd_sav, 1);
	//ft_printf("\n\n");
	
	// t_ast_nde	*cmd_sav2 = cmd_sav;
	// while (cmd_sav2)
	// {	
	// 	if(cmd_sav2->token == RAW || cmd_sav2->token == DOLL)// || cmd_sav2->token == SCHEV_LFT || cmd_sav2->token == DCHEV_LFT || cmd_sav2->token == SCHEV_RGTH || cmd_sav2->token == DCHEV_RGTH)
	// 	{			
	// 		print_rslt(cmd_sav2->child, 0);
	// 		ft_printf(" ");
	// 	}
	// 	cmd_sav2 = cmd_sav2->sibling;
	// }
	// ft_printf("\n\n");
	
	cmd_sav = format_io(cmd_sav);
	//print_rslt(cmd_sav, 1);
	//ft_printf("\n\n");
	// t_ast_nde	*cmd_sav3 = cmd_sav;
	// while (cmd_sav3)
	// {	
	// 	if(cmd_sav3->token == RAW || cmd_sav3->token == DOLL)// || cmd_sav2->token == SCHEV_LFT || cmd_sav2->token == DCHEV_LFT || cmd_sav2->token == SCHEV_RGTH || cmd_sav2->token == DCHEV_RGTH)
	// 	{			
	// 		print_rslt(cmd_sav3->child, 0);
	// 		ft_printf(" ");
	// 	}
	// 	cmd_sav3 = cmd_sav3->sibling;
	// }
	// ft_printf("\n\n");
	
	cmd_sav = format_io2(cmd_sav);
	// print_rslt(cmd_sav, 1);
	// ft_printf("\n\n");
	// t_ast_nde	*cmd_sav4 = cmd_sav;
	// while (cmd_sav4)
	// {	
	// 	if(cmd_sav4->token == RAW || cmd_sav4->token == DOLL)// || cmd_sav2->token == SCHEV_LFT || cmd_sav2->token == DCHEV_LFT || cmd_sav2->token == SCHEV_RGTH || cmd_sav2->token == DCHEV_RGTH)
	// 	{			
	// 		print_rslt(cmd_sav4->child, 0);
	// 		ft_printf(" ");
	// 	}
	// 	cmd_sav4 = cmd_sav4->sibling;
	// }
	// ft_printf("\n\n");

	if (!cmd_sav)
		ast_res = root;
	else
		ast_res = cmd_sav;
	return (ast_res);
}

t_ast_nde	*parse(char *str)
{
	if (!*str)
		return (NULL);
	return (create_ast(str));	
}
int	tmp_main(void)
{	
	char *str = " |cat <file1|\"rev\"|ca't'e |grep -n \" cmd1 | cmd2\"| >file2 cut -d':' -f1 ";
	ft_printf("\n%s\n", str);
	parse(str);
	return(0);
}