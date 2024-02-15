/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:43:09 by dan               #+#    #+#             */
/*   Updated: 2024/02/15 17:01:32 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_echo(t_Data *data, char **command_tab)
{
	int	i;
	int	j;
 //write(2, "IN EXC ECHO!\n", 13);
	i = 1;
	if (!command_tab[1])
		return ;
	if (!ft_strncmp(command_tab[1], "-n", 3))
		i = 2;
	j = i;
	while (command_tab[i])
	{
		ft_printf("%s", command_tab[i++]);
		if (command_tab[i])
			ft_printf(" ");
	}
	if (j == 1)
		ft_printf("\n");
	if (data)
		data->exit_status = 0;	
}
