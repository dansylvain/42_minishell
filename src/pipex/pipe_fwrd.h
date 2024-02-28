/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fwrd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:18:04 by seblin            #+#    #+#             */
/*   Updated: 2024/02/28 14:19:11 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_FWRD_H
# define PIPE_FWRD_H

# include <unistd.h>
# include "pipex_setup.h"
# include "libft.h"

void	close_fds(int fd[]);
void	close_fd(int fd);

#endif