/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:54:41 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_ENV_H
# define EXEC_ENV_H

# include <minishell.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "ft_printf.h"

void	exec_env(t_Data *data, char **command_tab);
void	display_error_detail(char *str, char *details, char *str2);

#endif
