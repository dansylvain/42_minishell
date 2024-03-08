/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:03:28 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_COMMAND_TAB_H
# define FILL_COMMAND_TAB_H

# include <minishell.h>
# include <stdlib.h>
# include "parsing_utils.h"
# include "libft.h"
# include "ft_printf.h"

void	print_node(t_ast_nde *node);;
void	store_and_free_cmd_tab(char ***cmd_tab);;
int		is_raw(t_ast_nde *node);;
void	print_ast_sib(t_ast_nde *sib);;
int		is_raw(t_ast_nde *node);
void	add_pipe_tab_to_tab(char ****cmd_tab, int *i);
void	create_chev_tab(char ****cmd_tab, t_ast_nde **current, int *i);
void	add_raw_to_cmd_tab(t_Data *data,
			char ****cmd_tab, t_ast_nde *current, int *i);
int		cmd_tab_error_check(t_ast_nde *node);
void	create_dollar_tab(t_Data *data, t_ast_nde **node,
			char ****cmd_tab, int *i);
void	complete_raw_tab(t_Data *data, char ****cmd_tab,
			t_ast_nde *node, int *i);
char	*get_node_str(t_Data *data, t_ast_nde *node);
int		is_separator(t_ast_nde *node);
int		is_chevron(t_ast_nde *node);

#endif
