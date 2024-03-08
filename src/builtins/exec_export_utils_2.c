/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:52:59 by dsylvain          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:27 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_export_utils_2.h"

/**========================================================================
 *                           get_env_var
 *========================================================================**/
char	*get_env_var(t_Data *data, char *to_find)
{
	char	*env_var;
	int		len;
	int		j;
	char	*var;

	env_var = NULL;
	len = ft_strlen(to_find);
	j = 0;
	while (data->envp_tab[j])
	{
		var = data->envp_tab[j];
		if (!ft_strncmp(var, to_find, len) && var[len] == '=')
		{
			env_var = &var[len + 1];
			break ;
		}
		j++;
	}
	return (env_var);
}

/**========================================================================
 *                           are_only_valid_chars
 *========================================================================**/
int	are_only_valid_chars(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='
			&& str[i] != '\"' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
