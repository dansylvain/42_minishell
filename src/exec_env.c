/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:46:30 by dan               #+#    #+#             */
/*   Updated: 2024/01/26 18:00:22 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_env(char **envp, char **command_tab)
{
	int	i;

	if (command_tab[1] != NULL)
	{
		ft_printf("env: ‘%s’: No such file or directory\n", command_tab[1]);
		return ;
	}
	else
	{
		i = 0;
		while (envp[i])
			ft_printf("%s\n", envp[i++]);
	}
}
