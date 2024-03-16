/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/03/16 20:38:24 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "test.h"

int	set_parenthesis(t_ast_nde *node);
int	exec_pipex(t_Data *data, char *cmd, char *envp[], int reset);
int	leaf_tree_par(t_ast_nde	*raw, t_Data *data);

extern int	m_flag;//!! remetre a un ds prompt loop
extern int	p_flag;

static int	is_double_token(t_ast_nde *node)
{
	t_tok	d_tok;

	d_tok = RAW;
	while (node)
	{
		if (node->token != RAW && !is_chevron(node) && node->token != JOKER && node->token != DOLL)
		{
			// if (d_tok < 0)
// 				return (display_error_free(ft_strjoin("minishell: syntax 
// error near unexpected token DTOK 0 ", translate_enum(d_tok))), 1); //!pas bonn ne marche pas si token diff
			if (node->token == d_tok)
				return (display_error_free(ft_strjoin("minishell: syntax \
error near DOUBLEunexpected token ", translate_enum(d_tok))), 1);
		}
		d_tok = node->token;
		node = node->sibling;
	}
	return (0);
}

static void	set_root(t_ast_nde **root, char *str)
{
	*root = create_node(RAW);
	(*root)->start = str;
	(*root)->end = str + ft_strlen(str) - 1;
	(*root)->child = copy_node(*root);
	(*root)->child->child = copy_node(*root);
}

int	parse_par(char *str, t_Data *data, t_ast_nde *root)
{
	
	t_ast_nde	*cmd_sav;
	t_ast_nde	*cmd;
	t_ast_nde	*quote;
	int			first_rec;
	// if (root)
	// {
	// 	ft_printf("parse par\n");
	// 	print_node(root);
	// 	ft_printf("\n");
	// }
	//m_flag = 0;
	first_rec = 0;
	if (!*str)
		return (1);
	cmd_sav = NULL;
	exec_pipex(NULL, NULL, NULL, 1);
	if (!root)
	{
		first_rec = 1;
		set_root(&root, str);
		quote = set_qute_sib(str);		
		root->child->child->child = quote;
		if (!quote)
			return (free_tree(root), 1);
		store_or_free_tree_par(root);
		root = root->child;
	}	
	if (set_parenthesis(root) < 0)
	{	
		if (first_rec)		
			store_or_free_tree_par(NULL);		
		return (1);
	}		
	if (leaf_tree_par(root, data))
	{			
		if (first_rec)		
			store_or_free_tree_par(NULL);		
		return (1);
	}
	if (first_rec)	
		store_or_free_tree_par(NULL);	
	return (0);	
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
	
	set_root(&root, str);
	quote = set_qute_sib(str);
	root->child->child->child = quote;		
	if (!quote)
		return (free_tree(root), NULL);	
	if (set_operator(root->child))
		return (free_tree(root), NULL);	
	leaf_tree(root, &cmd, &cmd_sav, data);
	if (is_double_token(cmd_sav))
		return (free_sibling_and_child(cmd_sav), free_tree(root), NULL);
	return (free_tree(root), cmd_sav);
}
