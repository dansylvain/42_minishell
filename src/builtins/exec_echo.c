/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:43:09 by dan               #+#    #+#             */
/*   Updated: 2024/02/19 14:01:10 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**========================================================================
 *                           exec_echo
 *========================================================================**/
void	exec_echo(t_Data *data, char **command_tab)
{
	int	i;
	int	j;

	i = 1;
	if (!command_tab[1] || is_only_space(command_tab[1]))
	{
		ft_printf("\n");
		return ;
	}
	if (!ft_strncmp(command_tab[1], "-n", 3))
		i = 2;
	j = i;
	while (command_tab[i])
	{
		ft_printf("%s", command_tab[i++]);
		if (command_tab[i] && command_tab[i][0])
			ft_printf(" ");
	}
	if (j == 1)
		ft_printf("\n");
	if (data)
		data->exit_status = 0;
}

/**========================================================================
 *                           is_only_space
 *========================================================================**/
int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
