/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab_utils.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:54:13 by dan               #+#    #+#             */
/*   Updated: 2024/03/13 07:55:36 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_COMMAND_TAB_UTILS_H
# define FILL_COMMAND_TAB_UTILS_H

# include "parsing_utils.h"
# include "libft.h"

char	*get_node_str(t_ast_nde *node);
int		is_separator(t_ast_nde *node);
int		is_chevron(t_ast_nde *node);
char	**add_sep_tab(char **cmd_tab_sep, t_ast_nde *node);
char	***add_redir_tabs(char ***cmd_tab, t_ast_nde **node, int *i);
char	**add_remaining_tabs(char **cmd_tab_tab, t_ast_nde *node);
int		get_cmd_nbr(t_ast_nde *node);

#endif