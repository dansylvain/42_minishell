/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:22:59 by seblin            #+#    #+#             */
/*   Updated: 2024/02/28 16:16:46 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "pipex_utils.h"
# include <stdlib.h>
# include "libft.h"

int		get_fdio(t_redir *redir);
void	here_doc_handle(int pipefd_in[], t_redir redir);

#endif