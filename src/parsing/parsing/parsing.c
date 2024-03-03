/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/03/03 10:59:27 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_parenthesis(t_ast_nde *node);

// t_ast_nde	*parse(char *str, t_Data *data)
// {
// 	t_ast_nde	*root;
// 	t_ast_nde	*cmd_sav;
// 	t_ast_nde	*cmd;
// 	t_ast_nde	*quote;
	
// 	if (!*str)
// 		return (NULL);
// 	cmd_sav = NULL;
// 	root = create_node(RAW);
// 	root->start = str;
// 	root->end = str + ft_strlen(str) - 1;
// 	root->child = copy_node(root);
// 	root->child->child = copy_node(root);
// 	quote = set_qute_sib(str);
// 	if (!quote)
// 		return (free_tree(root), NULL);	
// 	root->child->child->child = quote;
// 	if (set_parenthesis(root->child))
// 		return (free_tree(root), NULL);
// 	leaf_tree(root, &cmd, &cmd_sav, data);
// 	// if (set_operator(root->child))
// 	// 	return (free_tree(root), NULL);	
// 	// leaf_tree(root, &cmd, &cmd_sav, data);
// 	//print_cmd(cmd_sav);	
// 	return (free_tree(root), cmd_sav);
// }



// #include "parsing.h"
// int	set_parenthesis(t_ast_nde *node);

void	exec_pipex(t_Data *data, char *cmd, char *envp[]);
int	leaf_tree_par(t_ast_nde	*raw, t_Data *data, char *envp[])
{		
	t_ast_nde	*token;

	if (raw)
	{
		if (raw->child)
		{
			token = raw->child->sibling;
			if (token && token->child)
			{				
				if (leaf_tree_par(token->child->sibling, data, envp))
					exec_pipex(data, ft_strndup(token->start, token->end - token->start + 1), envp);
				else
					leaf_tree_par(token->child->sibling->sibling, data, envp);				
			}
		}		
	}
	else
		return (1);
	return (0);
}

t_ast_nde	*parse_par(char *str, t_Data *data, char *envp[])
{
	t_ast_nde	*root;
	t_ast_nde	*cmd_sav;
	t_ast_nde	*cmd;
	t_ast_nde	*quote;
	
	if (!*str)
		return (NULL);
	cmd_sav = NULL;
	root = create_node(RAW);
	root->start = str;
	root->end = str + ft_strlen(str) - 1;
	root->child = copy_node(root);
	root->child->child = copy_node(root);
	quote = set_qute_sib(str);
	if (!quote)
		return (free_tree(root), NULL);
	print_qute_sib(quote);
	root->child->child->child = quote;
	if (set_parenthesis(root->child))
		;//return (free_tree(root), NULL);
	leaf_tree_par(root->child, data, envp);
	//print_tree(root);
	exit(1);	
}

t_ast_nde	*parse(char *str, t_Data *data)
{
	t_ast_nde	*root;
	t_ast_nde	*cmd_sav;
	t_ast_nde	*cmd;
	t_ast_nde	*quote;
	
	if (!*str)
		return (NULL);
	cmd_sav = NULL;
	root = create_node(RAW);
	root->start = str;
	root->end = str + ft_strlen(str) - 1;
	root->child = copy_node(root);
	root->child->child = copy_node(root);
	quote = set_qute_sib(str);
	if (!quote)
		return (free_tree(root), NULL);	
	root->child->child->child = quote;		
	if (set_operator(root->child))
		return (free_tree(root), NULL);	
	leaf_tree(root, &cmd, &cmd_sav, data);
	// print_cmd(cmd_sav);	
	return (free_tree(root), cmd_sav);
}
