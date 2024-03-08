/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_utils_2.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:55:06 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_EXPORT_UTILS_2_H
# define EXEC_EXPORT_UTILS_2_H

# include <minishell.h>
# include <stddef.h>
# include "libft.h"
# include "parsing_utils.h"

int		are_only_valid_chars(char *str);
void	store_and_free_cmd_tab_node_sav(t_ast_nde *cmd_tab_node_sav);

#endif
