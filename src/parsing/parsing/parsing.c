/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:18:58 by seblin            #+#    #+#             */
/*   Updated: 2024/02/26 09:38:57 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing_utils.h"
#include "libft.h"
#include "minishell.h"

t_ast_nde	*copy_node(t_ast_nde *node);
t_ast_nde	*set_qute_sib(char *str);
t_ast_nde	*set_operator(t_ast_nde *node);
void		leaf_tree(t_ast_nde *operator, t_ast_nde **rslt,
				t_ast_nde **rslt_sav, t_Data *data);
void		free_tree(t_ast_nde *operator);
void		print_qute_sib(t_ast_nde *sib);
void		print_tree(t_ast_nde *node);
void		print_cmd(t_ast_nde *cmd);

t_ast_nde	*parse(char *str, t_Data *data)
{
	t_ast_nde	*root;
	t_ast_nde	*cmd_sav;
	t_ast_nde	*cmd;

	if (!*str)
		return (NULL);
	cmd_sav = NULL;
	root = create_node(RAW);
	root->start = str;
	root->end = str + ft_strlen(str) - 1;
	root->child = copy_node(root);
	root->child->child = copy_node(root);
	root->child->child->child = set_qute_sib(str);
	set_operator(root->child);
	leaf_tree(root, &cmd, &cmd_sav, data);
	free_tree(root);
	return (cmd_sav);
}
