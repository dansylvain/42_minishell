/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf_par_raw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:12:01 by seblin            #+#    #+#             */
/*   Updated: 2024/03/16 21:57:34 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaf_par_raw.h"

extern int	m_flag;
extern int	p_flag;

static t_ast_nde *get_next_right_token(t_ast_nde *raw_lft) //token ds le noeud right
{	 
	if ((raw_lft && raw_lft->sibling && raw_lft->sibling->sibling
			&& raw_lft->sibling->sibling->child && raw_lft->sibling->sibling
				->child));//->sibling));
	return (raw_lft->sibling->sibling->child);//->sibling);
	return (NULL);
}

static int	is_prev_token(t_ast_nde *raw_lft, t_ast_nde *root)
{
	t_ast_nde	*ex_token;
		
	while (root && root != raw_lft)
	{
		ex_token = root;
		if (get_next_right_token(raw_lft) )
		root = get_next_right_token(raw_lft);
	}
	return ((raw_lft && raw_lft->sibling && raw_lft->sibling->child
			&& raw_lft->sibling->child));//->sibling));
}

int	raw_left_area(t_ast_nde *raw_lft, t_Data *data, int *or_flag)
{
	char		*tmp_str;

	if (raw_lft && raw_lft->child)
	{
		//ft_printf("on raw left!\n");
		// print_node(raw_lft);
		// ft_printf("\n");
		if (get_next_right_token(raw_lft))
			p_flag = 3;
		else
			p_flag = 2;
		//ft_printf("is tk, p_flag :%d\n", p_flag);		
		tmp_str = ft_strndup(raw_lft->start, raw_lft->end - raw_lft->start + 1);
		store_or_free_cmd(tmp_str);
		*or_flag = exec_pipex(data, tmp_str, data->envp_tab, 0);
		store_or_free_cmd(NULL);
	}
}

int	middle_area(t_ast_nde *middle, t_Data *data, int or_flag)
{
	char	*tmp_str;

	if (middle && middle->child && !or_flag)
	{
		m_flag = 1;
		middle->start++;
		middle->end--;
		middle->child->start++;
		middle->child->end--;
		tmp_str = ft_strndup(middle->start, middle->end - middle->start + 1);
		store_or_free_cmd_par(tmp_str);
		if (parse_par(tmp_str, data, middle))
		{
			store_or_free_cmd_par(NULL);
			m_flag = 0;
			return (1);
		}
		store_or_free_cmd_par(NULL);
	}
}

int	raw_right_area(t_ast_nde *raw_rght, t_Data *data)
{
	if (raw_rght && raw_rght->child)
	{
		if (leaf_tree_par(raw_rght, data))
		{
			m_flag = 0;
			return (1);
		}
	}
}
