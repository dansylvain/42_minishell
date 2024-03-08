/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:29:50 by seblin            #+#    #+#             */
/*   Updated: 2024/03/08 19:45:25 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOLLAR_EXPANSION_H
# define DOLLAR_EXPANSION_H

# include <unistd.h>
# include "parsing_utils.h"
# include "minishell.h"
# include "libft.h"

char	*wilcard_func(char *pattern);
void	display_error_detail(char *str, char *details, char *str2);
char	*search_var(const t_ast_nde *node, t_Data *data);

#endif