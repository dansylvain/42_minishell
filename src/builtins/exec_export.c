/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:08:19 by dan               #+#    #+#             */
/*   Updated: 2024/01/27 09:14:48 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_export(char **command_tab, t_Data *data)
{
	int i;
	int j;
	int k;
	bool equal_was_done;
	char *temp;
	char envp_export_tab[100][500];
	char **temp_envp;
	
	temp_envp = duplicate_envp(data, data->envp);
	if (temp_envp == NULL)
		return (0);
	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 500)
		{
			envp_export_tab[i][j++] = '\0';
		}
		i++;
	}
	
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
