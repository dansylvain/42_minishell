/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:08:19 by dan               #+#    #+#             */
/*   Updated: 2024/02/01 17:06:33 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_export_tab(t_Data *data);

int	is_valid_var(char *export_arg)
{
	int i;

	i = 1;
	while (export_arg[i])
	{
		if (export_arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	exec_export(char **command_tab, t_Data *data)
{
	int i;
	int j;
	
	if (command_tab[1] == NULL)
		display_export_tab(data);
	i = 1;
	while (command_tab[i])
	{
		if (is_valid_var(command_tab[i]))
		{
			j = 0;
			while (data->envp_tab[j])
				j++;
			data->envp_tab[j] = (char *)ft_calloc((ft_strlen(command_tab[i]) + 1), sizeof(char));
			if (data->envp_tab[j] == NULL)
				return (0);
			ft_strlcpy(data->envp_tab[j], command_tab[i], ft_strlen(command_tab[i]) + 1);
			data->envp_tab[j + 1] = NULL;
		}
		i++;
	}
	
}

void	display_export_tab(t_Data *data)
{
	int	i;
	int j;
	int k;
	char export_tab[100][500];
	int equal_was_done;
	char temp[500];
	
	i = 0;
	while (i < 100)
		ft_bzero(export_tab[i++], 500);
	i = 0;
	while (data->envp_tab[i])
	{
		// if (data->envp_tab[i][0] == '_')
		// 	break;
		ft_strlcpy(export_tab[i], "declare -x ", 12);
		j = 0;
		k = 11;
		equal_was_done = 0;
		while(data->envp_tab[i][j])
		{
			export_tab[i][k] = data->envp_tab[i][j];
			if (data->envp_tab[i][j] == '=' && equal_was_done == 0)
			{
				equal_was_done = 1;
				export_tab[i][k++ + 1] = '"';
			}
			j++;
			k++;
		}
		export_tab[i][k++] = '"';
		export_tab[i][k] = '\0';
		i++;
	}
	i = 0;
	while (export_tab[i][0] && export_tab[i + 1][0])
	{
		if (strcmp(export_tab[i], export_tab[i + 1]) > 0)
		{
			ft_strlcpy(temp, export_tab[i], sizeof(temp));
			ft_strlcpy(export_tab[i], export_tab[i + 1], sizeof(export_tab[i]));
			ft_strlcpy(export_tab[i + 1], temp, sizeof(export_tab[i + 1]));
			i = -1;
		}
		i++;
	}
	i = 0;
	while (export_tab[i][0])
	{
		if (export_tab[i][11] != '_')
			ft_printf("%s\n", export_tab[i]);
		i++;
	}
}





int	exec_export2(char **command_tab, t_Data *data)
{
	int i;
	int j;
	int k;
	bool equal_was_done;
	char *temp;
	char envp_export_tab[100][500];
	char **temp_envp;
	
	temp_envp = duplicate_envp(data, data->envp_tab);
	if (temp_envp == NULL)
		return (0);
	
	i = 0;
	while (temp_envp[++i])
		if (ft_strncmp(temp_envp[i], "_=", 2) == 0)
			temp_envp[i] = NULL;
	i = 0;
	while (temp_envp[i] && temp_envp[i + 1])
	{
		if (ft_strncmp(temp_envp[i], temp_envp[i + 1], ft_strlen(temp_envp[i])) > 0)
		{
			temp = temp_envp[i];
			temp_envp[i] = temp_envp[i + 1];
			temp_envp[i + 1] = temp;
			i = -1;
		}
		i++;
	}
	i = 0;
	while (temp_envp[i])
	{
		equal_was_done = 0;
		j = 0;
		k = 0;
		while (temp_envp[i][j])
		{
			envp_export_tab[i][k] = temp_envp[i][j];
			if (temp_envp[i][j] == '=' && equal_was_done == 0)
			{
				k++;
				envp_export_tab[i][k] = '"';
				equal_was_done = 1;	
			}
			j++;
			k++;
		}
		envp_export_tab[i][k] = '"';
		i++;
	}
	i = 0;
	if (command_tab[1] == NULL)
		while (temp_envp[i])
			ft_printf("declare -x %s\n", envp_export_tab[i++]);
	j = 0;
	while (j > i)
	{
		free(temp_envp[j]);
		j++;
	}
	free (temp_envp);
	return (1);
}
