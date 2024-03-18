/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:43:09 by dan               #+#    #+#             */
/*   Updated: 2024/03/18 05:29:05 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_echo.h"

void	initial_conditions(char **command_tab, int *i)
{
	if (!command_tab[1] || is_only_space(command_tab[1]))
	{
		ft_printf("\n");
		return ;
	}
	if (command_tab[*i] && !ft_strncmp(command_tab[*i], "-n", 3))
	{
		while (command_tab[*i] && !ft_strncmp(command_tab[*i], "-n", 3))
			(*i)++;
	}
}

/**========================================================================
 *                           exec_echo
 *========================================================================**/
void	exec_echo(t_Data *data, char **command_tab)
{
	int	i;
	int	j;

	i = 1;
	initial_conditions(command_tab, &i);
	j = i;
	while (command_tab[i])
	{
		ft_printf("%s", command_tab[i++]);
		if (command_tab[i] && command_tab[i][0])
			ft_printf(" ");
	}
	if (j == 1)
		ft_printf("\n");
	data = get_data(NULL);
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

/**========================================================================
 *                           is_empty_prompt
 *========================================================================**/
int	is_not_empty_prompt(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str && str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isspace(str[i]) && str[i] != '\'' && str[i] != '\"')
			return (0);
		i++;
	}
	return (1);
}
