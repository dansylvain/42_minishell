/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:52:53 by dan               #+#    #+#             */
/*   Updated: 2024/03/18 05:29:23 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_ECHO_H
# define EXEC_ECHO_H

# include <minishell.h>
# include "ft_printf.h"
# include "libft.h"

void	exec_echo(t_Data *data, char **command_tab);
int		is_only_space(char *str);
int		is_not_empty_prompt(char *str);
t_Data	*get_data(char *envp[]);

#endif
