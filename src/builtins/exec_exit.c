/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:30:35 by dan               #+#    #+#             */
/*   Updated: 2024/03/03 16:27:36 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	store_and_free_cmd_list(t_ast_nde *cmd_list);
void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);
void	store_and_free_cmd_tab(char ***cmd_tab);

/**========================================================================
 *                           exec_exit
 *========================================================================**/
int	exec_exit(t_Data *data, char **command_tab)
{
	int exit_int;
	data->exit_status = 0;
	ft_printf("exit\n");
	if (command_tab[1])
	{
		if (!str_is_digit(command_tab[1]))
		{
			display_error_detail("minishell: exit: ", command_tab[1],
				": numeric argument required\n");
			data->exit_status = 2;
		}
		else
			data->exit_status = ft_atoi(command_tab[1]);
		if (str_is_digit(command_tab[1]) && command_tab[2])
		{
			display_error("minishell: exit: too many arguments\n");
			data->exit_status = 1;
		}
	}
	free_command_tab(&command_tab);	
	command_tab = NULL;
	store_and_free_cmd_tab_node_sav(NULL);
	store_and_free_cmd_list(NULL);
	exit_int = data->exit_status;
	free_data(data);
	// store_and_free_cmd_tab(NULL);
	exit(exit_int);
}

/**========================================================================
 *                           str_is_digit
 *========================================================================**/
int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[0]) && str[0] != '+' && str[0] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
