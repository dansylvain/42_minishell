/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:54:56 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_EXPORT_H
# define EXEC_EXPORT_H

# include <minishell.h>
# include <stdlib.h>
# include "libft.h"

int		exec_export(char **command_tab, t_Data *data);
int		realloc_env_var(t_Data *data, char var[], char *new_var_command);
void	add_env_var_to_envp_tab(char **command_tab, t_Data *data, int *i);
void	create_export_tab(t_Data *data, char export_tab[][500]);
void	display_export_tab(char export_tab[][500]);
int		are_only_valid_chars(char *str);
void	display_error_detail(char *str, char *details, char *str2);
char	*get_env_var(t_Data *data, char *to_find);
char	**create_new_env_var(char **envp, char *env_var);
void	free_command_tab(char ***command_tab);

#endif
