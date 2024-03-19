/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/17 11:23:50 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_command_tab.h"

/**========================================================================
 *                           store_and_free_cmd_tab
 *! FUNCTION TO REMOVE BEFORE END OF PROJECT 
 *========================================================================**/
void	store_and_free_cmd_tab(char ***cmd_tab)
{
	static char	***cmd_tab_lcl;

	if (cmd_tab)
		cmd_tab_lcl = cmd_tab;
	else
		free_command_tab_lg(cmd_tab_lcl);
}

/**========================================================================
 *                           display_command_tab
 *! FUNCTION TO REMOVE BEFORE END OF PROJECT 
 *========================================================================**/
void	display_command_tab(char ***cmd_tab)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_tab && cmd_tab[i])
	{
		j = 0;
		while (cmd_tab && cmd_tab[i] && cmd_tab[i][j])
		{
			ft_printf("cmd_tab[%i][%i]: %s\n", i, j, cmd_tab[i][j]);
			j++;
		}
		i++;
	}
}

/**========================================================================
 *                           create_command_tab
 *========================================================================**/
char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
{
	char	***cmd_tab;
	int		pipe_parts_nbr;
	char	*tmp;

	cmd_tab = NULL;
	pipe_parts_nbr = get_pipe_parts_nbr(&node);
	cmd_tab = alloc_memory_for_pipe_parts(cmd_tab, pipe_parts_nbr);
	if (is_not_empty_prompt(node->child->start))
	{
		tmp = get_node_str(node->child);
		display_error_detail("", tmp, " : command not found\n");
		data->exit_status = 127;
		free(tmp);
		cmd_tab[0] = ft_calloc(2, sizeof(char *));
		cmd_tab[1] = NULL;
		cmd_tab[0][0] = ft_strdup("");
		return (cmd_tab);
	}
	fill_command_tab(cmd_tab, node);
	return (cmd_tab);
	(void)data;
	(void)envp;
}
