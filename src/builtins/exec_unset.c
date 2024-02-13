/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:09:58 by dan               #+#    #+#             */
/*   Updated: 2024/02/13 10:29:38 by seblin           ###   ########.fr       */
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

void	exec_unset(char *envp[], char **command_tab)
{
	int	i;
	int	j;
write(2, "IN EXC unset!\n", 13);
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
	//exit(0);
}
