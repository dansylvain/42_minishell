/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:01:17 by seblin            #+#    #+#             */
/*   Updated: 2024/03/10 22:20:03 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

void	handle_ctrl_d(char *line, t_redir *redir)
{
	char	*ctrl_d;

	free(line);
	get_next_line(42);
	ctrl_d = ft_strdup(redir->delim);
	ctrl_d[ft_strlen(redir->delim) - 1] = 0;
	ft_printf("\nwarning: here-document at line 1 \
delimited by end-of-file (wanted '%s\')\n", ctrl_d);
	free(ctrl_d);
}

void	here_doc_handle(t_redir *redir)
{
	char	*line;

	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (line)
		{
			if (line[ft_strlen(line) - 1] != '\n')
				ft_printf("\n");
			else if (ft_strcmp(line, redir->delim))
				ft_putstr_fd(line, redir->pipe_hd[1]);
			else
			{
				free(line);
				get_next_line(42);
				break ;
			}
		}
		else
			return (handle_ctrl_d(line, redir));
		free(line);
	}
}
