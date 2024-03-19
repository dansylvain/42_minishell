/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:28:05 by seblin            #+#    #+#             */
/*   Updated: 2024/03/11 13:47:23 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

# include "minishell.h"
# include "parsing_utils.h"
# include "libft.h"

void	display_error(char *str);
t_Data	*get_data(char *envp[]);

#endif