/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:03:28 by dan               #+#    #+#             */
/*   Updated: 2024/03/13 10:21:13 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_COMMAND_TAB_H
# define FILL_COMMAND_TAB_H

# include "parsing_utils.h"
# include "libft.h"
# include "ft_printf.h"

void	free_node(t_ast_nde *node);
char	*get_node_str(t_ast_nde *node);
int		is_separator(t_ast_nde *node);
int		is_chevron(t_ast_nde *node);
char	**add_sep_tab(char **cmd_tab_sep, t_ast_nde *node);
char	***add_redir_tabs(char ***cmd_tab, t_ast_nde **node, int *i);
char	**add_remaining_tabs(char **cmd_tab_tab, t_ast_nde *node);
int		get_cmd_nbr(t_ast_nde *node);
char	***add_sep_tab_loop(char ****cmd_tab, t_ast_nde **node, int *i);
char	***add_remaining_tabs_loop(char ***cmd_tab, t_ast_nde *node,
			int *cmd_was_added, int *i);
char	***add_redir_tabs_loop(char ***cmd_tab, t_ast_nde **node,
			int *redir_were_added, int *i);

#endif
