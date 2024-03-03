/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:22:52 by dsylvain          #+#    #+#             */
/*   Updated: 2024/03/03 16:27:42 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**========================================================================
 *                           close_minishell
 *========================================================================**/
void	close_minishell(t_Data *data)
{
	ft_printf("exit\n");
	free_data(data);
}

/**========================================================================
 *                           free_data
 *========================================================================**/
void	free_data(t_Data *data)
{
	if (data->envp_tab)
		free_command_tab(&data->envp_tab);
	if (data)
		free(data);
}

/**========================================================================
 *                           free_command_tab
 *========================================================================**/
void	free_command_tab(char ***command_tab)
{
	int	i;

	i = 0;
	while ((*command_tab)[i])
	{
		
		// ft_printf("inner command_tab[%i]: %s\n", i, (*command_tab)[i]);
		free((*command_tab)[i]);
		(*command_tab)[i] = NULL;
		i++;
	}
	if (*command_tab)
		free(*command_tab);
	*command_tab = NULL;
}

/**========================================================================
 *                           free_command_tab_lg
 *========================================================================**/
void	free_command_tab_lg(char ***command_tab)
{
	int	i;

	i = 0;
	while (command_tab[i])
	{
		if (command_tab[i])
		{
			// ft_printf("command_tab sup[%i][1]: %s\n", i, command_tab[i][0]);
			free_command_tab(&command_tab[i]);
			command_tab[i] = NULL;	
		}
		i++;
	}
	if (command_tab)
		free(command_tab);
}
