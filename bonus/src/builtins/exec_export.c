/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:08:19 by dan               #+#    #+#             */
/*   Updated: 2024/03/09 12:50:52 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_export.h"

/**========================================================================
 *                           exec_export
 *========================================================================**/
int	exec_export(char **command_tab, t_Data *data)
{
	char	export_tab[100][500];
	int		i;

	if (command_tab[1] == NULL)
	{
		create_export_tab(data, export_tab);
		display_export_tab(export_tab);
		return (0);
	}
	i = 1;
	while (command_tab[i])
	{
		if (!are_only_valid_chars(command_tab[i]))
		{
			display_error_detail("minishell: export: `", command_tab[i],
				"': not a valid identifier\n");
			data->exit_status = 1;
			return (0);
		}
		add_env_var_to_envp_tab(command_tab, data, &i);
		i++;
	}
	return (0);
}

/**========================================================================
 *                           realloc_env_var
 *========================================================================**/
void	realloc_env_var(t_Data *data, char var[], char *new_var_command)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (data->envp_tab[i])
	{
		if (!ft_strncmp(var, data->envp_tab[i], len) && var[len - 1] == '=')
		{
			free(data->envp_tab[i]);
			data->envp_tab[i] = (char *)malloc(len
					+ ft_strlen(new_var_command) + 2);
			ft_strlcpy(data->envp_tab[i], var, len);
			ft_strcat(data->envp_tab[i], "=");
			ft_strcat(data->envp_tab[i], new_var_command);
			break ;
		}
		i++;
	}
}

/**========================================================================
 *                      add_env_var_to_envp_tab
 *========================================================================**/
void	add_env_var_to_envp_tab(char **command_tab, t_Data *data, int *i)
{
	int		j;
	char	var[500];
	char	*env_var;

	ft_bzero(var, 500);
	j = 0;
	while (command_tab[*i][j] && command_tab[*i][j] != '=')
	{
		var[j] = command_tab[*i][j];
		j++;
	}
	env_var = get_env_var(data, var);
	if (command_tab[*i][j] == '=')
		var[j++] = '=';
	else
	{
		data->envp_tab = create_new_env_var(data->envp_tab, command_tab[*i]);
		return ;
	}
	if (env_var && ft_strncmp(command_tab[*i], "_=", 2))
	{
		realloc_env_var(data, var, command_tab[*i] + ft_strlen(var));
	}
	else if (ft_strncmp(command_tab[*i], "_=", 2))
		data->envp_tab = create_new_env_var(data->envp_tab, command_tab[*i]);
}

/**========================================================================
 *                           create_new_env_var
 *========================================================================**/
char	**create_new_env_var(char **envp, char *env_var)
{
	char	**new_envp_tab;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp_tab = (char **)ft_calloc(i + 2, sizeof(char *));
	if (new_envp_tab == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp_tab[i] = (char *)ft_calloc((ft_strlen(envp[i]) + 1),
				sizeof(char));
		if (new_envp_tab[i] == NULL)
			return (free_command_tab(&new_envp_tab), NULL);
		ft_strlcpy(new_envp_tab[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	new_envp_tab[i] = (char *)ft_calloc((ft_strlen(env_var) + 1), sizeof(char));
	if (new_envp_tab[i] == NULL)
		return (free_command_tab(&new_envp_tab), NULL);
	ft_strlcpy(new_envp_tab[i++], env_var, ft_strlen(env_var) + 1);
	new_envp_tab[i] = NULL;
	return (free_command_tab(&envp), new_envp_tab);
}
