/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:03:54 by dan               #+#    #+#             */
/*   Updated: 2024/02/11 12:04:08 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parsing_utils.h"

int	is_env_var(char *str)
{
	int		i;
	char	*tok;

	tok = "\'\"<>|&";
	if (str[0] != '$')
		return (0);
	i = 0;
	while (tok[i] != '\0')
		if (str[1] == tok[i++])
			return (0);
	if (str[1] == '\0')
		return (0);
	return (1);
}

char	*get_env_var(t_Data *data, char *str, char buff[])
{
	int		i;
	int		j;
	int		k;
	char	*env_var;

	ft_bzero(buff, 2000);
	i = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
			&& str[i] != '>' && str[i]
			!= '<' && str[i] != '|' && str[i] != '&'))
		i++;
	k = 0;
	ft_memcpy(buff, str, i);
	buff[i] = '\0';
	j = 0;
	while (data->envp_tab[j])
	{
		if (!ft_strncmp(&buff[1], data->envp_tab[j], i - 1)
			&& data->envp_tab[j][ft_strlen(buff) - 1] == '=')
			return (getenv(&buff[1]));
		j++;
	}
	env_var = ft_strdup(buff);
	ft_bzero(env_var, ft_strlen(buff));
	return (env_var);
}

void	insert_env_var(char **command, char *env_var, char buff[])
{
	char	*start;
	char	*end;
	int		len;
	char	*sav_command;

	sav_command = (*command);
	len = ft_strlen(buff);
	start = ft_strstr((*command), buff);
	end = &start[len];
	(*command) = (char *)ft_calloc(ft_strlen(sav_command)
			- len + ft_strlen(env_var) + 1, sizeof(char));
	if ((*command) == NULL)
		return ;
	ft_strlcpy((*command), sav_command, &start[0] - &sav_command[0] + 1);
	ft_strlcat(&(*command)[ft_strlen((*command))],
		env_var, ft_strlen(env_var) + 1);
	ft_strlcat(&(*command)[ft_strlen((*command))], end, ft_strlen(end) + 1);
	free(sav_command);
}

void	check_if_env_var_and_get_it(t_Data *data, t_ast_nde **node, char **env_var, char buff[])
{
	t_ast_nde	*current;
	int	j;

	current = (*node)->child;
	while (current)
	{
		if (current->token == IN_DQUTE || current->token == RAW)
		{
			j = 0;
			while (j < current->end - current->start + 1)
			{
				if (is_env_var(&current->start[j]))
					*env_var = get_env_var(data, &current->start[j], buff);
				j++;
			}
		}
		current = current->sibling;
	}
}