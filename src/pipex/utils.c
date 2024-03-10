/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:27:30 by seblin            #+#    #+#             */
/*   Updated: 2024/03/10 22:21:11 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

int	is_path(char *path)
{
	while (*path)
		if (*path++ == '/')
			return (1);
	return (0);
}

char	***forward_next_cmd(char **argv[])
{
	while (*argv && **argv && ***argv != '|')
	{
		if (***argv != '>' && ***argv != '<' )
			return (argv);
		argv++;
	}
	return (NULL);
}

int	forward_next_pipe(char ***argv[])
{
	while (**argv && ***argv && ****argv)
		if (***(*argv)++ == '|')
			return (1);
	return (0);
}
