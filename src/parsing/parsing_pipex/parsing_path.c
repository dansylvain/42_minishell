/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:06:02 by svidot            #+#    #+#             */
/*   Updated: 2024/02/14 15:47:14 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "parsing_build.h"

void	display_error(char *str);

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
	free_ptr_arr(split_colon_sav);
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
	if (!env_find)
		return (NULL);
	env_find += ft_strlen(env_to_find);
	return (env_find);
}

char	**parse_cmd(char *argv[], char *envp[])
{
	char	**split_arg;
	char	*env_find;

	if (!**argv)
		return (NULL);
	env_find = search_env_var(envp, "PATH=");
	if (!env_find)
	{
		ft_putstr_fd("env PATH not found.\n", 2);
		exit(1);
	}
	split_arg = create_ast_pipex(*argv);
	if (!try_paths(split_arg, env_find) && ft_strcmp(*split_arg, "cd")
		&& ft_strcmp(*split_arg, "unset") && ft_strcmp(*split_arg, "export")
		&& ft_strcmp(*split_arg, "exit"))
	{
		// perror(*split_arg);
		//free_ptr_arr(split_arg);
		//exit(1);
	}// printf("in parse %s\n", *split_arg);
//	ft_putstr_fd("in parse\n", 2 );
	return (split_arg);
}
char	**search_path(char *argv[], char *envp[])
{
	char	**split_arg;
	char	*env_find;

	if (!**argv)
		return (NULL);
	env_find = search_env_var(envp, "PATH=");
	if (!env_find)
	{
		ft_putstr_fd("env PATH not found.\n", 2);
		exit(1);
	}	
	if (!try_paths(argv, env_find))
	{
		ft_putstr_fd("not_existing_command: command not found\n", 2);
		
		// perror(*argv);
		// free_ptr_arr(split_arg);
		exit(1);
	}

	return (split_arg);
}