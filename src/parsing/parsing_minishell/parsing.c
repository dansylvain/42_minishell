/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/03 17:43:59 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing_utils.h"
#include "libft.h"
#include "stdio.h"
#include "parsing_spce.h"
#include "parsing_qute.h"
#include "ft_printf.h"

t_ast_nde	*set_qute_sib(char *str);
t_ast_nde	*sib_last(t_ast_nde *sib);
t_ast_nde	*set_pipe(t_ast_nde *node);
void		print_qute_sib(t_ast_nde *sib);
void		print_sib(t_ast_nde *sib);

static void	leaf_tree(t_ast_nde *root, t_ast_nde **cmd, t_ast_nde **cmd_sav)
{
	t_ast_nde	*head;
	
	head = root;
	while (head)
	{			
		if (head->token == PIPE)
		{				
			leaf_tree(head->child, cmd, cmd_sav);
			if (!head->child->child->child)			
				add_sibling(head->child, cmd, cmd_sav);			
			add_sibling(head->child->sibling, cmd, cmd_sav);
			return ;
		}		
		head = head->child;
	}	
}

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
	qute_sib = set_qute_sib(str);
	print_qute_sib(qute_sib);
	root = create_node(NONE);
	root->start = qute_sib->start;
	root->end = sib_last(qute_sib)->end;
	root->child = qute_sib;
	pip_sib = set_pipe(root);	
	print_sib(pip_sib);
	leaf_tree(root, &cmd, &cmd_sav);
	ft_printf("commandes:\n");
	print_sib(cmd_sav);
	
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