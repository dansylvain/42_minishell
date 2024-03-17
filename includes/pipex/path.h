/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:15:20 by seblin            #+#    #+#             */
/*   Updated: 2024/03/17 21:20:18 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"
# include "minishell.h"
# include "parsing_utils.h"

void	display_error(char *str);
void	display_error_detail(char *str, char *details, char *str2);
t_Data	*get_data(char *envp[]);

#endif