/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:33:40 by dan               #+#    #+#             */
/*   Updated: 2024/02/18 18:30:22 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"

char		**parse_cmd(char **command, char **env);
void		tmp_main(void);
void		display_command_tab(char **command_tab);
int			pipex(char **argv[], char *envp[]);
t_ast_nde	*parse(char *str, t_Data *data);
char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[]);
void	display_command_tab_big(char ***command_tab);
void	launch_command_tab(t_Data *data, t_ast_nde *node, char *envp[], int flag);
int	has_wildcard(char *str);
int wilcard_func(char *pattern);
void	free_tree(t_ast_nde *node);

void	exec_pipex(t_Data *data, char *cmd, char *envp[])
{
	t_ast_nde *cmd_list;

	cmd_list = parse(cmd, data);
	t_ast_nde *current;
	current = cmd_list;
	while (current)
	{
		wilcard_func(current->start);
		current = current->sibling;	
	}
	launch_command_tab(data, cmd_list, envp, 0);
	free_sibling_and_child(cmd_list);
}