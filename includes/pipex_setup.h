/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_setup.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:27:14 by svidot            #+#    #+#             */
/*   Updated: 2024/02/17 19:03:09 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_SETUP_H
# define PIPEX_SETUP_H

typedef struct set_redir
{
	int		redir[2];
	int		fd_file[2];
	char	*filepath[2];
	char	*delim;
}	t_redir;

#endif
