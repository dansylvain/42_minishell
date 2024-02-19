/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:22:52 by dsylvain          #+#    #+#             */
/*   Updated: 2024/02/19 20:10:33 by dan              ###   ########.fr       */
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
		perror("display_error");
}

void	display_error_detail(char *str, char *details, char *str2)
{
	char tmp[2000];
	int len = 0;
	
	ft_bzero(tmp, 2000);
	int len1 = ft_strlen(str);
	memcpy(tmp, str, len1);
	len += len1;
	int len2 = ft_strlen(details);
	memcpy(&tmp[len + 1], details, len2);
	len += len2 + 1;
	int len3 = ft_strlen(str2);
	memcpy(&tmp[len + 1], str2, len3);
	len += len3 + 1;
	if (write(2, tmp, len) == -1)
		perror("display_error");
}

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

/**========================================================================
 *                           free_command_tab_lg
 *========================================================================**/
void	free_command_tab_lg(char ***command_tab)
{
	int	i;

	i = 0;
	while (command_tab[i])
	{
		free_command_tab(command_tab[i++]);
	}
	free(command_tab);
}
