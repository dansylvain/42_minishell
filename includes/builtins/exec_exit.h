/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:55:11 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_EXIT_H
# define EXEC_EXIT_H

# include <minishell.h>
# include <stdlib.h>
# include "ft_printf.h"
# include "libft.h"
# include "parsing_utils.h"

void	store_and_free_cmd_list(t_ast_nde *cmd_list);;
void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);;
void	store_and_free_cmd_tab(char ***cmd_tab);;
void	display_exit_stuff(t_Data *data, char **command_tab);
int		exec_exit(t_Data *data, char **command_tab);
int		str_is_digit(char *str);
void	display_error_detail(char *str, char *details, char *str2);
void	display_error(char *str);
void	free_data(t_Data *data);

#endif
