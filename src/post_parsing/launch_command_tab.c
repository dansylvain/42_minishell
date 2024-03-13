/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/13 10:22:57 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launch_command_tab.h"
#include <test.h>
char	*rebuild_dollar_str(const t_ast_nde *operator, char *str, t_Data *data);
t_ast_nde	*rebuild_dollar_str_node(char *str, t_tok token);
#include "parsing_utils.h"
#include "libft.h"
t_Data	*get_data(char *envp[]);
/**========================================================================
 *                           launch_command_tab
 *========================================================================**/
int	launch_command_tab(t_Data *data, t_ast_nde *node,
		char *envp[], int flag)
{
	t_ast_nde	*cmd_tab_node;
	t_ast_nde	*cmd_tab_node_sav;
	char		***cmd_tab;
	//ft_printf("in flag: %d\n", flag);
	//print_node(node);
	//ft_printf("\n");
	cmd_tab_node_sav = NULL;
	while (node && node->token != AND && node->token != OR)
	{
		if (!flag)
		{
			if (node->token == DOLL && node->start == node->end && *node->start != '$')
			{
				// ft_printf("here\n");
				// print_node(node);
				// ft_printf("end here\n");	
				free(node->start);					
				node->start = ft_itoa(get_data(NULL)->exit_status);
				node->end = node->start;
				node->child->start = node->start;
				node->child->end = node->start;
				// ft_printf("here2\n");
				// print_node(node);
				// ft_printf("end here2\n");
			}				
			add_sibling(copy_node_and_child(node), &cmd_tab_node,
				&cmd_tab_node_sav);				
		}
		node = node->sibling;
	}
//	store_and_free_cmd_tab_node_sav(cmd_tab_node_sav);
	if (cmd_tab_node_sav)
		build_command_tab(&cmd_tab, data, &cmd_tab_node_sav, envp);
	flag = data->exit_status;
	if (node && node->token == OR)
		flag = !flag;
	// if (node)
	// 	print_node(node);
//	ft_printf("\n");
//	ft_printf("af flag: %d\n", flag);
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
	// ft_printf("AVANT PIPEX compa data: %d\n,", data->exit_status);
	// ft_printf("AVANT PIPEX la cmd est un ds un pipeline exit status:%d\n", get_data(NULL)->exit_status);
		free_sibling_and_child(*cmd_tab_node_sav);
		get_data(NULL)->exit_status = pipex(*cmd_tab);
		
		// ft_printf("APRES PIPEX la cmd est un ds un pipeline exit status:%d\n", get_data(NULL)->exit_status);
	}
	else if (!command_is_builtin(*(*cmd_tab), get_data(NULL)))
	{
		// ft_printf("AVANT PIPEX compa data: %d\n,",  data->exit_status);
		// ft_printf("AVANT PIPEX la cmd nest pas  ds un plpeline et nest pas un builtin exit status:%d, -%s-\n", get_data(NULL)->exit_status, ***cmd_tab);

		//ft_printf("la cmd nest pas un buitin\n");
		free_sibling_and_child(*cmd_tab_node_sav);
		get_data(NULL)->exit_status = pipex(*cmd_tab);
		
		// ft_printf("APRES PIPEX la cmd nest pas  ds un plpeline et nest pas un builtin exit status:%d, -%s-\n", get_data(NULL)->exit_status, ***cmd_tab);
	}
	else
	{
		// ft_printf("compa data: %d\n",  data->exit_status);
		// ft_printf("la cmd etait un buitin exit status:%d\n", get_data(NULL)->exit_status);
		free_sibling_and_child(*cmd_tab_node_sav);
	}
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
