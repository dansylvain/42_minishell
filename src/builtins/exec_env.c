/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:46:30 by dan               #+#    #+#             */
/*   Updated: 2024/02/20 11:06:40 by dan              ###   ########.fr       */
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
		display_error_detail("env: ‘", command_tab[1],
			"’: No such file or directory\n");
		return ;
	}
	else if (!data)
	{
	}
	else
	{
		i = 0;
		while (data->envp_tab[i])
			ft_printf("%s\n", data->envp_tab[i++]);
	}
}
