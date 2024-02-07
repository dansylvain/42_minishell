/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/07 19:02:27 by seblin           ###   ########.fr       */
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
t_ast_nde	*set_qute_sib(char *str);
t_ast_nde	*sib_last(t_ast_nde *sib);
t_ast_nde	*set_pipe(t_ast_nde *node);
void		print_qute_sib(t_ast_nde *sib);
void		print_sib(t_ast_nde *sib);
t_ast_nde	*set_operator(t_ast_nde *node);
void	print_tree(t_ast_nde *node);

void print_rslt(t_ast_nde *rslt);
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
	if (operator && operator->child)
		raw_lft = operator->child;
	if (raw_lft && raw_lft->sibling)
	 	raw_rght = raw_lft->sibling;
	if (raw_rght)
	{
		add_sibling(raw_rght, rslt, rslt_sav);	
		add_sibling(operator, rslt, rslt_sav);
	}
	next_operator = NULL;
	if (raw_lft && raw_lft->child && raw_lft->child->sibling)
		next_operator = raw_lft->child->sibling;
	if (next_operator)
		leaf_tree(next_operator, rslt, rslt_sav);
	else if (raw_lft && raw_lft->child)	
		add_sibling(raw_lft->child, rslt, rslt_sav);	
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
				ft_printf("var_node->start: %s\n", var_node->start);
				ft_printf("starting_char: %c\n", var_node->start[0]);
				ft_printf("ending_char: %c\n", var_node->end[0]);
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

void	print_raw_rght(t_ast_nde *raw_rght);
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
	print_qute_sib(root->child->child->child);

	set_operator(root->child);
	print_tree(root->child->child->sibling);

	leaf_tree(root->child->child->sibling, &cmd, &cmd_sav);	
	print_rslt(cmd_sav);

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