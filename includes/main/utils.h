/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:57:31 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "parsing_utils.h"
# include <stdlib.h>
# include "ft_printf.h"
# include "libft.h"

void	close_minishell(t_Data *data);
void	free_data(t_Data *data);
void	free_command_tab(char ***command_tab);
void	free_command_tab_lg(char ***command_tab);

#endif
