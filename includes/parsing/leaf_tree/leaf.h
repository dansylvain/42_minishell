/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:29:53 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 19:45:37 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAF_H
# define LEAF_H

# include "parsing_utils.h"
# include <unistd.h>
# include "minishell.h"

void		leaf_tree(t_ast_nde *oper, t_ast_nde **rslt,
				t_ast_nde **rslt_sav, t_Data *data);
char		*rebuild_dollar_str(const t_ast_nde *oper,
				char *str, t_Data *data);
t_ast_nde	*rebuild_dollar_str_node(char *str, t_tok token);

#endif