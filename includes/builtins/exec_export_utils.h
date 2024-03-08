/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:55:02 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_EXPORT_UTILS_H
# define EXEC_EXPORT_UTILS_H

# include <minishell.h>
# include "ft_printf.h"
# include "libft.h"

void	create_export_tab(t_Data *data, char export_tab[][500]);
void	format_export_tab(char export_tab[][500]);
void	insert_quote(char *str);
int		has_var(char *str);
void	display_export_tab(char export_tab[][500]);

#endif
