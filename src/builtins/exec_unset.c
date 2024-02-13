/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:09:58 by dan               #+#    #+#             */
/*   Updated: 2024/02/13 17:06:04 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
void	unset_var(char *envp[], int i)
{
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

void	exec_unset(t_Data *data, char **command_tab)
{
	int	i;
	int	j;
write(2, "IN EXC unset!\n", 13);
	i = 0;
	while (data->envp_tab[i])
	{
		j = 1;
		while (command_tab[j] && ft_strncmp(data->envp_tab[i], "_=", 2))
		{
			if ((!ft_strncmp(command_tab[j], data->envp_tab[i], ft_strlen
						(command_tab[j]))) && data->envp_tab[i][ft_strlen
				(command_tab[j])] == '=')
			{
				unset_var(data->envp_tab, i);
				exec_unset(data, command_tab);
			}
			j++;
		}
		i++;
	}
}
