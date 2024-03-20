/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:14:59 by seblin            #+#    #+#             */
/*   Updated: 2024/03/17 09:57:31 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_tree.h"

void	free_start(t_ast_nde *node)
{
	if (node && node->start)
		free(node->start);
}

void	free_sibling_cmd(t_ast_nde *sib)
{
	t_ast_nde	*tmp;

	while (sib)
	{
		tmp = sib->sibling;
		free_start(sib);
		free(sib);
		sib = tmp;
	}
}

t_ast_nde	*store_or_free_tree_par(t_ast_nde *root)
{
	static t_ast_nde	*lcl_root;

	if (!root && lcl_root)
	{
		free_tree_par(lcl_root);
		lcl_root = NULL;
	}
	else if (root && !lcl_root)
		lcl_root = root;
	else if (root && lcl_root)
		return (lcl_root);
	return (NULL);
}

void	store_or_free_cmd(char *cmd)
{
	t_ast_nde			*new_cmd;
	static t_ast_nde	*lcl_cmds;
	static t_ast_nde	*lcl_cmds_sav;

	if (!cmd && lcl_cmds_sav)
	{
		free_sibling_cmd(lcl_cmds_sav);
		lcl_cmds_sav = NULL;
	}
	else if (cmd)
	{
		new_cmd = create_node(RAW);
		new_cmd->start = cmd;
		add_sibling(new_cmd, &lcl_cmds, &lcl_cmds_sav);
	}
}

void	store_or_free_cmd_par(char *cmd)
{
	t_ast_nde			*new_cmd;
	static t_ast_nde	*lcl_cmds;
	static t_ast_nde	*lcl_cmds_sav;

	if (!cmd && lcl_cmds_sav)
	{
		free_sibling_cmd(lcl_cmds_sav);
		lcl_cmds_sav = NULL;
	}
	else if (cmd)
	{
		new_cmd = create_node(RAW);
		new_cmd->start = cmd;
		add_sibling(new_cmd, &lcl_cmds, &lcl_cmds_sav);
	}
}
