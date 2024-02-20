/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:06:02 by svidot            #+#    #+#             */
/*   Updated: 2024/02/20 08:44:15 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"


void	display_error(char *str);
void	free_ptr_arr(char **arr);

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
/**========================================================================
 *!                             COMMENT BLOCK
 *!		THIS FREE CAUSES COMMAND "ls -a -l" to terminate  
 *!  	with error message "free(): invalid pointer"
 *========================================================================**/
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

char	*search_env_var(char *envp[], char *env_to_find)
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
	//ft_printf("in search: -%s-", env_find);
	if (!env_find)
		return (NULL);
	env_find += ft_strlen(env_to_find);
	//ft_printf("in search: -%s-", env_find);
	return (env_find);
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
		//ft_printf("not exist:%s\n", *argv);
		// ft_putstr_fd("%s: command not found\n", argv[0]);
		display_error("command not found\n");
		// perror(*argv);
		// free_ptr_arr(split_arg);
		exit(1);
	}

	return (split_arg);
}