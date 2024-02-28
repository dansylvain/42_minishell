/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:22:59 by seblin            #+#    #+#             */
/*   Updated: 2024/02/28 14:23:26 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "pipex_setup.h"
#include <stdlib.h>
#include "libft.h"

int		get_fdio(t_redir *redir);
void	close_fd(int fd);
void	close_fds(int fd[]);
void	here_doc_handle(int pipefd_in[], t_redir redir);

#endif