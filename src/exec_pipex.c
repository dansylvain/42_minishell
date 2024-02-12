/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:33:40 by dan               #+#    #+#             */
/*   Updated: 2024/02/12 21:55:49 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"

char		**parse_cmd(char **command, char **env);
void		tmp_main(void);
void		display_command_tab(char **command_tab);
int			pipex(char **argv[], char *envp[]);
t_ast_nde	*parse(char *str);
char	***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[]);
void	display_command_tab_big(char ***command_tab);
void	launch_command_tab(t_Data *data, t_ast_nde *node, char *envp[], int flag);

void	exec_pipex2(t_Data *data, char *cmd, char *envp[])
{
	char	***cmd_tab;
	int exit_status;

	cmd_tab = create_command_tab(data, parse(cmd), envp);
	display_command_tab_big(cmd_tab);
	exit_status = pipex(cmd_tab, envp);
}

void	exec_pipex(t_Data *data, char *cmd, char *envp[])
{
	//char	***cmd_tab;
	//int exit_status;

	//cmd_tab = 
	launch_command_tab(data, parse(cmd), envp, 0);
//	exit(1);
	//display_command_tab_big(cmd_tab);
	//exit_status = pipex(cmd_tab, envp);
}