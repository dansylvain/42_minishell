/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:28:10 by seblin            #+#    #+#             */
/*   Updated: 2024/02/28 14:40:06 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPACE_H
# define SPACE_H

# include <stdlib.h>
# include "parsing_utils.h"

t_ast_nde	*set_dollar(t_ast_nde *node);
void		fill_child(t_ast_nde *sib, t_ast_nde *raw_lft,
				t_ast_nde *raw_rght, t_ast_nde *token);
t_ast_nde	*create_token_child(t_ast_nde *raw, t_ast_nde *token);

#endif