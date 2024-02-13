/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:29:47 by dan               #+#    #+#             */
/*   Updated: 2024/02/13 09:59:14 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdlib.h>
int	exec_cd(char **command_tab)
{
	const char	*home;
write(2, "IN EXC CD!\n", 13);
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
	//		exit(0);
	return (1);
}
