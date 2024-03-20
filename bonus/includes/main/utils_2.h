/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seblin <seblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:57:07 by dan               #+#    #+#             */
/*   Updated: 2024/03/11 10:21:09 by seblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_2_H
# define UTILS_2_H

# include <minishell.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

void	display_error(char *str);
void	display_error_free(char *str);
void	display_error_detail(char *str, char *details, char *str2);
t_Data	*get_data(char *envp[]);

#endif
