/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:46:30 by dan               #+#    #+#             */
/*   Updated: 2024/02/20 10:26:42 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**========================================================================
 *                           exec_env
 *========================================================================**/
void	exec_env(t_Data *data, char **command_tab)
{
	int	i;

	if (command_tab[1] != NULL)
	{
		display_error_detail("env: ‘", command_tab[1], "’: No such file or directory\n");
		return ;
	}
	else if (!data)
	{
	}
		// display_error("no data in child\n");
	else
	{
		i = 0;
		while (data->envp_tab[i])
			ft_printf("%s\n", data->envp_tab[i++]);
	}
}
