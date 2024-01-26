/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_qute.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:34:55 by svidot            #+#    #+#             */
/*   Updated: 2024/01/26 15:22:05 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_QUTE_H
# define PARSING_QUTE_H

# include "parsing_utils.h"

char		clean_quotes(char *start, t_ast_nde	*qute_nde);
t_ast_nde	*set_quote_nde(char *argv);

#endif