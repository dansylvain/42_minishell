/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:33:40 by dan               #+#    #+#             */
/*   Updated: 2024/02/22 10:46:00 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_pipex(t_Data *data, char *cmd, char *envp[])
{
	t_ast_nde	*cmd_list;
	t_ast_nde	*current;

	cmd_list = parse(cmd, data);
	current = cmd_list;
	while (current)
	{
		wilcard_func(current->start);
		current = current->sibling;
	}
	launch_command_tab(data, cmd_list, envp, 0);
	free_sibling_and_child(cmd_list);
}
