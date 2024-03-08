/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidot <svidot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:22:59 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 11:14:42 by svidot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "pipex_utils.h"
# include <stdlib.h>
# include "libft.h"

int		get_fd_in(t_redir *redir);
int		get_fd_out(t_redir *redir);
void	here_doc_handle(int pipefd_in[], t_redir redir);

#endif