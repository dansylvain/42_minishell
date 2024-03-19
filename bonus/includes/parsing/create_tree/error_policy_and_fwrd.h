/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_policy_and_fwrd.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:45:26 by seblin            #+#    #+#             */
/*   Updated: 2024/03/17 17:49:50 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_POLICY_AND_FWRD_H
# define ERROR_POLICY_AND_FWRD_H

# include <stdlib.h>
# include "parsing_utils.h"
# include "libft.h"

void		display_error_free(char *str);
int			set_space(t_ast_nde *node);
int			set_operator(t_ast_nde *node);
char		*translate_enum(t_tok token);
int			is_chevron(t_ast_nde *node);
int			is_only_space_op(char *start, char *end);
int			is_sibling_only_space(t_ast_nde *sib);

#endif