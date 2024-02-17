/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:08:19 by dan               #+#    #+#             */
/*   Updated: 2024/02/17 14:34:32 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_valid_var(char *export_arg);
#include <stdlib.h>

void	format_export_tab(char export_tab[][500])
{
	int i;
	char str[500];

	ft_bzero(str, 500);
	i = 0;
	while (export_tab[i][0] && export_tab[i + 1][0])
	{
		if (ft_strcmp(export_tab[i], export_tab[i + 1]) > 0)
		{
			ft_strlcpy(str, export_tab[i], 500);
			ft_strlcpy(export_tab[i], export_tab[i + 1], 500);
			ft_strlcpy(export_tab[i + 1], str, 500);
			i = 0;
			continue;
		}
		i++;
	}
}

void	insert_quote(char *str)
{
	int i;
	char tmp[500];
	int	qute_dne;
	
	i = 0;
	qute_dne = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '=' && qute_dne == 0)
		{
			qute_dne = 1;
			ft_memcpy(tmp, &(str[i + 1]), 501 - i);
			ft_memcpy(&(str[i + 2]), tmp, 500 - i);
			str[i + 1] = '\"';
		}
		i++;
	}
	if (qute_dne == 1)
		str[i + 1] = '\"';
}

int	has_var(char *str)
{
	int i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	create_export_tab(t_Data *data, char export_tab[][500])
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	ft_memset(export_tab, '\0', sizeof(char) * 500 * 100);
	while (data->envp_tab[i])
	{
		if (ft_strncmp(data->envp_tab[i], "_=", 2) && has_var(data->envp_tab[i]))
		{
			ft_strlcpy(export_tab[j], data->envp_tab[i], sizeof(export_tab[i]));
			insert_quote(export_tab[j]);
			j++;
		}
		i++;
	}
	format_export_tab(export_tab);
}

void	display_export_tab(char export_tab[][500])
{
	int i;

	i = 0;
	while (export_tab[i][0])
		ft_printf("declare declare -x %s\n", export_tab[i++]);
}

char *get_env_var(t_Data *data, char *to_find)
{
	char *env_var;
	int len;
	int j;
	char *var;
	
	env_var = NULL;
	len = ft_strlen(to_find);
	j = 0;
	while (data->envp_tab[j])
	{
		var = data->envp_tab[j];
		if (!ft_strncmp(var, to_find, len) && var[len] == '=')
		{
			env_var = &var[len + 1];
			break;
		}
		j++;
	}
	return (env_var);
}

char	**create_new_env_var(char **envp, char *env_var)
{
	char **new_envp_tab;
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
		new_envp_tab[i] = (char *)ft_calloc((ft_strlen(envp[i]) + 1), sizeof(char));
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

int	exec_export(char **command_tab, t_Data *data)
{
	char export_tab[100][500];
	int	i;
	int j;
	char	var[500];
	char	*env_var;

	ft_bzero(var, 500);
	if (command_tab[1] == NULL)
	{
		create_export_tab(data, export_tab);
		display_export_tab(export_tab);
		return 0;
	}
	i = 1;
	while (command_tab[i])
	{
		
		ft_bzero(var, 500);
		j = 0;
		while (command_tab[i][j] && command_tab[i][j] != '=')
		{
			var[j] = command_tab[i][j];
			j++;
		}
		env_var = get_env_var(data, var); 
		if (env_var && ft_strncmp(command_tab[i], "_=", 2))
		{
			ft_strlcpy(env_var, &(command_tab[i][j + 1]), ft_strlen(&(command_tab[i][j])));
		}
		else if (ft_strncmp(command_tab[i], "_=", 2))
			data->envp_tab = create_new_env_var(data->envp_tab, command_tab[i]);
		i++;
	}
		
}
