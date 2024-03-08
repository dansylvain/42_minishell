/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:57:20 by dan               #+#    #+#             */
/*   Updated: 2024/03/08 19:42:28 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_3_H
# define UTILS_3_H

# include <minishell.h>
# include <stdlib.h>
# include <libft.h>
# include "ft_printf.h"

void	update_shlvl(char	**envp_tab);
void	free_command_tab(char ***command_tab);

#endif
