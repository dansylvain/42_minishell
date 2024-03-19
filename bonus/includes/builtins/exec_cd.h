/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:52:37 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CD_H
# define EXEC_CD_H

# include <minishell.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <libft.h>

void	update_home_env_var(t_Data *data);
int		exec_cd(t_Data *data, char **command_tab);
void	add_env_var_to_envp_tab(char **command_tab, t_Data *data, int *i);
void	display_error(char *str);
void	display_error_detail(char *str, char *details, char *str2);

#endif
