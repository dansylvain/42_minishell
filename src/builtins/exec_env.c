/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:46:30 by dan               #+#    #+#             */
/*   Updated: 2024/02/19 14:07:35 by dan              ###   ########.fr       */
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
		ft_printf("env: ‘%s’: No such file or directory\n", command_tab[1]);
		return ;
	}
	else if (!data)
		ft_printf("no data in child\n");
	else
	{
		i = 0;
		while (data->envp_tab[i])
			ft_printf("%s\n", data->envp_tab[i++]);
	}
}
