/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:09:58 by dan               #+#    #+#             */
/*   Updated: 2024/02/11 07:54:09 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
void	unset_var(char *envp[], int i)
{write(2, "IN EXC unset!\n", 13);
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

void	exec_unset(char *envp[], char **command_tab)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 1;
		while (command_tab[j] && ft_strncmp(envp[i], "_=", 2))
		{
			if ((!ft_strncmp(command_tab[j], envp[i], ft_strlen
						(command_tab[j]))) && envp[i][ft_strlen
				(command_tab[j])] == '=')
			{
				unset_var(envp, i);
				exec_unset(envp, command_tab);
			}
			j++;
		}
		i++;
	}
}
