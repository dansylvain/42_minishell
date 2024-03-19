/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:06:02 by svidot            #+#    #+#             */
/*   Updated: 2024/03/18 16:15:20 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

static char	*try_paths(char **argv, char *env_find)
{
	char	*cmd;
	char	**split_colon;
	char	**split_colon_sav;
	char	*tmp;

	cmd = NULL;
	split_colon = ft_split(env_find, ':');
	split_colon_sav = split_colon;
	while (split_colon && *split_colon)
	{
		tmp = ft_strjoin(*split_colon++, "/");
		cmd = ft_strjoin(tmp, *argv);
		free(tmp);
		if (!access(cmd, X_OK))
		{
			free(*argv);
			*argv = cmd;
			break ;
		}
		free(cmd);
		cmd = NULL;
	}
	ft_free_ptr_arr((void **) split_colon_sav);
	return (cmd);
}

static char	*search_env_var(char *envp[], char *env_to_find)
{
	char	*env_find;

	env_find = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp++, env_to_find, ft_strlen(env_to_find)))
		{
			env_find = *--envp;
			break ;
		}
	}
	if (env_find)
		env_find += ft_strlen(env_to_find);
	return (env_find);
}

int	search_path(char *argv[], char *envp[])
{
	char	*env_find;

	if (!**argv)
		return (1);
	env_find = search_env_var(envp, "PATH=");
	if (!env_find)
	{
		ft_putstr_fd("PATH: not found.\n", 2);
		return (1);
	}
	if (!try_paths(argv, env_find))
	{
		display_error_detail(argv[0], ": command ", "not found\n");
		return (1);
	}
	return (0);
}

char	*search_var(t_ast_nde *node, t_Data *data)
{
	char	*str;
	char	*var;
	char	*tmp;

	str = ft_strndup(node->start, node->end - node->start + 1);
	if (*(str + 1) == '?')
	{
		node->token = STAT;
		var = ft_strdup("$$$");
	}
	else
	{
		tmp = ft_strjoin_up(str + 1, "=", 0, 0);
		var = search_env_var(data->envp_tab, tmp);
		if (var)
			var = ft_strdup(var);
		free(tmp);
	}
	if (str)
		free(str);
	return (var);
}
