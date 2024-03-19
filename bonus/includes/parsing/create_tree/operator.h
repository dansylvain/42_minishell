/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:27:56 by seblin            #+#    #+#             */
/*   Updated: 2024/03/17 18:12:56 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_H
# define OPERATOR_H

# include <stdlib.h>
# include "parsing_utils.h"
# include "libft.h"

t_ast_nde	*create_token_child(t_ast_nde *raw, t_ast_nde *token);
void		fill_child(t_ast_nde *sib, t_ast_nde *raw_lft,
				t_ast_nde *raw_rght, t_ast_nde *token);
int			error_policy_and_forwarding(t_ast_nde *raw_lft,
				t_ast_nde *raw_rght, t_ast_nde *token);
int			error_policy_and_forwarding_2(t_ast_nde *raw_lft,
				t_ast_nde *raw_rght, t_ast_nde *token);
int			set_space(t_ast_nde *node);

#endif