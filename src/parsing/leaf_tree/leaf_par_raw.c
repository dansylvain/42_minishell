/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf_par_raw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:12:01 by seblin            #+#    #+#             */
/*   Updated: 2024/03/18 19:32:18 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaf_par_raw.h"

static int	is_next_middle(t_ast_nde *raw_lft)
{
	return (raw_lft && raw_lft->sibling && raw_lft->sibling->child);
}

void	raw_left_area(t_ast_nde *raw_lft, t_Data *data, int *or_flag)
{
	char	*tmp_str;
	int		*policy;

	policy = get_err_policy();
	if (raw_lft && raw_lft->child)
	{
		if (is_next_middle(raw_lft) && policy[2])
			policy[0] = 3;
		else
			policy[0] = 2;
		tmp_str = ft_strndup(raw_lft->start, raw_lft->end - raw_lft->start + 1);
		store_or_free_cmd(tmp_str);
		*or_flag = exec_pipex(data, tmp_str, data->envp_tab, 0);
		store_or_free_cmd(NULL);
	}
}

void	middle_area(t_ast_nde *middle, t_Data *data, int or_flag)
{
	char	*tmp_str;
	int		*policy;

	policy = get_err_policy();
	if (middle && middle->child && !or_flag)
	{
		policy[1] = 1;
		middle->start++;
		middle->end--;
		middle->child->start++;
		middle->child->end--;
		tmp_str = ft_strndup(middle->start, middle->end - middle->start + 1);
		store_or_free_cmd_par(tmp_str);
		if (parse_par(tmp_str, data, middle))
		{
			store_or_free_cmd_par(NULL);
			policy[1] = 0;
			return ;
		}
		store_or_free_cmd_par(NULL);
	}
}

void	raw_right_area(t_ast_nde *raw_rght, t_Data *data)
{
	int	*policy;

	policy = get_err_policy();
	if (raw_rght && raw_rght->child)
	{
		policy[2] = 1;
		leaf_tree_par(raw_rght, data);
		policy[1] = 0;
	}
}
