/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:14:14 by seblin            #+#    #+#             */
/*   Updated: 2024/03/10 22:22:44 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

static void	free_all(t_redir *redir, char **argv_sav[])
{
	free_data(get_data(NULL));
	free_command_tab_lg(argv_sav);
	store_and_free_cmd_list(NULL);
	if (redir->delim)
		free(redir->delim);
}

void	free_and_exit(t_redir *redir, char **argv_sav[], int n_exit,
	char *err_str)
{
	if (err_str)
		display_error(err_str);
	free_all(redir, argv_sav);
	exit(n_exit);
}

void	errno_handle(char **argv[], char **argv_sav[], t_redir *redir)
{
	if (errno == EACCES)
	{
		if (access(**argv, X_OK))
		{
			display_error("minishell: ");
			display_error(**argv);
			free_and_exit(redir, argv_sav, 126, ": Permission denied\n");
		}
		else
		{
			display_error("minishell: ");
			display_error(**argv);
			free_and_exit(redir, argv_sav, 126, ": Is a directory\n");
		}
	}
	else if (errno == ENOENT)
	{
		display_error("minishell: ");
		display_error(**argv);
		free_and_exit(redir, argv_sav, 127, ": No such file or directory\n");
	}
	else if (errno == ENOEXEC)
		free_and_exit(redir, argv_sav, EXIT_SUCCESS, NULL);
}
