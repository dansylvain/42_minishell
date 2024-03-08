/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:46:30 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 16:23:04 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_env.h"

/**========================================================================
 *                           exec_env
 *========================================================================**/
void	exec_env(t_Data *data, char **command_tab)
{
	int	i;

	if (command_tab[1] != NULL)
	{
		display_error_detail("env: ", command_tab[1],
			"’: No such file or directory\n");
		if (data)
			data->exit_status = 126;
		if (waitpid(-1, NULL, WNOHANG) != -1)
			exit(42);
		return ;
	}
	else
	{
		i = 0;
		if (data)
		{
			while (data->envp_tab[i])
				ft_printf("%s\n", data->envp_tab[i++]);
		}
	}
	if (data)
		data->exit_status = 0;
}
