/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:08:19 by dan               #+#    #+#             */
/*   Updated: 2024/02/02 08:24:31 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_export_tab(t_Data *data);
int	exec_export(char **command_tab, t_Data *data);
int	is_valid_var(char *export_arg);


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




