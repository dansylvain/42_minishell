/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:27:14 by svidot            #+#    #+#             */
/*   Updated: 2024/03/08 12:19:35 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

typedef struct set_redir
{
	int		redir[2];
	int		file_fd[2];
	char	*filepath[2];
	char	*delim;
	int		hd_pipe[2];
}	t_redir;

void	close_fd(int fd);
void	close_fds(int fd[]);

#endif
