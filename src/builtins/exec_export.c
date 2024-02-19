/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:08:19 by dan               #+#    #+#             */
/*   Updated: 2024/02/19 19:28:10 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	are_only_valid_chars(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=' && str[i] != '\"')
			return (0);
		i++;
	}
	return (1);
}

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
			display_error("minishell: export: ", command_tab[i], ": not a valid identifier\n");
			data->exit_status = 1;
			return (0);
		}
		add_env_var_to_envp_tab(command_tab, data, &i);
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
	if (env_var && ft_strncmp(command_tab[*i], "_=", 2))
	{
		ft_strlcpy(env_var, &(command_tab[*i][j + 1]),
			ft_strlen(&(command_tab[*i][j])));
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
			return (NULL);
		ft_strlcpy(new_envp_tab[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	new_envp_tab[i] = (char *)ft_calloc((ft_strlen(env_var) + 1), sizeof(char));
	if (new_envp_tab[i] == NULL)
		return (NULL);
	ft_strlcpy(new_envp_tab[i], env_var, ft_strlen(env_var) + 1);
	free_command_tab(envp);
	return (new_envp_tab);
}

/**========================================================================
 *                           get_env_var
 *========================================================================**/
char	*get_env_var(t_Data *data, char *to_find)
{
	char	*env_var;
	int		len;
	int		j;
	char	*var;

	env_var = NULL;
	len = ft_strlen(to_find);
	j = 0;
	while (data->envp_tab[j])
	{
		var = data->envp_tab[j];
		if (!ft_strncmp(var, to_find, len) && var[len] == '=')
		{
			env_var = &var[len + 1];
			break ;
		}
		j++;
	}
	return (env_var);
}
