/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_tab_allocation.h                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:58:48 by dan               #+#    #+#             */
/*   Updated: 2024/03/13 08:59:39 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_COMMAND_TAB_ALLOCATION_H
# define CREATE_COMMAND_TAB_ALLOCATION_H

# include "parsing_utils.h"
# include "minishell.h"
# include "libft.h"
# include "ft_printf.h"

int		is_separator(t_ast_nde *node);
int		is_chevron(t_ast_nde *node);
void	display_command_tab_big(char ***command_tab);
void	print_node(t_ast_nde *node);
void	print_tree(t_ast_nde *node);
char	*get_node_str(t_ast_nde *node);
int		get_pipe_parts_nbr(t_ast_nde **node);
char	***alloc_memory_for_pipe_parts(char ***cmd_tab, int pipe_parts_nbr);
int		get_pipe_elements_nbr(t_ast_nde *node);
char	**alloc_memory_for_pipe_elements(char **cmd_tab, int pipe_elements_nbr);

#endif