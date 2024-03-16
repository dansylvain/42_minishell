/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:59:08 by seblin            #+#    #+#             */
/*   Updated: 2024/03/16 10:14:01 by seblin           ###   ########.fr       */
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

void	free_sibling(t_ast_nde *sib)
{
	t_ast_nde	*tmp;

	while (sib)
	{
		tmp = sib->sibling;
		free(sib);
		sib = tmp;
	}
}

static void	free_branch(t_ast_nde *raw, void (*rec) (t_ast_nde *nde))
{
	t_ast_nde	*cont;

	cont = raw->child;
	free(raw);
	if (cont)
	{
		free_sibling(cont->child);
		if (cont->sibling)
			rec(cont->sibling);
		free(cont);
	}
}

void	free_tree(t_ast_nde *operator)
{
	t_ast_nde	*raw_lft;
	t_ast_nde	*raw_rght;

	raw_lft = NULL;
	raw_rght = NULL;
	if (operator)
	{
		raw_lft = operator->child;
		if (raw_lft)
			raw_rght = raw_lft->sibling;
		free(operator);
	}
	if (raw_lft)
		free_branch(raw_lft, free_tree);
	if (raw_rght)
		free_branch(raw_rght, free_tree);
}

void	free_tree_par(t_ast_nde *operator)
{
	t_ast_nde	*raw_lft;
	t_ast_nde	*middle;
	t_ast_nde	*raw_rght;

	raw_lft = NULL;
	middle = NULL;
	raw_rght = NULL;
	if (operator)
	{
		raw_lft = operator->child;
		if (raw_lft)
			middle = raw_lft->sibling;
		if (middle)
			raw_rght = middle->sibling;
		free(operator);
	}
	if (raw_lft)
		free_branch(raw_lft, free_tree_par);
	if (middle)
		free_branch(middle, free_tree_par);
	if (raw_rght)
		free_branch(raw_rght, free_tree_par);
}

void	store_or_free_tree_par(t_ast_nde *root)
{
	static t_ast_nde	*lcl_root;

	if (!root && lcl_root)
		free_tree_par(lcl_root);
	else if (root)
		lcl_root = root;
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

void	free_sibling_and_child(t_ast_nde *sib)
{
	t_ast_nde	*tmp;

	while (sib)
	{
		free_sibling(sib->child);
		tmp = sib->sibling;
		free(sib);
		sib = tmp;
	}
}
