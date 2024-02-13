/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:22:52 by dsylvain          #+#    #+#             */
/*   Updated: 2024/02/13 16:43:09 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**========================================================================
 *                           display_error
 * takes the error message as argument
 *! error message should not be longer than 1000 chars
 *========================================================================**/
void	display_error(char *str)
{
	if (write(2, str, ft_strlen(str)) == -1)
		perror("display_error\n");
}

/**========================================================================
 *                           close_minishell
 *========================================================================**/
void	close_minishell(t_Data *data)
{
	ft_printf(">>>exit\n");
	free_data(data);
}

/**========================================================================
 *                           free_data
 *========================================================================**/
void	free_data(t_Data *data)
{
	if (data->envp_tab)
		free_command_tab(data->envp_tab);
	if (data)
		free(data);
}

/**========================================================================
 *                           free_command_tab
 *========================================================================**/
void	free_command_tab(char **command_tab)
{
	int	i;

	i = 0;
	while (command_tab[i])
	{
		if (command_tab[i])
			free(command_tab[i]);
		i++;
	}
	free(command_tab);
}
