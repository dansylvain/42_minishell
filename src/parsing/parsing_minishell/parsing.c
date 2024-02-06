/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/06 09:29:09 by dan              ###   ########.fr       */
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

/* typedef struct s_ast_nde
{
	t_tok				token;
	char				*start;
	char				*end;
	struct s_ast_nde	*child;
	struct s_ast_nde	*sibling;
}	t_ast_nde; 

typedef enum e_tok
{
	RAW,
	INVRT,
	SQUTE,
	IN_SQUTE,
	DQUTE,
	IN_DQUTE,
	PIPE,
	SPCE,
	CMD,
	ARG_CMD,
	OPT_CMD,
	ARG_OPT	
}	t_tok;

*/

t_ast_nde	*expand_vars(t_ast_nde *qute_sib)
{
	t_ast_nde *current;
	t_ast_nde *next_sibling;
	t_ast_nde *var_node;
	int i;
	
	var_node = NULL;
	current = qute_sib;
	while (current)
	{
		next_sibling = current->sibling;
		if (qute_sib->token == RAW || qute_sib->token == IN_DQUTE)
		{
			i = 0;
			while (i < qute_sib->end + 1 - qute_sib->start)
			{
				if (qute_sib->start[i] == '$' && qute_sib->start[i + 1] && qute_sib->start[i + 1] != ' ')
				{
					var_node = create_node(EXP);
					var_node->start = &qute_sib->start[i];
				}
				if (var_node && (qute_sib->start[i + 1] == ' ' || i == qute_sib->end - qute_sib->start))
				{
					var_node->end = &qute_sib->start[i];
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
	// ft_printf("qute_sib: ");
	// print_qute_sib(qute_sib);
	root = create_node(RAW);
	root->start = qute_sib->start;
	root->end = sib_last(qute_sib)->end;
	root->child = qute_sib;
	expand_vars(qute_sib);
	pip_sib = set_pipe(root);
	// ft_printf("\nsib: ");
	// print_sib(pip_sib);
	leaf_tree(root, &cmd, &cmd_sav);
	// ft_printf("commandes:\n");
	// print_sib(cmd_sav);
	
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