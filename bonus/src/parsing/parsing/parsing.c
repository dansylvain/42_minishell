/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 19:36:39 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	set_root(t_ast_nde **root, char *str)
{
	*root = create_node(RAW);
	(*root)->start = str;
	(*root)->end = str + ft_strlen(str) - 1;
	(*root)->child = copy_node(*root);
	(*root)->child->child = copy_node(*root);
}

int	first_init_root(char *str, int *first_rec, t_ast_nde **root)
{
	t_ast_nde	*quote;

	*first_rec = 1;
	set_root(root, str);
	quote = set_qute_sib(str);
	(*root)->child->child->child = quote;
	if (!quote)
		return (free_tree(*root), 1);
	store_or_free_tree_par(*root);
	*root = (*root)->child;
	return (0);
}

int	clean_par(int first_rec, int ret)
{
	if (first_rec)
		store_or_free_tree_par(NULL);
	return (ret);
}

int	parse_par(char *str, t_Data *data, t_ast_nde *root)
{
	int	first_rec;
	int	*policy;

	if (!*str)
		return (1);
	policy = get_err_policy();
	policy[1] = 1;
	policy[2] = 0;
	first_rec = 0;
	exec_pipex(NULL, NULL, NULL, 1);
	if (!root && first_init_root(str, &first_rec, &root))
		return (1);
	if (set_parenthesis(root) < 0)
		return (clean_par(first_rec, 1));
	leaf_tree_par(root, data);
	clean_par(first_rec, 0);
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
	return (free_tree(root), cmd_sav);
}
