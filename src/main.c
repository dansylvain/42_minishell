/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:04:56 by dan               #+#    #+#             */
/*   Updated: 2024/02/01 13:03:57 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
char **parse_cmd(char **command, char **env);
// void	tmpmain();
/**========================================================================
 *                             COMMENTS POLICY
 *? signal info at the end of a function's comment block 
 *? signal info in the main comment bloc
 *? add your name at the beggining of a comment
 *---
 *! lors du parsing, si une commande n'est pas trouvée, l'algo de parsing
 *! quitte le programme => l'application est fermée
 *! erreur renvoyée par minishell: "pouetpouet: No such file or directory"
 *========================================================================**/
/**========================================================================
 *                           main.c
 *? rl_catch_signals is a global variable (from readline lib)
 *? it is used to ignore SIGQUILL (see handle_signals.c)
*========================================================================**/
int	main(int argc, char **argv, char *envp[])
{
	t_Data	*data;
	
	data = (t_Data *)malloc(sizeof(t_Data));
	if (data == NULL)
		return (display_error("Error\n"), free_data(data), 255);
	data->envp_tab = duplicate_envp(data, envp);

	if (!data->envp_tab)
		return (display_error("Error\n"), free_data(data), 255);
	rl_catch_signals = 0;
	if (argc != 1)
		return (free_data(data), display_error("Usage: ./minishell\n"), 255);
	handle_signals();
	if (prompt_loop(data, envp) == 0)
		return (free_data(data), 255);
	return (0);
}

/**========================================================================
 *                           
 * possibility to add the path before prompt with this function
 * (write a function "build_prompt")
 * prompt = getcwd(NULL, 0);
 *========================================================================**/
int	prompt_loop(t_Data *data, char *envp[])
{
	char	*command;
	char	*prompt;

	command = NULL;
	while (1)
	{
		command = readline("minishell> ");
		if (command && *command)
		{
			add_history(command);
		}
		if (command == NULL)
			return (ft_printf("exit\n"), 0);
		if (command_is_builtin(command, data, envp) == 0)
			return (free(command), 0);
		if (command)
			free(command);
	}
	return (1);
}

/**========================================================================
 *                           command_is_builtin
 * exit builtin implemented without extern function
 * 0 is returned, and the data struct is freed in calling function
 *========================================================================**/
int	command_is_builtin(char *command, t_Data *data, char *envp[])
{
	char	**command_tab;
	char	*cmd[2];
	
	cmd[0] = command;
	cmd[1] = NULL;
	command_tab = NULL;
	command_tab = parse_cmd(cmd, data->envp_tab);
	if (!command_tab)
		return (1);
	if (!command_tab[0])
		return (free(command_tab), 1);
	if (!ft_strncmp(&(command_tab[0][ft_strlen(command_tab[0]) - 4]), "echo", 5))
		exec_echo(command_tab);
	if (!ft_strncmp(&(command_tab[0][ft_strlen(command_tab[0]) - 5]), "unset", 6))
		exec_unset(data->envp_tab, command_tab);
	if (!ft_strncmp(&(command_tab[0][ft_strlen(command_tab[0]) - 6]), "export", 7))
		exec_export(command_tab, data);
	if (!ft_strncmp(&(command_tab[0][ft_strlen(command_tab[0]) - 3]), "env", 4))
		exec_env(data->envp_tab, command_tab);
	if (!ft_strncmp(&(command_tab[0][ft_strlen(command_tab[0]) - 3]), "pwd", 4))
		exec_pwd();
	if (!ft_strncmp(&(command_tab[0][ft_strlen(command_tab[0]) - 2]), "cd", 3))
		exec_cd(command_tab);
	if (!ft_strncmp(&(command_tab[0][ft_strlen(command_tab[0]) - 4]), "exit", 5))
		return (free_command_tab(command_tab), 0);
	free_command_tab(command_tab);
	return (1);
}

char	**duplicate_envp(t_Data *data, char *envp[])
{
	char	**envp_tab;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	envp_tab = (char **)ft_calloc((i + 1), sizeof(char *));
	if (envp_tab == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_tab[i] = (char *)ft_calloc((ft_strlen(envp[i]) + 1), sizeof(char));
		if (envp_tab[i] == NULL)
			return (NULL);
		ft_strlcpy(envp_tab[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	envp_tab[i] = NULL;
	return (envp_tab);
}
