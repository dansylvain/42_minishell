/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:29:47 by dan               #+#    #+#             */
/*   Updated: 2024/01/27 09:14:29 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cd(char **command_tab)
{
	const char	*home;

	if (!command_tab[1])
	{
		home = getenv("HOME");
		if (home == NULL)
			return (ft_printf("HOME env var not found\n"), 0);
		if (chdir(home) != 0)
			return (ft_printf("chdir"), 1);
		return (1);
	}
	if (command_tab[1] && command_tab[2])
		return (ft_printf("minishell: cd: too many arguments\n"), 1);
	if (chdir(command_tab[1]) != 0)
		return (ft_printf
			("minishell: cd: %s: No such file or directory\n", command_tab[1]));
	return (1);
}
