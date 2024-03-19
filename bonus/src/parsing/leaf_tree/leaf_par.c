/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf_par.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:10:42 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 19:25:30 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaf_par.h"

static void	token_zone(t_ast_nde *token, t_Data *data)
{
	t_ast_nde	*raw_lft;
	t_ast_nde	*middle;
	t_ast_nde	*raw_rght;
	int			or_flag;

	or_flag = 0;
	if (token)
	{
		raw_lft = token->child;
		if (raw_lft)
		{
			raw_left_area(raw_lft, data, &or_flag);
			middle = raw_lft->sibling;
			if (middle)
			{
				middle_area(middle, data, or_flag);
				raw_rght = middle->sibling;
				if (raw_rght)
					raw_right_area(raw_rght, data);
			}
		}
	}
}

static void	no_token_zone(t_ast_nde *raw, t_Data *data)
{
	char	*tmp_str;
	int		*policy;

	policy = get_err_policy();
	if (policy[1] && !policy[2])
		policy[0] = 0;
	else
		policy[0] = 1;
	policy[1] = 0;
	tmp_str = ft_strndup(raw->start, raw->end - raw->start + 1);
	store_or_free_cmd(tmp_str);
	exec_pipex(data, tmp_str, data->envp_tab, 0);
	store_or_free_cmd(NULL);
}

void	leaf_tree_par(t_ast_nde	*raw, t_Data *data)
{
	t_ast_nde	*token;

	if (raw && raw->child)
	{
		token = raw->child->sibling;
		if (token)
			token_zone(token, data);
		else
			no_token_zone(raw, data);
	}
}
