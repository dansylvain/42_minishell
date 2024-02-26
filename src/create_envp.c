/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:33:25 by dan               #+#    #+#             */
/*   Updated: 2024/02/26 09:21:44 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_shlvl(char	**envp_tab)
{
	int		i;
	int		shlvl;
	char	*new_shlvl;

	i = 0;
	if (envp_tab == NULL)
		return ;
	while (envp_tab[i])
	{
		if (!ft_strncmp(envp_tab[i], "SHLVL=", 6))
		{
			shlvl = ft_atoi(&(envp_tab[i][6]));
			shlvl++;
			new_shlvl = ft_itoa(shlvl);
			ft_strlcpy(&envp_tab[i][6], new_shlvl, ft_strlen (new_shlvl) + 1);
			free(new_shlvl);
		}
		i++;
	}
}

/**========================================================================
 *                           duplicate_envp
 *========================================================================**/
char	**duplicate_envp(t_Data *data, char *envp[])
{
	char	**envp_tab;
	int		i;
	
	if (envp[0] == NULL)
		return (ft_printf("No env var... no fun!\n"), NULL);
	i = 0;
	while (envp[i])
		i++;
	envp_tab = (char **)ft_calloc(i + 1, sizeof(char *));
	if (envp_tab == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_tab[i] = (char *)ft_calloc((ft_strlen(envp[i]) + 1), sizeof(char));
		if (envp_tab[i] == NULL)
			return (NULL);
		ft_strlcpy(envp_tab[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	envp_tab[i] = NULL;
	update_shlvl(envp_tab);
	return (envp_tab);
	(void)data;
}
