/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:27:56 by seblin            #+#    #+#             */
/*   Updated: 2024/03/15 09:54:33 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_H
# define OPERATOR_H

# include <stdlib.h>
# include "parsing_utils.h"
# include "libft.h"

void		display_error_free(char *str);
int			set_space(t_ast_nde *node);
int			set_operator(t_ast_nde *node);
char		*translate_enum(t_tok token);
t_ast_nde	*create_token_child(t_ast_nde *raw, t_ast_nde *token);
void		fill_child(t_ast_nde *sib, t_ast_nde *raw_lft,
				t_ast_nde *raw_rght, t_ast_nde *token);
int			is_chevron(t_ast_nde *node);
int			is_sibling_only_space(t_ast_nde *sib);
int			is_only_space_no_term(char *start, char *end);

#endif