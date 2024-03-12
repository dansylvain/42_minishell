/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:43:46 by dan               #+#    #+#             */
/*   Updated: 2024/03/12 09:06:28 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_command_tab.h"

/**========================================================================
 *                           store_and_free_cmd_tab
 *========================================================================**/
void	store_and_free_cmd_tab(char ***cmd_tab)
{
	static char	***cmd_tab_lcl;

	if (cmd_tab)
		cmd_tab_lcl = cmd_tab;
	else
		free_command_tab_lg(cmd_tab_lcl);
}

int	alloc_memo(char *****cmd_tab, int lstsize, int *i, int *j)
{
	(**cmd_tab)[*i] = (char **)ft_calloc(lstsize + 1, sizeof (char *));
	if ((**cmd_tab)[*i] == NULL)
		return (0);
	*j = 0;
	while (*j < lstsize)
	{
		(**cmd_tab)[*i][*j] = (char *)ft_calloc(100, sizeof (char));
		if ((**cmd_tab)[*i][*j] == NULL)
			return (0);
		(*j)++;
	}
	(*i)++;
	return (1);
}

int	alloc_memory_for_command_tab(t_ast_nde *node, char ****cmd_tab)
{
	int	lstsize;
	int	i;
	int	j;

	lstsize = 0;
	while (node)
	{
		lstsize++;
		node = node->sibling;
	}
	*cmd_tab = (char ***)ft_calloc(lstsize + 1, sizeof (char **));
	if (*cmd_tab == NULL)
		return (0);
	i = 0;
	while (i < lstsize)
	{
		if (alloc_memo(&cmd_tab, lstsize, &i, &j) == 0)
			return (0);
	}
	return (1);
}

/**========================================================================
 *                           create_command_tab
 *========================================================================**/
char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[])
{
	char		***cmd_tab;
	int			cmd_nbr;

	if (alloc_memory_for_command_tab(node, &cmd_tab) == 0)
		free_command_tab_lg(cmd_tab);
	cmd_tab = fill_cmd_tab_tabs(data, node, cmd_tab);
	return (cmd_tab);
	(void)cmd_nbr;
	(void)envp;
}
