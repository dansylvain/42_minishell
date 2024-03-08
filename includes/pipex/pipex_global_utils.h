/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_global_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:44:24 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:44:27 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_GLOBAL_UTILS_H
# define PIPEX_GLOBAL_UTILS_H

typedef struct set_redir
{
	int		redir[2];
	int		pipe_io[2][2];
	int		pipe_hd[2];
	int		fd_file[2];
	char	*filepath[2];
	char	*delim;
}	t_redir;

void	close_fd(int fd);
void	close_fds(int fd[]);

#endif
