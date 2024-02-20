/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:29:47 by dan               #+#    #+#             */
/*   Updated: 2024/02/20 09:20:48 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**========================================================================
 *                           exec_cd
 *========================================================================**/
int	exec_cd(t_Data *data, char **command_tab)
{
	const char	*home;

	if (data)
		data->exit_status = 1;
	if (!command_tab[1])
	{
		home = getenv("HOME");
		if (home == NULL)
			return (ft_printf("HOME env var not found\n"));
		if (chdir(home) != 0)
			return (ft_printf("problem chdir"));
		if (data)
			data->exit_status = 0;
		return (0);
	}
	if (command_tab[1] && command_tab[2])
		return (display_error("minishell: cd: too many arguments\n"), 0);
	if (chdir(command_tab[1]) != 0)
		return (display_error_detail("env: ‘", command_tab[1], "’: No such file or directory\n"), 0);
	if (data)
		data->exit_status = 0;
	return (0);
}
