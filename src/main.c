/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:04:56 by dan               #+#    #+#             */
/*   Updated: 2024/02/18 17:50:07 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"

char		**parse_cmd(char **command, char **env);
void		tmp_main(void);
void		display_command_tab(char **command_tab);
int			pipex(char **argv[], char *envp[]);
t_ast_nde	*parse(char *str);
char		***create_command_tab(t_Data *data, t_ast_nde *node, char *envp[]);
void		display_command_tab_big(char ***command_tab);
void		exec_pipex(t_Data *data, char *cmd, char *envp[]);
void		launch_command_tab(t_Data *data, t_ast_nde *node,
				char *envp[], int flag);
int			exec_exit(t_Data *data, char **command_tab);
char	*get_next_line(int fd);


/**========================================================================
 *                             COMMENTS POLICY
 *? signal info at the end of a function's comment block 
*? signal info in the main comment bloc
*? add your name at the beggining of a comment
*---
*! found free risponsible for invalid free error in file parsing_path.c
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

void	build_prompt(char prompt[])
{
	char	cwd[1024];
	char	*home;
	char	*shortened_cwd;

	home = getenv("HOME");
	ft_strlcpy(prompt, "\033[1;33mminishell: \033[0m", 18);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		shortened_cwd = strstr(cwd, home);
		if (shortened_cwd != NULL)
		{
			ft_strcat(prompt, "\033[1;37m");
			ft_strcat(prompt, shortened_cwd + strlen(home));
			ft_strcat(prompt, "\033[0m");
		}
		else
			ft_strcat(prompt, cwd);
	}
	else
		perror("getcwd");
	ft_strcat(prompt, "\033[1;36m $\033[0m ");
}

/**========================================================================
 *                           prompt_loop
 *========================================================================**/

int	prompt_loop(t_Data *data, char *envp[])
{
	char	*cmd[2];
	char	prompt[1024];

	cmd[1] = NULL;
	while (1)
	{
		// build_prompt(prompt);
		// cmd[0] = readline(prompt);
		// ft_printf("%s", prompt);
		char *gnl_output = get_next_line(0);
		gnl_output[ft_strlen(gnl_output) - 1] = '\0';
		cmd[0] = gnl_output;
		if (cmd[0] && *cmd[0])
			add_history(cmd[0]);
		if (cmd[0] == NULL)
			return (ft_printf("exit\n"), 0);
		exec_pipex(data, cmd[0], data->envp_tab);
		free(cmd[0]);
	}
	return (1);
}

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
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
	int	return_pipex;
	int	len;
	
	len = ft_strlen(cmd_tab[0]);
	if (!cmd_tab)
		return (1);
	if (!cmd_tab[0])
		return (free_command_tab(cmd_tab), 1);
	if (is_only_space(cmd_tab[0]))
		return (1);
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

char	**update_shlvl(char	**envp_tab)
{
	int		i;
	int		shlvl;
	char	*new_shlvl;

	i = 0;
	while (envp_tab[i])
	{
		if (!ft_strncmp(envp_tab[i], "SHLVL=", 6))
		{
			shlvl = ft_atoi(&(envp_tab[i][6]));
			shlvl++;
			new_shlvl = ft_itoa(shlvl);
			ft_strlcpy(&envp_tab[i][6], new_shlvl, ft_strlen (new_shlvl) + 1);
			free(new_shlvl);
		}
		i++;
	}
}

/**========================================================================
 *                           duplicate_envp
 *========================================================================**/
char	**duplicate_envp(t_Data *data, char *envp[])
{
	char	**envp_tab;
	int		i;

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
	update_shlvl(envp_tab);
	return (envp_tab);
}
