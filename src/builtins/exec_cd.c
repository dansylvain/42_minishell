/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:29:47 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 16:22:20 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cd.h"

void	update_home_env_var(t_Data *data)
{
	char	**buffer;
	int		*i;
	int		j;

	j = 0;
	i = &j;
	buffer = (char **)ft_calloc(1, sizeof(char *));
	buffer[0] = (char *)ft_calloc(4096, sizeof (char));
	ft_strlcpy(buffer[0], "PWD=", 5);
	if (getcwd(&(buffer[0][4]), 4096 - 5) == NULL)
		perror("getcwd");
	add_env_var_to_envp_tab(buffer, data, i);
	free(buffer[0]);
	free(buffer);
}

/**========================================================================
 *                           exec_cd
 *========================================================================**/
int	exec_cd(t_Data *data, char **command_tab)
{
	const char	*home;

	if (data)
		data->exit_status = 1;
	if (!command_tab[1])
	{
		home = getenv("HOME");
		if (home == NULL)
			return (display_error("HOME env var not found\n"), 0);
		if (chdir(home) != 0)
			return (display_error("problem chdir"), 0);
		if (data)
			data->exit_status = 0;
		update_home_env_var(data);
		return (0);
	}
	if (command_tab[1] && command_tab[2])
		return (display_error("minishell: cd: too many arguments\n"), 0);
	if (chdir(command_tab[1]) != 0)
		return (display_error_detail("env: ‘", command_tab[1],
				"’: No such file or directory\n"), 0);
	if (data)
		data->exit_status = 0;
	update_home_env_var(data);
	return (0);
}
