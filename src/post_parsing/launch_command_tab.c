/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/18 12:31:20 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launch_command_tab.h"
#include "test.h"


void	store_and_free_exit_status_var(char *var_exit_status)
{
	static char	*var_exit_status_lcl = NULL;

	// ft_printf("var: %s\n", var);
	if (var_exit_status)
		var_exit_status_lcl = var_exit_status;
	if (var_exit_status)
		var_exit_status_lcl = var_exit_status;
	else if (var_exit_status_lcl)
	{
	// ft_printf("exec store_and_free_exit_status_var!!!\n");
		free(var_exit_status_lcl);
		var_exit_status_lcl = NULL;
	}
}


/**========================================================================
 *                          build_command_tab_node
 *========================================================================**/

char	*ft_delchar(char *s)
{
	char	*s_save;
		//	ft_printf("del\n");
	s_save = s;
	while (s && *s)
	{
		*s = *(s + 1);
		s++;
	}
	//ft_printf("del\n, s_save: -%s-\n", s_save);
	return (s_save);
}

char	*replace_exit_status(char *str)
{
	char	*status;
	int		status_len;
	int		i;

	status = ft_itoa(get_data(NULL)->exit_status);
	status_len = ft_strlen(status);
	while (*str)
	{
		i = 0;
		status_len = ft_strlen(status);
		if (*str == '$' && str + 1 && *(str + 1) == '$' && str + 2 && *(str + 2) == '$')
		{
			//ft_printf("une fois par triplet\n");
			while (str[i] && i < status_len)
			{
				str[i] = status[i];
				i++;			
			}
			status_len = 3 - i;
			//ft_printf("status_len %d\n", status_len);
			while (str[i] && status_len--) 
				ft_delchar(&str[i]);
			continue;
		}
		str++;
	}
	free(status);
}

void	build_command_tab_node(t_ast_nde *node, t_ast_nde **cmd_tab_node,
	t_ast_nde **cmd_tab_node_sav)
{
	//if (node->token == DOLL && node->start == node->end && *node->start != '$')
	if (node->token == STAT)
	{//ft_printf("tes la ? %s\n", node->start);
		
		replace_exit_status(node->start);
		//ft_printf("tes la suite ? %s\n", node->start);
		//free(node->start);
		// node->start = ft_itoa(get_data(NULL)->exit_status);
		// node->end = node->start + ft_strlen(node->start) - 1;
		node->child->start = node->start;
		node->child->end = node->end;
	}
	add_sibling(copy_node_and_child(node), cmd_tab_node,
		cmd_tab_node_sav);
	store_and_free_cmd_tab_node_sav(*cmd_tab_node_sav);
}

/**========================================================================
 *                           launch_command_tab
 *========================================================================**/

int	launch_command_tab(t_Data *data, t_ast_nde *node,
		char *envp[], int flag)
{
	t_ast_nde	*cmd_tab_node;
	t_ast_nde	*cmd_tab_node_sav;
	char		***cmd_tab;

	cmd_tab_node_sav = NULL;
	while (node && node->token != AND && node->token != OR)
	{
		if (!flag)
			build_command_tab_node(node, &cmd_tab_node, &cmd_tab_node_sav);
		else if (node->token == STAT || node->token == DOLL)
			free(node->start);//store_and_free_exit_status_var(NULL);
		node = node->sibling;
	}
	if (cmd_tab_node_sav)
		build_command_tab(&cmd_tab, data, &cmd_tab_node_sav, envp);
	flag = data->exit_status;
	if (node && node->token == OR)
		flag = !flag;
	if (node && node->sibling)
		flag = launch_command_tab(data, node->sibling, envp, flag);
	return (flag);
}

/**========================================================================
 *                           store_and_free_cmd_tab_node_sav
 *========================================================================**/
void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav)
{
	static t_ast_nde	*cmd_tab_lcl;

	if (cmd_tab_node_sav)
		cmd_tab_lcl = cmd_tab_node_sav;
	else
		free_sibling_and_child(cmd_tab_lcl);
}

/**========================================================================
 *                           build_command_tab
 *========================================================================**/
void	build_command_tab(char ****cmd_tab, t_Data *data,
		t_ast_nde **cmd_tab_node_sav, char *envp[])
{
	(*cmd_tab) = create_command_tab(data, (*cmd_tab_node_sav), envp);
	store_and_free_cmd_tab(*cmd_tab);
	if (is_pipeline(*cmd_tab_node_sav))
	{
		free_sibling_and_child(*cmd_tab_node_sav);
		get_data(NULL)->exit_status = pipex(*cmd_tab);
	}
	else if (!command_is_builtin(*(*cmd_tab), get_data(NULL)))
	{
		free_sibling_and_child(*cmd_tab_node_sav);
		get_data(NULL)->exit_status = pipex(*cmd_tab);
	}
	else
		free_sibling_and_child(*cmd_tab_node_sav);
	free_command_tab_lg(*cmd_tab);
}

/**========================================================================
 *                           is_pipeline
 *========================================================================**/
int	is_pipeline(t_ast_nde *cmd_tab_node_sav)
{
	while (cmd_tab_node_sav)
	{
		if (cmd_tab_node_sav->token == PIPE || is_chevron(cmd_tab_node_sav))
			return (1);
		cmd_tab_node_sav = cmd_tab_node_sav->sibling;
	}
	return (0);
}
