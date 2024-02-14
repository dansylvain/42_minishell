	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   main.c                                             :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2024/01/17 14:04:56 by dan               #+#    #+#             */
	/*   Updated: 2024/02/12 11:58:29 by dan              ###   ########.fr       */
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
	void	exec_pipex(t_Data *data, char *cmd, char *envp[]);
	void	launch_command_tab(t_Data *data, t_ast_nde *node, char *envp[], int flag);
	
	/**========================================================================
	 *                             COMMENTS POLICY
	 *? signal info at the end of a function's comment block 
	*? signal info in the main comment bloc
	*? add your name at the beggining of a comment
	*---
	*TODO finish builtin export
	*TODO fix memory leaks export
	*TODO fix memory leaks unset
	*========================================================================**/

	/**========================================================================
	 *                           main.c
	 *? rl_catch_signals is a global variable (from readline lib)
	*? it is used to ignore SIGQUILL (see handle_signals.c)
	*========================================================================**/
	int	main(int argc, char **argv, char *envp[])
	{
	static t_Data	*data = NULL;

	rl_catch_signals = 0;
	if (data == NULL)
		data = (t_Data *)ft_calloc(sizeof(t_Data), 1);
	if (data == NULL)
		return (display_error("Error\n"), 255);
	data->envp_tab = duplicate_envp(data, envp);
	if (!data->envp_tab)
		return (display_error("Error\n"), free_data(data), 255);
	if (argc != 1)
		return (free_data(data), display_error("Usage: ./minishell\n"), 255);
	handle_signals();
	if (prompt_loop(data, envp) == 0)
		return (free_data(data), 0);
	return (0);
	}

	void build_prompt(char prompt[]) {
	char cwd[1024];
	char *home;

	home = getenv("HOME");
	ft_strlcpy(prompt, "minishell: ", 12);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		char *shortened_cwd = strstr(cwd, home);
		if (shortened_cwd != NULL)
			strcat(prompt, shortened_cwd + strlen(home));
		else
			strcat(prompt, cwd);
	}
	else
		perror("getcwd");
	strcat(prompt, "$ ");
	}


	/**========================================================================
	 *                           
	 * possibility to add the path before prompt with this function
	 * (write a function "build_prompt")
	 * prompt = getcwd(NULL, 0);
	 *========================================================================**/
	int	prompt_loop(t_Data *data, char *envp[])
	{
	char	*cmd[2];
	char	prompt[1024];

	ft_bzero(prompt, 1024);
	// build_prompt(prompt);
	cmd[1] = NULL;
	while (1)
	{
		// cmd[0] = readline(prompt);
		cmd[0] = readline("minishell : ");
		if (cmd[0] && *cmd[0])
			add_history(cmd[0]);
		if (cmd[0] == NULL)
			return (ft_printf("exit\n"), 0);
		exec_pipex(data, cmd[0], data->envp_tab);
		// ft_printf("exit_status: %i\n", data->exit_status);
		
		free(cmd[0]);
	}
	return (1);
	}

	/**========================================================================
	 *                           command_is_builtin
	 * exit builtin implemented without extern function
	 * 0 is returned, and the data struct is freed in calling function
	 *========================================================================**/
	int	command_is_builtin(char	*cmd_tab[], t_Data *data, char *envp[])
	{
	int		return_pipex;

	if (!cmd_tab)
	{
		// ft_putstr_fd("commande is nul a chier fd\n", 2);
		// ft_printf("commande is nul a chier\n");
		return (1);
	}
	if (!cmd_tab[0])
	{
		// ft_putstr_fd("premier element de com is nul a chier fd\n", 2);
		// ft_printf("premier element de com is nul a chier\n");
		return (free_command_tab(cmd_tab), 1);
	} 
	// ft_putstr_fd(*cmd_tab, 2);
	// ft_putstr_fd("\n", 2);
	//ft_printf("on est avant le test buitin, is %s\n", cmd_tab[0]);
	if (!ft_strncmp(&(cmd_tab[0][ft_strlen(cmd_tab[0]) - 4]), "echo", 5))
		return (exec_echo(data, cmd_tab), 1);
	if (!ft_strncmp(&(cmd_tab[0][ft_strlen(cmd_tab[0]) - 5]), "unset", 6))
		return (exec_unset(data, cmd_tab), 1);
	if (!ft_strncmp(&(cmd_tab[0][ft_strlen(cmd_tab[0]) - 6]), "export", 7))
		return (exec_export(cmd_tab, data), 1);
	if (!ft_strncmp(&(cmd_tab[0][ft_strlen(cmd_tab[0]) - 3]), "env", 4))
		return (exec_env(data, cmd_tab), 1);
	if (!ft_strncmp(&(cmd_tab[0][ft_strlen(cmd_tab[0]) - 3]), "pwd", 4))
		return(exec_pwd(data), 1);
	if (!ft_strncmp(&(cmd_tab[0][ft_strlen(cmd_tab[0]) - 2]), "cd", 3))
		return (exec_cd(data, cmd_tab), 1);
	if (!ft_strncmp(&(cmd_tab[0][ft_strlen(cmd_tab[0]) - 4]), "exit", 5))
		return (exit(1), 1); //ft_putstr_fd("builtin\n", 2);
	//free_command_tab(cmd_tab);
	return (0);
	}

	/**========================================================================
	 *                           duplicate_envp
	 *========================================================================**/
	char	**duplicate_envp(t_Data *data, char *envp[])
	{
	char	**envp_tab;
	int		i;

	// ft_printf("CREATE ENVP!\n");
	i = 0;
	while (envp[i])
		i++;
	envp_tab = (char **)ft_calloc(i + 1, sizeof(char *));
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
