/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:30:00 by seblin            #+#    #+#             */
/*   Updated: 2024/03/02 17:52:51 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include "parsing_utils.h"
# include "libft.h"
# include "minishell.h"

int	set_parenthesis(t_ast_nde *node);
t_ast_nde	*set_qute_sib(char *str);
t_ast_nde	*set_operator(t_ast_nde *node);
void		leaf_tree(t_ast_nde *operator, t_ast_nde **rslt,
				t_ast_nde **rslt_sav, t_Data *data);

void		print_qute_sib(t_ast_nde *sib);//!
void		print_tree(t_ast_nde *node);//!
void		print_cmd(t_ast_nde *cmd);//!

#endif