/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:30:00 by seblin            #+#    #+#             */
/*   Updated: 2024/03/11 13:12:34 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include "parsing_utils.h"
# include "libft.h"
# include "minishell.h"
# include "ft_printf.h"

int			set_parenthesis(t_ast_nde *node);
t_ast_nde	*set_qute_sib(char *str);
t_ast_nde	*set_operator(t_ast_nde *node);
void		leaf_tree(t_ast_nde *operator, t_ast_nde **rslt,
				t_ast_nde **rslt_sav, t_Data *data);
void		print_qute_sib(t_ast_nde *sib);
void		print_tree(t_ast_nde *node);
void		print_cmd(t_ast_nde *cmd);
void		display_error_free(char *str);
char		*translate_enum(t_tok token);
int			is_chevron(t_ast_nde *node);

#endif