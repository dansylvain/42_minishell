/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:01:34 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 18:51:00 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include "pipex_global_utils.h"
# include "ft_printf.h"
# include "../../lib/gnl/get_next_line.h"
# include "libft.h"
# include "parsing_utils.h"
# include "minishell.h"

void	display_error(char *str);
void	store_and_free_cmd_list(t_ast_nde *cmd_list);
void	free_command_tab_lg(char ***command_tab);
void	free_data(t_Data *data);
t_Data	*get_data(char *envp[]);

#endif