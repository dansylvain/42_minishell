/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:22:59 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 20:54:38 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "pipex_global_utils.h"
# include <stdlib.h>
# include "libft.h"

int		get_fd_in(t_redir *redir);
int		get_fd_out(t_redir *redir);
void	here_doc_handle(t_redir *redir);
void	init_pipe_io(t_redir *redir);

#endif