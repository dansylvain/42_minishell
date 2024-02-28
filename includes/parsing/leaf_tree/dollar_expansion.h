/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:29:50 by seblin            #+#    #+#             */
/*   Updated: 2024/02/28 15:18:06 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOLLAR_EXPANSION_H
# define DOLLAR_EXPANSION_H

# include <unistd.h>
# include "parsing_utils.h"
# include "minishell.h"

char		*search_var(const t_ast_nde *node, t_Data *data);

#endif