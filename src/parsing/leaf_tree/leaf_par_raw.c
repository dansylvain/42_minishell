/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf_par_raw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:12:01 by seblin            #+#    #+#             */
/*   Updated: 2024/03/17 18:24:19 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaf_par_raw.h"
#include "test.h"

extern int	r_flag;
extern int	m_flag;
extern int	p_flag;

static int	is_next_middle(t_ast_nde *raw_lft)
{	 
	return (raw_lft && raw_lft->sibling && raw_lft->sibling->child);
}

int	raw_left_area(t_ast_nde *raw_lft, t_Data *data, int *or_flag)
{
	char	*tmp_str;

	if (raw_lft && raw_lft->child)
	{
		//ft_printf("on raw left!\n");
		// print_node(raw_lft);
		// ft_printf("\n");
	//	ft_printf("rflag: %d, is middle: %d\n",r_flag, is_next_middle(raw_lft));
		if (is_next_middle(raw_lft) && r_flag)
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
		r_flag = 1;
		if (leaf_tree_par(raw_rght, data))
		{
			m_flag = 0;
			return (1);
		}
	}
}
