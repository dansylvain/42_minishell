/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:29:47 by dan               #+#    #+#             */
/*   Updated: 2024/02/13 19:49:13 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdlib.h>
int		exec_cd(t_Data *data, char **command_tab)
{
	const char	*home;
	data->exit_status = 1;
	if (!command_tab[1])
	{
		home = getenv("HOME");
		if (home == NULL)
			return (ft_printf("HOME env var not found\n"));
		if (chdir(home) != 0)
			return (ft_printf("problem chdir"));
		data->exit_status = 0;
		return ;
	}
	if (command_tab[1] && command_tab[2])
		return (ft_printf("minishell: cd: too many arguments\n"));
	if (chdir(command_tab[1]) != 0)
		return (ft_printf
			("minishell: cd: %s: No such file or directory\n", command_tab[1]));
	data->exit_status = 0;
	return ;
}
