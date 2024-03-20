/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:27:47 by seblin            #+#    #+#             */
/*   Updated: 2024/02/28 16:15:32 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "parsing_utils.h"

t_ast_nde	*create_token_child(t_ast_nde *raw, t_ast_nde *token);
void		fill_child(t_ast_nde *sib, t_ast_nde *raw_lft, t_ast_nde *raw_rght,
				t_ast_nde *token);

#endif