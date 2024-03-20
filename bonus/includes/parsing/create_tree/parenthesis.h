/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:28:02 by seblin            #+#    #+#             */
/*   Updated: 2024/03/16 14:42:10 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARENTHESIS_H
# define PARENTHESIS_H

# include <stdlib.h>
# include "parsing_utils.h"
# include "libft.h"

t_ast_nde	*copy_node(t_ast_nde *node);
int			set_parenthesis(t_ast_nde *node);
void		fill_child_par(t_ast_nde *sib, t_ast_nde **raw_child,
				t_ast_nde *token);
int			create_token_node(t_ast_nde *sib, t_ast_nde **token_nde);

#endif