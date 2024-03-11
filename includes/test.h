/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:28:26 by seblin            #+#    #+#             */
/*   Updated: 2024/03/11 11:32:58 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_C
# define TEST_C

# include <stdio.h>
# include <stdlib.h>
# include "parsing_utils.h"
# include "ft_printf.h"

void	print_space_tree(t_ast_nde *node);
void	print_tree(t_ast_nde *node);
void	print_raw(t_ast_nde *raw);
void	print_descend(t_ast_nde *node);
void	print_cmd(t_ast_nde *cmd);
void	print_sibling(t_ast_nde *sib);
void	print_node(t_ast_nde *node);
void	print_qute_sib(t_ast_nde *sib);
void	print_raw(t_ast_nde *raw);

#endif