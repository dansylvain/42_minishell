/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:27:14 by svidot            #+#    #+#             */
/*   Updated: 2024/02/28 15:22:29 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

typedef struct set_redir
{
	int		redir[2];
	int		fd_file[2];
	char	*filepath[2];
	char	*delim;
	int		pipe[2];
}	t_redir;

void	close_fd(int fd);
void	close_fds(int fd[]);

#endif
