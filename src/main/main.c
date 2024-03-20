/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:04:56 by dan               #+#    #+#             */
/*   Updated: 2024/03/19 10:54:14 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**========================================================================
 *                             COMMENTS POLICY
*? add your name at the beggining of a comment
 *? signal info at the end of a function's comment block 
*? signal info in the main comment bloc
*---
*========================================================================**/

/**========================================================================
 *                           main.c
 *? rl_catch_signals is a global variable (from readline lib)
*? it is used to ignore SIGQUILL (see handle_signals.c)
*========================================================================**/
int	main(int argc, char **argv, char *envp[])
{
	t_Data	*data;

	if (argc != 1)
		return (display_error("Usage: ./minishell\n"), 255);
	data = get_data(envp);
	if (data == NULL)
		return (display_error("Error\n"), 255);
	handle_signals();
	rl_catch_signals = 0;
	if (prompt_loop(data, envp) == 0)
		return (free_data(data), 0);
	return (0);
	(void)argv;
}

/**========================================================================
 *                           get_data
 *========================================================================**/
t_Data	*get_data(char *envp[])
{
	static t_Data	*data = NULL;

	if (data == NULL)
	{
		data = (t_Data *)ft_calloc(sizeof(t_Data), 1);
		if (data == NULL)
			return (NULL);
		data->envp_tab = duplicate_envp(data, envp);
		if (!data->envp_tab)
			return (free(data), NULL);
	}
	return (data);
}

/**========================================================================
 *                           prompt_loop
 *========================================================================**/
int	prompt_loop(t_Data *data, char *envp[])
{
	char	*cmd;
	char	prompt[1024];

	cmd = NULL;
	while (1)
	{
		build_prompt(prompt);
		cmd = readline(prompt);
		if (cmd && *cmd)
			add_history(cmd);
		if (cmd == NULL)
			return (ft_printf("exit\n"), 0);
		exec_pipex(data, cmd, data->envp_tab);
		free(cmd);
	}
	return (1);
	(void)envp;
}

/**========================================================================
 *                           build_prompt
 *========================================================================**/
void	build_prompt(char prompt[])
{
	char	cwd[1024];
	char	*home;
	char	*shortened_cwd;

	home = getenv("HOME");
	ft_strlcpy(prompt, "minishell: ", 18);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		shortened_cwd = ft_strstr(cwd, home);
		if (shortened_cwd != NULL)
		{
			ft_strcat(prompt, shortened_cwd + ft_strlen(home));
		}
		else
			ft_strcat(prompt, cwd);
	}
	else
		perror("getcwd");
	ft_strcat(prompt, " $ ");
}

/**========================================================================
 *                           command_is_builtin
 * exit builtin implemented without extern function
 * 0 is returned, and the data struct is freed in calling function
 *========================================================================**/
int	command_is_builtin(char	**cmd_tab, t_Data *data)
{
	int	len;

	len = ft_strlen(cmd_tab[0]);
	if (!cmd_tab || is_only_space(cmd_tab[0]))
		return (1);
	if (!cmd_tab[0])
		return (free_command_tab(&cmd_tab), 1);
	if (len >= 2 && !ft_strncmp(&(cmd_tab[0][len - 2]), "cd", 3))
		return (exec_cd(data, cmd_tab), 1);
	if (len >= 3 && !ft_strncmp(&(cmd_tab[0][len - 3]), "env", 4))
		return (exec_env(data, cmd_tab), 1);
	if (len >= 3 && !ft_strncmp(&(cmd_tab[0][len - 3]), "pwd", 4))
		return (exec_pwd(data), 1);
	if (len >= 4 && !ft_strncmp(&(cmd_tab[0][len - 4]), "echo", 5))
		return (exec_echo(data, cmd_tab), 1);
	if (len >= 4 && !ft_strncmp(&(cmd_tab[0][len - 4]), "exit", 5))
		(exec_exit(data, cmd_tab));
	if (len >= 5 && !ft_strncmp(&(cmd_tab[0][len - 5]), "unset", 6))
		return (exec_unset(data, cmd_tab), 1);
	if (len >= 6 && !ft_strncmp(&(cmd_tab[0][len - 6]), "export", 7))
		return (exec_export(cmd_tab, data), 1);
	return (0);
}
