/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 19:53:34 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_double_token(t_ast_nde *node)
{
	t_tok	d_tok;

	d_tok = RAW;
	while (node)
	{
		if (node->token != RAW && !is_chevron(node)
			&& node->token != DOLL)
		{
			if (node->token == d_tok)
				return (display_error_free(ft_strjoin("minishell: syntax \
error near unexpected token ", translate_enum(d_tok))), 1);
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
	if (!quote)
		return (free_tree(root), NULL);
	root->child->child->child = quote;
	if (set_operator(root->child))
		return (free_tree(root), NULL);
	leaf_tree(root, &cmd, &cmd_sav, data);
	if (is_double_token(cmd_sav))
		return (free_sibling_and_child(cmd_sav), free_tree(root), NULL);
	return (free_tree(root), cmd_sav);
}
