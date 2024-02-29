/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/29 12:19:08 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	// if (!quote)
	// {
	// 	free_tree(root);
	// 	return (NULL);	
	// }
	root->child->child->child = quote;
	// if (!set_operator(root->child))
	// {
	// 	free_tree(root);
	// 	return (NULL);
	// }
	leaf_tree(root, &cmd, &cmd_sav, data);
	//print_cmd(cmd_sav);
	free_tree(root);
	return (cmd_sav);
}
