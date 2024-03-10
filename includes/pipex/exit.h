/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:35:40 by seblin            #+#    #+#             */
/*   Updated: 2024/03/10 22:06:44 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "pipex_global_utils.h"
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include "parsing_utils.h"
# include "minishell.h"

void	display_error(char *str);
void	store_and_free_cmd_list(t_ast_nde *cmd_list);
void	free_command_tab_lg(char ***command_tab);
void	free_data(t_Data *data);
t_Data	*get_data(char *envp[]);

#endif
