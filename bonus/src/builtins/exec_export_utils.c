/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:11:13 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 16:23:40 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_export_utils.h"

/**========================================================================
 *                           create_export_tab
 *========================================================================**/
void	create_export_tab(t_Data *data, char export_tab[][500])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_memset(export_tab, '\0', sizeof(char) * 500 * 100);
	while (data->envp_tab[i])
	{
		if (ft_strncmp(data->envp_tab[i], "_=", 2)
			&& has_var(data->envp_tab[i]))
		{
			ft_strlcpy(export_tab[j], data->envp_tab[i], sizeof(export_tab[j]));
			insert_quote(export_tab[j]);
			j++;
		}
		i++;
	}
	format_export_tab(export_tab);
}

/**========================================================================
 *                           format_export_tab
 *========================================================================**/
void	format_export_tab(char export_tab[][500])
{
	int		i;
	char	str[500];

	ft_bzero(str, 500);
	i = 0;
	while (export_tab[i][0] && export_tab[i + 1][0])
	{
		if (ft_strcmp(export_tab[i], export_tab[i + 1]) > 0)
		{
			ft_strlcpy(str, export_tab[i], 500);
			ft_strlcpy(export_tab[i], export_tab[i + 1], 500);
			ft_strlcpy(export_tab[i + 1], str, 500);
			i = 0;
			continue ;
		}
		i++;
	}
}

/**========================================================================
 *                           insert_quote
 *========================================================================**/
void	insert_quote(char *str)
{
	int		i;
	char	tmp[500];
	int		qute_dne;

	i = 0;
	qute_dne = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] == '\0')
		{
			qute_dne = 1;
			str[i + 1] = '\"';
		}
		if (str[i + 1] && str[i] == '=' && qute_dne == 0)
		{
			qute_dne = 1;
			ft_memcpy(tmp, &(str[i + 1]), 501 - i);
			ft_memcpy(&(str[i + 2]), tmp, 500 - i);
			str[i + 1] = '\"';
		}
		i++;
	}
	if (qute_dne == 1)
		str[i] = '\"';
}

/**========================================================================
 *                           has_var
 *========================================================================**/
int	has_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/**========================================================================
 *                           display_export_tab
 *========================================================================**/
void	display_export_tab(char export_tab[][500])
{
	int	i;

	i = 0;
	while (export_tab[i][0])
		ft_printf("declare -x %s\n", export_tab[i++]);
}
